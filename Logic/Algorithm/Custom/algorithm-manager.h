#ifndef ALGORITHMMANAGER_H
#define ALGORITHMMANAGER_H

#include "base-algorithm.h"
#include <QVector>

class AlgorithmManager
{
public:
    AlgorithmManager();
    ~AlgorithmManager();

    QVector<int> start();

private:
    BaseAlgorithm* m_baseAlgorithm;

    void updateAlgorithm();
};

#endif // ALGORITHMMANAGER_H
