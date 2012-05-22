#ifndef ONESUBCYCLEALGORITHM_H
#define ONESUBCYCLEALGORITHM_H

#include "base-algorithm.h"
#include "../Ui/TrafficLights_manager/vehicle-count-manager.h"

class Junction;
class GAGenome;

class OneSubcycleAlgorithm : public BaseAlgorithm
{
public:
    OneSubcycleAlgorithm( Junction* junction, const QString& algorithmType );

protected:
    VehicleCountManager::SubCycle m_currentSubcycle;
    QVector<int> m_vehicleCountOnSubcycle;
    bool m_firstRun;
    int m_vehicleCount;
    static float S_MIN;
    static float S_MAX;
    static float S_PASS_RATE;

    virtual void chooseTheMostBlockSubcycleForBladzio();
    virtual void chooseTheMostBlockSubcycleForSimple();
    virtual void loadDataForBladzio();
    virtual void loadDataForSimple();
    int estimateGreenLight();
    virtual QVector<int> startAlgorithm();

    friend float objective( GAGenome& genome );
};

#endif // ONESUBCYCLEALGORITHM_H
