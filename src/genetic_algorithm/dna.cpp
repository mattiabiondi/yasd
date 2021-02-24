#include "dna.h"
// #include "src/utils.cpp"

DNA::DNA(){

}

DNA::DNA(int id) {
    this->carID = id;
    this->genes = new float[N_GENES];
    cout << "dna is: " << endl;
    for (int i = 0; i < N_GENES; i++) {
//        float gene = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float gene = getRandomFloat(1.0f, 0.1f);
        gene = getNumberWithOneDecimalDigit(gene);
        if(choose() == 1) gene *= -1;

        this->genes[i] = gene;
        cout << gene << "  ";
    }
    
    cout << endl;
}

DNA::DNA(float *genes) {
    this->genes = new float[N_GENES];
    for (int i = 0; i < N_GENES; i++) {
        this->genes[i] = genes[i];
    }
}

void DNA::setFitnessScore(float fitnessScore){
    this->fitnessScore = fitnessScore;
}


// float fitnessFunction(float timeBeforeCrash, float distanceTraveledBeforeCrash){
//     return timeBeforeCrash * 2 + distanceTraveledBeforeCrash; //da decidere insieme... al momento il tempo influisce per 2/3 e la distanza per 1/3
// }

// vector<DNA> pickDBestDNAs(vector<DNA> DNAs){
//     sort(DNAs.begin(),DNAs.end(), [](DNA a, DNA b){
//         return b.fitnessScore < a.fitnessScore;
//     });

//     vector<DNA> bestDNAs { DNAs[0], DNAs[1] };
//     return bestDNAs;

// }

// DNA crossover(vector<DNA> bestDNAs){
//     DNA firstParent = bestDNAs[0];
//     DNA secondParent = bestDNAs[1];
//     float *genes = new float[N_GENES];

//     for (int i = 0; i < N_GENES; ++i) {
//         int coin = rand() % 100;
//         switch(coin % 2){
//             case 0:
//                 genes[i] = firstParent.genes[i];
//                 break;
//             case 1:
//                 genes[i] = secondParent.genes[i];
//                 break;
//         }
//     }
//     DNA crossoveredDNA = DNA(genes);
//     return crossoveredDNA;

// }

// vector<DNA> mutation(DNA dna, int N_CARS){
//     vector<DNA> newGenerationDNAs;
//     for (int i = 0; i < N_CARS; i++) {

//         int maxProb = 100;
//         int minProb = 30;
//         int probability = rand() % maxProb;
//         DNA nthDNA = dna;
//         for (int j = 0; j < N_GENES; j++) {
//             if (probability > minProb) {
//                 nthDNA.genes[j] = getNumberWithOneDecimalDigit(getRandomFloat(1.0f, 0.1f));
//                 maxProb -= 2;
//                 minProb += rand() % 3;
//             }
//         }
//         newGenerationDNAs.push_back(nthDNA);
//     }
//     return newGenerationDNAs;
// }


    


