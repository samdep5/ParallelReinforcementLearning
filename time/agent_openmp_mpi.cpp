#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <algorithm>
#include <cstring>
#include <assert.h>
#include <omp.h>
#include <mpi.h>
#include <chrono>
#include <fstream>

#include "bandit.cpp"
#include "history.cpp"
#include "agent_generic.cpp"

using namespace std;
// See agent.cpp for the sequential algorithm and agent_openmp.cpp for the OpenMP parallelization on which this is based.

Bandit bandit(N);
int bandit_best;

void zero_array(double arr[]) {
    for (int i = 0; i < 2 * N; i++) {
        arr[i] = 0.0;
    }
}

int main(int argc, char *argv[]) {
    double total = 0.0;
    double historyaction = 0.0;
    double reward = 0;
    ofstream f;
    f.open("hybrid.txt", ios_base::app);
    auto beginning = std::chrono::high_resolution_clock::now();

    int episode_length;
    int episodes;

    if (argc != 3) {
        std::cout << "Usage: ./<> numberOfEpisodes episodeLength\n";
        return 1;
    } else {
        episodes = atoi(argv[1]);
        episode_length = atoi(argv[2]);
    }

    // Initialize MPI.  Must support at least the ability to run multiple OpenMP treads per process.
    int provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);
    if (provided < MPI_THREAD_FUNNELED) {
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
        return 0;
    }

    // Make sure we're all using the same bandit.  This should be blocking since learning without the right bandit is just usless.
    MPI_Bcast(bandit.arms, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    bandit_best = bandit.best_action ();

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    
    double local_sync_buffer[2 * N]; // For synchronization between OpenMP threads on the same node.
    double global_sync_buffer[2 * N]; // For synchronization across nodes.
    MPI_Request sync_req;

    // Measure time
    double t0, t1;
    t0 = omp_get_wtime();

    int numthreads;

#pragma omp parallel reduction(+: total)
{
    numthreads = omp_get_num_threads();
    int threadnum = omp_get_thread_num();

    drand48_data randombuffer;
    srand48_r(rank * 10000 + numthreads * 100 + time(NULL), &randombuffer);

    History history(N, 3); // Three levels: one for unsynchronized data, one for locally synchronized, and one for globally synchronized.

    #pragma omp reduction(+: reward)
    for (int i = 0; i < episodes / (numthreads * size); i++) { // Assume each node has the same number of OpenMP threads when calculating how many episodes to run on this one.

        // Begin global synchronization of level-1 histories before the episode, so that the latency can be hidden by the episode calculations.
#pragma omp master
{
        zero_array(global_sync_buffer);
        history.add_delta(1, global_sync_buffer); // History level 1 is already synchronized among all OpenMP agents, so we just use the master's here.
        MPI_Iallreduce(MPI_IN_PLACE, global_sync_buffer, 2 * N, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD, &sync_req);
}

        // Carry out the episode.
        double new_reward = episode(bandit, N, episode_length, epsilon, history, &randombuffer);
        reward += new_reward;

        // Wait for the MPI request to complete.
#pragma omp master
{
        zero_array(local_sync_buffer); // Zero out the local sync buffer while we wait, so that if the wait time is longer than the episode then at least one thread can do some useful work.
        MPI_Wait(&sync_req, MPI_STATUS_IGNORE);
}
#pragma omp barrier

        // Every thread pulls the history from the global sync buffer.
        history.sync_destructive(1, global_sync_buffer);

        //Carry out local synchronization as in the OpenMP-only implementation.
#pragma omp critical
{
        std::cout << threadnum << "\t" << i << "\t" << new_reward / episode_length << "\t" << ((double) history.action_count_level(bandit_best, 0)) / episode_length <<  "\n";
        history.add_delta(0, local_sync_buffer);
}

#pragma omp barrier
        history.sync_destructive(0, local_sync_buffer);

    }

// After the end of the loop, wait for all threads on all cores to complete and then print vital statistics before ending the OpenMP parallel section.
std::cout << std::flush ;
#pragma omp barrier
#pragma omp master
{
    MPI_Barrier (MPI_COMM_WORLD);
}
#pragma omp barrier
#pragma omp master
{
    //std::cout << "Rank:: " << rank << "\n";
    if (rank == 0) {
        std::cout << "\n" << history.total_reward () << "\t" << ((double) history.action_count(bandit_best)) / history.all_action_counts () << "\n";
        historyaction = ((double) history.action_count(bandit_best)) / history.all_action_counts();
        std::cout << "Total" << history.total_reward() << "\n";
        total = history.total_reward ();
    }
}
}

    if (rank == 0) {
        t1 = omp_get_wtime();
        std::cout << "Cores: " << size << "\n"
                  << "Threads on this core: " << numthreads << '\n'
                  << "Elapsed: " << t1 - t0 << " seconds\n";
        //Added for time keeping purposes
        f << total / (t1-t0) << "\t" << historyaction / (t1-t0) << "\t"<< (t1-t0)<< "\n";
        f.close();
    }
    MPI_Finalize ();

}
