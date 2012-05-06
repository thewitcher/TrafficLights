#ifndef ONESUBCYCLEALGORITHM_H
#define ONESUBCYCLEALGORITHM_H

#include "base-algorithm.h"
#include "../Ui/TrafficLights_manager/vehicle-count-manager.h"

class Junction;

class OneSubcycleAlgorithm : public BaseAlgorithm
{
public:
    /// User data
    struct Data
    {
        VehicleCountManager::SubCycle subcycle;
        int greenTime;
    };

    OneSubcycleAlgorithm( Junction* junction );

    QVector<int> startAlgorithm();
    float ratio() const;
    Data data() const;

    void clear();

private:
    QVector<int> m_times;
    int m_wholeTime;
    float m_ratio;
    Data m_data;

    VehicleCountManager::SubCycle chooseTheMostBlockSubcycleForBladzio( Junction* junction );
    VehicleCountManager::SubCycle chooseTheMostBlockSubcycleForSimple( Junction* junction );
    void startBladzio( Junction* junction );
    void startSimple( Junction* junction );
    int estimateGreenLight();
};

#endif // ONESUBCYCLEALGORITHM_H
