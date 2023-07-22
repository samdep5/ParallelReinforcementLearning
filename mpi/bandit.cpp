#include <random>
#include <map>
#include <iomanip>
#include <iostream>
#include <algorithm>

// Referenced https://stackoverflow.com/questions/19944111/creating-a-gaussian-random-generator-with-a-mean-and-standard-deviation

using namespace std;

// Bandit Class with attributes 
class Bandit {
    public:
    int N;  // size of array
    double *arms; // Array of integers

    Bandit(int N);  // Create the local instance of each array
    double take_action(int a);
    int best_action();
};


// init function creating a bandit object 
Bandit::Bandit(int n){
    this->N = n;

    this->arms = new double[N];
    random_device rd;
    mt19937 val(rd());
    normal_distribution<double> dist(1.0, 1.0);

    #pragma omp parallel for 
    for(int i = 0; i < N; i++){
      this->arms[i] = dist(val);
    }
}

// Pull a lever
double Bandit::take_action(int a){
    random_device rd;
    mt19937 val(rd());
    normal_distribution<double> dist(this->arms[a], 1);
    return dist(val); 
}

int Bandit::best_action(){
    double best = this->arms[0];
    double best_action = 0;
    #pragma omp parallel for 
    for (int i = 1; i < this->N; i++){
        if (this->arms[i] > best){
            #pragma omp critical
            {
            best = this->arms[i];
            best_action = i;
            }
        }
    }
    return best_action;
}
