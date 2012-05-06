#ifndef BASEALGORITHM_H
#define BASEALGORITHM_H

#include <QVector>
#include <QThread>

class Junction;

class BaseAlgorithm
{
public:
    BaseAlgorithm( Junction* junction );

    void start();
    Junction* junction();

protected:
    const unsigned int m_genomeSize;
    const float m_replacementProbability;
    const int m_populationSize;
    const int m_generations;
    const int m_scoreFrequency;
    const int m_flushFrequency;
    const float m_mutation;
    const float m_crossover;
    const char* m_logFile;

    virtual QVector<int> startAlgorithm() = 0;

    Junction* m_junction;
};

#endif // BASEALGORITHM_H
