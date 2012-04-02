#ifndef GENETICALGORITHMMANAGER_H
#define GENETICALGORITHMMANAGER_H

#include "GAGenome.h"

class GeneticAlgorithmManager
{
public:
    GeneticAlgorithmManager();

private:
    static unsigned int S_GENOME_SIZE;
    static int S_PARALLEL_POPULATIONS;
    static int S_POPULATION_SIZE;
    static int S_GENERATIONS;
    static float S_MUTATION;
    static float S_CROSSOVER;
};

#endif // GENETICALGORITHMMANAGER_H
