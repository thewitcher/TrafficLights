#ifndef ONESUBCYCLEALGORITHM_H
#define ONESUBCYCLEALGORITHM_H

#include "base-algorithm.h"
#include "../Ui/TrafficLights_manager/junction.h"

class OneSubcycleAlgorithm : public BaseAlgorithm
{
public:
    OneSubcycleAlgorithm();

    QVector<int> start( Junction* junction );

private:
    Junction::JUNCTION_TYPE chooseTheMostBlockSubcycleForBladzio( Junction* junction );
    Junction::JUNCTION_TYPE chooseTheMostBlockSubcycleForSimple( Junction* junction );
};

#endif // ONESUBCYCLEALGORITHM_H
