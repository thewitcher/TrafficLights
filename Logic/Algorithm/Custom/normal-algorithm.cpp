#include "normal-algorithm.h"

NormalAlgorithm::NormalAlgorithm():
    BaseAlgorithm()
{
}

QVector<int> NormalAlgorithm::start()
{
    QVector<int> vector;
    vector << 5000 << 5000 << 5000 << 5000;
    return vector;
}
