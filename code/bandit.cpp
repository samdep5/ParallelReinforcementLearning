#pragma once
#include <random>
#include <map>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <math.h>

// Referenced https://stackoverflow.com/questions/19944111/creating-a-gaussian-random-generator-with-a-mean-and-standard-deviation

using namespace std;

// Bandit Class with attributes 
class Bandit {
    public:
    int N;  // Number of actions
    double *arms; // Actions are otherwise known as pulling different lever arms

    Bandit(int N);
    double take_action(int a); // Get the randomized reward from pulling the given lever
    int best_action(); // Calculate the mean best action (used only for profiling, never by the agent itself)
};


Bandit::Bandit(int n){
    this->N = n;

    // Draw mean pre-mangle rewards for arms from a normal distribution
    this->arms = new double[N];
    random_device rd;
    mt19937 val(rd());
    normal_distribution<double> dist(1.0, 1.0);

    for(int i = 0; i < N; i++){
      this->arms[i] = dist(val);
    }
}

int mangle_count = 100000;
double mangle(double initial_value) { // Mangle the output so it's not so obviously normally distributed
    double val = initial_value;
    for (int i = 0; i < mangle_count; i++) {
        val = tanh(val) * (1 + (5.0 / mangle_count));
    }
    return val;
}

double Bandit::take_action(int a){
    random_device rd;
    mt19937 val(rd());
    normal_distribution<double> dist(this->arms[a], 1);
    return mangle(dist(val)); 
}

int Bandit::best_action(){
    double best = mangle(this->arms[0]);
    double best_action = 0;
    for (int i = 1; i < this->N; i++){
        double mangled = mangle(this->arms[i]);
        if (mangled > best){
            best = mangled;
            best_action = i;
        }
    }
    return best_action;
}
