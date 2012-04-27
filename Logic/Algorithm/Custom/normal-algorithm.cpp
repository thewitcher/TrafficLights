#include "normal-algorithm.h"

NormalAlgorithm::NormalAlgorithm():
    BaseAlgorithm()
{
}

QVector<int> NormalAlgorithm::start( Junction* junction )
{
    Q_UNUSED( junction );

    QVector<int> vector;
    vector << 6000 << 6000 << 6000 << 6000;
    return vector;
}
