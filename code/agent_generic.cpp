#include <cstdlib>
#include "bandit.cpp"
#include "history.cpp"

// Somewhat arbitrary constants
const int N = 10; // The number of arms on the bandit
const double epsilon = 0.1; // The probability with which the agent explores

// Generate a random double between 0 and 1.  Takes a specific buffer for thread-safety.
double rand_double(drand48_data* buffer) {
    double result;
    drand48_r(buffer, &result);
    return result;
}

// Generate a random it between low (inclusive) and high (exclusive).  Takes a specific buffer for thread-safety.
int rand_int_between(int low, int high, drand48_data* buffer) { // Assume 0 <= low <= high
    return (int) (low + rand_double(buffer) * (high - low)); // rand_double() < 1 and (int) truncates towards 0
}

// Carry out one episode: repeatedly take an action, record the reward, and learn.  Uses randomness so takes a buffer.
double episode(Bandit bandit, int N, int length, double epsilon, History history, drand48_data* buffer) {
    double reward_accum; // Keep track of total reward
    
    // Episode (epsilon-greedy exploration)
    for(int i = 0; i < length; i++) {
        int a; // The action to take
        if (rand_double(buffer) < epsilon) { // Explore with probability epsilon
            a = rand_int_between(0, N, buffer);
        } else { // Exploit with probability 1 - epsilon
            a = history.argmax_Q();
        }
        double reward = bandit.take_action(a);
        history.record(a, reward);
        reward_accum += reward;
    }

    return reward_accum; // Return total reward for the episode
}
