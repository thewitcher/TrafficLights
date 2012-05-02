#ifndef BASEALGORITHM_H
#define BASEALGORITHM_H

#include <QVector>

class Junction;

class BaseAlgorithm
{
public:
    BaseAlgorithm();

    virtual QVector<int> start( Junction* junction ) = 0;

private:
    const unsigned int m_genomeSize;
    const float m_replacementProbability;
    const int m_populationSize;
    const int m_generations;
    const int m_scoreFrequency;
    const int m_flushFrequency;
    const float m_mutation;
    const float m_crossover;
    const char* m_logFile;
};

#endif // BASEALGORITHM_H
