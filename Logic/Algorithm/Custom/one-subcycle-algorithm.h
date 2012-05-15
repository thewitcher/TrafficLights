#ifndef ONESUBCYCLEALGORITHM_H
#define ONESUBCYCLEALGORITHM_H

#include "base-algorithm.h"
#include "../Ui/TrafficLights_manager/vehicle-count-manager.h"

class Junction;
class GAGenome;

class OneSubcycleAlgorithm : public BaseAlgorithm
{
public:
    OneSubcycleAlgorithm( Junction* junction );

private:
    VehicleCountManager::SubCycle m_currentSubcycle;
    QVector<int> m_vehicleCountOnSubcycle;
    bool m_firstRun;
    int m_vehicleCount;
    static float S_MIN;
    static float S_MAX;
    static float S_PASS_RATE;

    void chooseTheMostBlockSubcycleForBladzio();
    void chooseTheMostBlockSubcycleForSimple();
    void loadDataForBladzio();
    void loadDataForSimple();
    int estimateGreenLight();
    QVector<int> startAlgorithm();

    friend float objective( GAGenome& genome );
};

#endif // ONESUBCYCLEALGORITHM_H
