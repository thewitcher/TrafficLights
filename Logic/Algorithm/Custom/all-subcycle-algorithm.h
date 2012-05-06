#ifndef ALLSUBCYCLEALGORITHM_H
#define ALLSUBCYCLEALGORITHM_H

#include "base-algorithm.h"
//#include "../Ui/TrafficLights_manager/vehicle-count-manager.h"

class Junction;
class GAGenome;
class UserPackage;
class AllSubcycleAlgorithm : public BaseAlgorithm
{
public:
    AllSubcycleAlgorithm( Junction* junction );

    QVector<int> startAlgorithm();

    int theSumOfTheRemainingVehiclesAtJunction( Junction *junction );
    int howMuchVehiclesAtLaneWillDrive( const int& subcycleId, const int& numberVehiclesOnLane );
    void setAlphaParam( const int& numberOfVehiclesThatWillDrive, Junction * junction );
    int checkAllSubcycles( const int& vehiclesCountAtSubcycle, const int& time );

    QVector<int> m_timeVector;
    float m_totalTimes;
    float m_numberOfVehiclesThatWillDrive;
    int m_alpha;
    int m_magicE;

    void clearAll();

    QVector<int> setParameters( int size, UserPackage* userPackage );

    int evalForSimpleJunction( const Junction *junction );
    int evalForBladzioJunction( const Junction *junction );
    void evalForBladzioJunctionSubcycle_0( const Junction *junction, int& numberOfVehiclesThatWillDrive );
    void evalForBladzioJunctionSubcycle_1( const Junction *junction, int& numberOfVehiclesThatWillDrive );
    void evalForBladzioJunctionSubcycle_2( const Junction *junction, int& numberOfVehiclesThatWillDrive );
    void evalForBladzioJunctionSubcycle_3( const Junction *junction, int& numberOfVehiclesThatWillDrive );
};

#endif // ALLSUBCYCLEALGORITHM_H
