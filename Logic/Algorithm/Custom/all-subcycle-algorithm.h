#ifndef ALLSUBCYCLEALGORITHM_H
#define ALLSUBCYCLEALGORITHM_H

#include "base-algorithm.h"
#include "../Ui/TrafficLights_manager/vehicle-count-manager.h"

class Junction;
class GAGenome;

class AllSubcycleAlgorithm : public BaseAlgorithm
{
public:
    AllSubcycleAlgorithm( Junction* junction, const QString& algorithmType );

    QVector<int> startAlgorithm();
    /*! Objective function.*/
    void operationEval( float& score );

    /*! This function starts up genetic algorithm. As an argument assumes is population size. */
    QVector<int> setParameters();
    /*! Auxiliary functions for custom genetic algorithm.*/
    float evalForSimpleJunction();
    float evalForBladzioJunction();
    void evalForBladzioJunctionSubcycle_0( int& numberOfVehiclesThatWillDrive );
    void evalForBladzioJunctionSubcycle_1( int& numberOfVehiclesThatWillDrive );
    void evalForBladzioJunctionSubcycle_2( int& numberOfVehiclesThatWillDrive );
    void evalForBladzioJunctionSubcycle_3( int& numberOfVehiclesThatWillDrive );

    /*! Auxiliary fuctions for bladzioObjective function. */
    float theSumOfTheRemainingVehiclesAtJunction();
    int howMuchVehiclesAtLaneWillDrive( const int& subcycleId, const int& numberVehiclesOnLane );
    void setAlphaParam( const int& numberOfVehiclesThatWillDrive);
    float checkAllSubcycles( const int& vehiclesCountAtSubcycle, const int& time );

    /*! This function is calls, when traffic at junction is low. */
    QVector<int> normalTraffic();
    /*! Auxiliary functions for normalTraffic function.*/
    QVector<int> normalTrafficForBladzioJunction();
    QVector<int> normalTrafficForSimpleJunction();
    int maxTimeFromFourLanes( QList<VehicleCountManager::Lane>& list );
    int maxTimeFromTwoLanes( QList<VehicleCountManager::Lane>& list );

    QVector<int> m_timeVector;
    float m_totalTimes;
    float m_numberOfVehiclesThatWillDrive;
    int m_alpha;
    float m_magicE;

    void clearAll();
    bool firstRun;
    void exceptionForSimple( QVector<int>& vector );
    void exceptionForBladzio( QVector<int> &vector );


};

#endif // ALLSUBCYCLEALGORITHM_H
