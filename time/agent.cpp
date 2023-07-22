#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <algorithm>
#include <cstring>
#include <assert.h>
#include <chrono>
#include <fstream>

#include "bandit.cpp"
#include "history.cpp"
#include "agent_generic.cpp"

using namespace std;
Bandit bandit(N);
int bandit_best = bandit.best_action(); // The agent, of course, does not know this.

int main(int argc, char *argv[]) {
    ofstream f;
    f.open("sequential.txt", ios_base::app);
    auto beginning = std::chrono::high_resolution_clock::now();

    // Parse arguments
    int episode_length;
    int episodes;

    if (argc != 3) {
        std::cout << "Usage: ./<> numberOfEpisodes episodeLength\n";
        return 1;
    } else {
        episodes = atoi(argv[1]);
        episode_length = atoi(argv[2]);
    }

    double reward = 0;

    History history(N, 1); // One level of history, since there is no synchronization necessary

    // Initialize randomness
    drand48_data randombuffer;
    srand48_r(time(NULL), &randombuffer);

    for (int i = 0; i < episodes; i++) {
        
        double new_reward = episode(bandit, N, episode_length, epsilon, history, &randombuffer);
        reward += new_reward;

        std::cout << "0\t" << i << "\t" << new_reward / episode_length << "\t" << ((double) history.action_count_level(bandit_best, 0)) / episode_length << "\n";

    }
    std::cout << "\n" << reward << "\t" << ((double) history.action_count(bandit_best)) / history.all_action_counts() << "\n";

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - beginning);
    f << "\n" << reward / elapsed.count() << "\t" << ((double) history.action_count(bandit_best)) / history.all_action_counts()/ elapsed.count() << "\n";
    f.close();
    
}
