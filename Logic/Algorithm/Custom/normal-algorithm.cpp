#include "normal-algorithm.h"

NormalAlgorithm::NormalAlgorithm( Junction *junction, const QString& algorithmType ):
    BaseAlgorithm( junction, algorithmType )
{
}

QVector<int> NormalAlgorithm::startAlgorithm()
{
    QVector<int> vector;
    vector << 6000 << 6000 << 6000 << 6000;
    return vector;
}
