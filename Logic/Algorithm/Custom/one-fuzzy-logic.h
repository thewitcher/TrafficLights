#ifndef ONEFUZZYLOGIC_H
#define ONEFUZZYLOGIC_H


#include "one-subcycle-algorithm.h"

class Junction;

class OneFuzzyLogic : public OneSubcycleAlgorithm
{
public:
    OneFuzzyLogic( Junction *junction, const QString& algorithmType );

protected:
    QVector<int> startAlgorithm();
    int estimateGreenLight();
};

#endif // ONEFUZZYLOGIC_H
