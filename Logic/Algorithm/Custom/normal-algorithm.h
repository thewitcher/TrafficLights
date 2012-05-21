#ifndef NORMALALGORITHM_H
#define NORMALALGORITHM_H

#include "base-algorithm.h"

class NormalAlgorithm: public BaseAlgorithm
{
public:
    NormalAlgorithm( Junction* junction, const QString& algorithmType );

    QVector<int> startAlgorithm();
};

#endif // NORMALALGORITHM_H
