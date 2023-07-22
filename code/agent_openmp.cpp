#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <algorithm>
#include <cstring>
#include <assert.h>
#include <omp.h>

#include "bandit.cpp"
#include "history.cpp"
#include "agent_generic.cpp"

// See agent.cpp for the sequential algorithm on which this is based.

Bandit bandit(N);
int bandit_best = bandit.best_action();

int main(int argc, char *argv[]) {
    int episode_length;
    int episodes;

    if (argc != 3) {
        std::cout << "Usage: ./<> numberOfEpisodes episodeLength\n";
        return 1;
    } else {
        episodes = atoi(argv[1]);
        episode_length = atoi(argv[2]);
    }

    // Setup
    double reward = 0;
    double sync_buffer[2 * N]; // Shared memory for synchronizing between threads

    // Measure time
    double t0, t1;
    t0 = omp_get_wtime();
    int numthreads;

#pragma omp parallel // Parallel section: every thread an agent
{
    numthreads = omp_get_num_threads();
    int threadnum = omp_get_thread_num();

    History history(N, 2); // Every agent gets its own history.  Two levels: one for unsynchronized data and one for synchronized.

    // Every agent gets its own random buffer.
    drand48_data randombuffer;
    srand48_r(numthreads * 100 + time(NULL), &randombuffer);

    #pragma omp  reduction(+: reward)
    for (int i = 0; i < episodes / numthreads; i++) {

        // Carry out episodes as in the sequential case.
        double new_reward = episode(bandit, N, episode_length, epsilon, history, &randombuffer);
        reward += new_reward;

        // Zero out the sync buffer in preparation for all threads to write to it.
#pragma omp master
{
        for (int j = 0; j < 2 * N; j++) {
            sync_buffer[j] = 0.0;
        }
}
#pragma omp barrier

        // Every thread outputs the details of its episode and then writes its history from the most recent episode into the sync buffer.
#pragma omp critical
{
        std::cout << threadnum << "\t" << i << "\t" << new_reward / episode_length << "\t" << ((double) history.action_count_level(bandit_best, 0)) / episode_length << "\n";
        history.add_delta(0, sync_buffer);
}
#pragma omp barrier

        // Every thread pulls the history from the sync buffer.
        history.sync_destructive(0, sync_buffer);

    }

    // After the loop, wait for all threads to complete and then print a summary.  Do this within the parallel section so as not to lose access to the history.
#pragma omp barrier
#pragma omp master
{
    std::cout << "\n" << reward << "\t" << ((double) history.action_count(bandit_best)) / history.all_action_counts () << "\n";
}
}

    // Output elapsed time.
    t1 = omp_get_wtime();
    std::cout << "Threads: " << numthreads << '\n'
              << "Elapsed: " << t1 - t0 << " seconds\n";
}
