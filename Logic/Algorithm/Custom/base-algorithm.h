#ifndef BASEALGORITHM_H
#define BASEALGORITHM_H

#include <QVector>


class BaseAlgorithm
{
public:
    BaseAlgorithm();

    virtual QVector<int> start() = 0;

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

#endif // BASEALGORITHM_H
