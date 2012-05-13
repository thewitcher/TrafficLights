#include "normal-algorithm.h"

NormalAlgorithm::NormalAlgorithm( Junction *junction ):
    BaseAlgorithm( junction, "NORMAL" )
{
}

QVector<int> NormalAlgorithm::startAlgorithm()
{
    QVector<int> vector;
    vector << 6000 << 6000 << 6000 << 6000;
    return vector;
}
