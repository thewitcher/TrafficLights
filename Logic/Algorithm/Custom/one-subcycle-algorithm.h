#ifndef ONESUBCYCLEALGORITHM_H
#define ONESUBCYCLEALGORITHM_H

#include "base-algorithm.h"

class OneSubcycleAlgorithm : public BaseAlgorithm
{
public:
    OneSubcycleAlgorithm();

    QVector<int> start( Junction* junction );
};

#endif // ONESUBCYCLEALGORITHM_H
