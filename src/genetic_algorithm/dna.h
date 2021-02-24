#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

#include "src/const.h"
#include "src/utils.h"

using namespace std;


class DNA {

public:
    DNA();
    DNA(int id); //first time (initializing DNA with random genes
    DNA(float *genes); // get from parameters dna after crossover and here we have to call mutation
    void setFitnessScore(float fitnessScore);
    // float fitnessFunction(float timeBeforeCrash, float distanceTraveledBeforeCrash);
    // vector<DNA> pickBestDNAs(vector<DNA> DNAs);
    // DNA crossover(vector<DNA> bestDNAs);
    // vector<DNA> mutation(DNA dna, int N_CARS);
    float *genes;
    int carID;
    float fitnessScore;
    

};