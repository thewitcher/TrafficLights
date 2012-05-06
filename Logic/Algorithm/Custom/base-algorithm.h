#ifndef BASEALGORITHM_H
#define BASEALGORITHM_H

#include <QVector>
#include <QThread>

class Junction;

class BaseAlgorithm: public QThread
{
public:
    BaseAlgorithm( Junction* junction );

    void run();
    const QVector<int>& timeVector() const;
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

    QVector<int> m_timeVector;
    Junction* m_junction;

    virtual QVector<int> startAlgorithm() = 0;
};

#endif // BASEALGORITHM_H
