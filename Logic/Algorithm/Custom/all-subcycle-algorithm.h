#ifndef ALLSUBCYCLEALGORITHM_H
#define ALLSUBCYCLEALGORITHM_H

#include "base-algorithm.h"
#include "../Ui/TrafficLights_manager/vehicle-count-manager.h"

class AllSubcycleAlgorithm : public BaseAlgorithm
{
public:
    AllSubcycleAlgorithm();

    QVector<int> start( Junction* junction );

    QVector<int> evalForSimple( QVector<int> vector, Junction *junction );
    int theSumOfTheRemainingVehiclesAtJunction( const QVector<int> &vector, const int &numberOfVehiclesAtJunction, Junction *junction );
    int theSumOfTheRemainingVehiclesAtLane( VehicleCountManager::Lane, int subcycleId );
};

#endif // ALLSUBCYCLEALGORITHM_H
