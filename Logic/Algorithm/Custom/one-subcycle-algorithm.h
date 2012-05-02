#ifndef ONESUBCYCLEALGORITHM_H
#define ONESUBCYCLEALGORITHM_H

#include "base-algorithm.h"
#include "../Ui/TrafficLights_manager/vehicle-count-manager.h"

class Junction;

class OneSubcycleAlgorithm : public BaseAlgorithm
{
public:
    OneSubcycleAlgorithm();

    QVector<int> start( Junction* junction );

    void clear();

    /// User data
    struct Data
    {
        VehicleCountManager::SubCycle subcycle;
        int greenLine;
    };

private:
    QVector<int> m_times;
    int m_wholeTime;

    VehicleCountManager::SubCycle chooseTheMostBlockSubcycleForBladzio( Junction* junction );
    VehicleCountManager::SubCycle chooseTheMostBlockSubcycleForSimple( Junction* junction );
    Data startBladzio( Junction* junction );
    Data startSimple( Junction* junction );
    int estimateGreenLight();
};

#endif // ONESUBCYCLEALGORITHM_H
