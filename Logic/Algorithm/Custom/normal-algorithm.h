#ifndef NORMALALGORITHM_H
#define NORMALALGORITHM_H

#include "base-algorithm.h"

class NormalAlgorithm: public BaseAlgorithm
{
public:
    NormalAlgorithm();

    QVector<int> start( Junction* junction );
};

#endif // NORMALALGORITHM_H
