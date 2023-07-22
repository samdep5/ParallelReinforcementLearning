#pragma once
#include <cstdlib>

class History {
    double* history;
    int N;
    int levels;
    
    public:

    History(int N, int levels);
    void record(int a, double r); // Add a new element to history at level 0.
    void add_delta(int level, double* delta); // Add the history at the given level to a buffer.
    void sync_destructive(int level, double* combined_deltas); // Clear the history at the given level and add the values in the buffer to the next level.

    double Q(int a); // Estimate the expected reward from taking action a.
    int argmax_Q(); // Estimate the best action based on Q.

    int action_count_level(int a, int level); // How many times has this action been taken at this level?
    int action_count(int a); // How many times has this action been taken?
    int all_action_counts(); // How many times have we taken any actions?
    double total_reward(); // Total reward earned.
};

History::History(int N, int levels) {
    this->N = N;
    this->levels = levels;
    this->history = (double*) calloc(2 * N * levels, sizeof(double));
}

void History::record(int a, double r) {
    this->history[a] += 1; // Layer 0 is updated during episodes.
    this->history[a + N] += r;
}

void History::add_delta(int level, double* delta) {
    for (int i = 0; i < 2 * this->N; i++) {
        delta[i] += this->history[2 * N * level + i];
    }
}

void History::sync_destructive(int level, double* combined_deltas) {
    for (int i = 0; i < 2 * this->N; i++) {
        this->history[2 * N * level + i] = 0;
        this->history[2 * N * (level + 1) + i] += combined_deltas[i];
    }
}

double History::Q(int a) {
    double action_counts = 0;
    double rewards = 0;
    for (int i = 0; i < this->levels; i++) {
        action_counts += this->history[2 * N * i + a];
        rewards += this->history[2 * N * i + N + a];
    }
    if (action_counts == 0) {
        return 10000.0; // Use large estimated rewards for unknown values to encourage exploration.
    }
    return rewards / action_counts;
}

int History::argmax_Q() {
    int best = 0;
    double reward = this->Q(0);
    for (int i = 1; i < N; i++) {
        double newreward = this->Q(i);
        if (newreward > reward) {
            best = i;
            reward = newreward;
        }
    }
    return best;
}

int History::action_count_level(int a, int level) {
    return this->history[2 * N * level + a];
}

int History::action_count(int a) {
    int count = this->history[a];
    for (int i = 1; i < this->levels; i++) {
        count += action_count_level(a, i);
    }
    return count;
}

int History::all_action_counts() {
    int count = this->action_count(0);
    for (int i = 1; i < this->N; i++) {
        count += this->action_count(i);
    }
    return count;
}

double History::total_reward() {
    double count = 0;
    for (int i = 0; i < this->levels; i++){
        for(int j = N; j < 2 * N; j++) {
            count += this->history[2 * N * i + j];
        }
    }
    return count;
}