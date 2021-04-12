#include "dna.h"
// #include "src/utils.cpp"

DNA::DNA()
{
}

DNA::DNA(int id)
{
	this->carID = id;
	this->genes = new double[N_GENES];

	// [DEBUG] Print DNA sequence
	//cout << "------------------DNA-------------------" << endl;

	for (int i = 0; i < N_GENES; i++) {
//        double gene = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
		double gene = getRandomDouble(1.0f, 0.1f);
		gene = getNumberWithOneDecimalDigit(gene);
		if (choose() == 1) gene *= -1;

		this->genes[i] = gene;

		// [DEBUG] Print DNA sequence
		//cout << gene << "  ";
	}

	// [DEBUG] End DNA sequence printing
	//cout << endl
	//cout << "----------------------------------------" << endl;
}

DNA::DNA(double *genes)
{
	this->genes = new double[N_GENES];
	for (int i = 0; i < N_GENES; i++)
		this->genes[i] = genes[i];
}

void DNA::setFitnessScore(double fitnessScore)
{
	this->fitnessScore = fitnessScore;
}

double DNA::getFitnessScore(){
	return this->fitnessScore;
}


// double fitnessFunction(double timeBeforeCrash, double distanceTraveledBeforeCrash){
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
//     double *genes = new double[N_GENES];

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
//                 nthDNA.genes[j] = getNumberWithOneDecimalDigit(getRandomDouble(1.0f, 0.1f));
//                 maxProb -= 2;
//                 minProb += rand() % 3;
//             }
//         }
//         newGenerationDNAs.push_back(nthDNA);
//     }
//     return newGenerationDNAs;
// }
