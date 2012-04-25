#ifndef ALGORITHMMANAGER_H
#define ALGORITHMMANAGER_H

#include "base-algorithm.h"
#include <QVector>

class Junction;

class AlgorithmManager
{
public:
    AlgorithmManager( Junction* junction );
    ~AlgorithmManager();

    QVector<int> start();

private:
    BaseAlgorithm* m_baseAlgorithm;
    Junction* m_junction;

    void updateAlgorithm();
};

#endif // ALGORITHMMANAGER_H
