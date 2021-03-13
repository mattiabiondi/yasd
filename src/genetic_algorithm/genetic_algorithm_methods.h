double fitnessFunction(double timeBeforeCrash, double distanceTraveledBeforeCrash);
vector<DNA> pickBestDNAs(vector<DNA> DNAs);
DNA crossover(vector<DNA> bestDNAs);
vector<DNA> mutation(DNA dna, int N_CARS);
