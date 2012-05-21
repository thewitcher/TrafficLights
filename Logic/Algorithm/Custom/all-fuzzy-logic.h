#ifndef ALLFUZZYLOGIC_H
#define ALLFUZZYLOGIC_H

#include "base-algorithm.h"

class Junction;

class AllFuzzyLogic : public BaseAlgorithm
{
public:
    AllFuzzyLogic( Junction *junction, const QString& algorithmType );
    QVector<int> startAlgorithm();
};

#endif // ALLFUZZYLOGIC_H
