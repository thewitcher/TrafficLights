#include "one-subcycle-algorithm.h"
#include "../Ui/TrafficLights_manager/vehicle-count-manager.h"
#include "QDebug"

OneSubcycleAlgorithm::OneSubcycleAlgorithm()
{
}

QVector<int> OneSubcycleAlgorithm::start( Junction* junction )
{
    switch( junction->junctionType() )
    {
    case Junction::BLADZIO:
        chooseTheMostBlockSubcycleForBladzio( junction );
        break;
    case Junction::SIMPLE:
//        chooseTheMostBlockSubcycleForSimple();
        break;
    default:
        break;
    }

    QVector<int> vector;
    vector << 5000 << 5000 << 5000 << 5000;
    return vector;
}


Junction::JUNCTION_TYPE OneSubcycleAlgorithm::chooseTheMostBlockSubcycleForBladzio( Junction *junction )
{
    int wholeTime = VehicleCountManager::wholeVehicleWaitingTimeForSubcycle( junction, VehicleCountManager::SUBCYCLE_0 )
                    + VehicleCountManager::wholeVehicleWaitingTimeForSubcycle( junction, VehicleCountManager::SUBCYCLE_1 )
                    + VehicleCountManager::wholeVehicleWaitingTimeForSubcycle( junction, VehicleCountManager::SUBCYCLE_2 )
                    + VehicleCountManager::wholeVehicleWaitingTimeForSubcycle( junction, VehicleCountManager::SUBCYCLE_3 );

    double ratio = 0;

    qDebug() << "Whole time: " << wholeTime;
}

Junction::JUNCTION_TYPE OneSubcycleAlgorithm::chooseTheMostBlockSubcycleForSimple( Junction *junction )
{

}
