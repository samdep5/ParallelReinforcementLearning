#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <assert.h>
#include <omp.h>

#include "bandit.cpp"

drand48_data randombuffer;

int N = 10;
int episodes = 500;
int episode_length = 100;
double epsilon = 0.1; // whynot.gif

Bandit bandit(N);

double rand_double() {
    double result;
    drand48_r(&randombuffer, &result);
    return result;
}

int rand_int_between(int low, int high) { // Assume 0 <= low <= high
    return (int) (low + rand_double() * (high - low)); // rand_double() < 1 and (int) truncates towards 0
}

int argmax(int N, double a[]) {
    assert (N > 1);
    int best = 0;
    #pragma omp parallel for
    for (int i = 1; i < N; i++) {
        #pragma omp critical
        if (a[i] > a[best]) best = i;
    }
    return best;
}

double episode(int N, int length, double epsilon, double estimates[], double action_counts[]) {
    double reward_accum; // Keep track of average reward
    int best = argmax(N, estimates);
    
    // Episode (epsilon-greedy exploration)
    #pragma omp parallel for
    for(int i = 0; i < length; i++) {
        int a;
        if (rand_double() < epsilon) {
            a = rand_int_between(0, N);
        } else {
            a = best;
        }
        double reward = bandit.take_action(a);

        #pragma omp critical
        {
            estimates[a] = (estimates[a] * action_counts[a] + reward) / (action_counts[a] + 1);
            if (a != best && estimates[a] > estimates[best]) best = a;
            action_counts[a]++;
            reward_accum += reward;
        }
    }

    return reward_accum / N;
}

int main() {

    MPI_Init(&argc, &argv);
    // Allow for nested parallelism
    // omp_set_nested(1);
    omp_set_num_threads(4);

    // Global go betweens: 
    double action_counts[N] = {};
    double estimates[N];
    std::fill_n (estimates, N, 100000.0); // Use large values for estimated rewards at first to force exploration.
    double reward = 0; 
    // Setup
    srand48_r(time(NULL), &randombuffer);
    int best_action = bandit.best_action();

    // Shared variables
    double action_counts[N] = {};
    double estimates[N];
    std::fill_n (estimates, N, 100000.0); // Use large values for estimated rewards at first to force exploration.
    double reward = 0; 
    // Setup
    srand48_r(time(NULL), &randombuffer);
    int best_action = bandit.best_action();

    // Learning
        for (int i = 0; i < episodes; i++) {
            double new_reward = episode(N, episode_length, epsilon, estimates, action_counts);
            #pragma omp atomic
            reward += new_reward;
            std::cout << i << " " << reward / (episode_length * (i + 1)) << " " << ((double) action_counts[best_action]) / ((double) (i + 1) * episode_length * agents) << "\n";
            if(episodes % frequency){
                MPI_Ireduce(&estimates, &estimates, )
            }
        }

    std::cout << reward / agents;
}
