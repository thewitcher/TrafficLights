#ifndef GENETICALGORITHMMANAGER_H
#define GENETICALGORITHMMANAGER_H

#include "GAGenome.h"
#include "genome-data.h"


class GeneticAlgorithmManager
{
public:
    GeneticAlgorithmManager();

    GAGenome start( GenomeData *dynamicGenomeData );

private:
    static unsigned int S_GENOME_SIZE;
    static float S_REPLACEMENT_PROBABILITY;
    static int S_POPULATION_SIZE;
    static int S_GENERATIONS;
    static int S_SCORE_FREQUENCY;
    static int S_FLUSH_FREQUENCY;
    static float S_MUTATION;
    static float S_CROSSOVER;
    static char* S_LOG_FILE;
};

#endif // GENETICALGORITHMMANAGER_H
