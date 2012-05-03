#include "all-subcycle-algorithm.h"
#include "../Ui/TrafficLights_manager/junction.h"
//#include "../Ui/TrafficLights_manager/vehicle-count-manager.h"
#include <cmath>

AllSubcycleAlgorithm::AllSubcycleAlgorithm( Junction *junction ):
    BaseAlgorithm( junction ),
    m_numberOfVehiclesThatWillDrive( 0 ),
    m_alpha( 0 ),
    m_magicE( 0 )
{}

QVector<int> AllSubcycleAlgorithm::startAlgorithm()
{
    QVector<int> timeVector;
    switch( m_junction->junctionType() )
    {
    case Junction::BLADZIO:
        break;
    case Junction::SIMPLE:
//        timeVector = evalForSimple();
        break;
    default:
        break;
    }

    return timeVector;
}

int AllSubcycleAlgorithm::objective( QVector<int> vector, Junction *junction )
{
    float currentScore = 0.0;
    m_timeVector = vector;
    int countOfVehiclesRemainingAtJunction = theSumOfTheRemainingVehiclesAtJunction( junction );

    for( int i = 0; i < vector.size(); i++ )
    {
        m_totalTimes += vector.at( i );
    }

    currentScore = ((((( m_numberOfVehiclesThatWillDrive / m_totalTimes ) * 1000) -
            countOfVehiclesRemainingAtJunction ) * exp( m_alpha ) ) + m_magicE );

    return currentScore;
}

int AllSubcycleAlgorithm::theSumOfTheRemainingVehiclesAtJunction( Junction *junction  )
{
   int score = 0;

   if( junction->id() != 2 )
       m_numberOfVehiclesThatWillDrive = evalForSimpleJunction( junction );
   else
       m_numberOfVehiclesThatWillDrive = evalForBladzioJunction( junction );


   score = junction->currentNumberOfVehicles() - m_numberOfVehiclesThatWillDrive;

   setAlphaParam( m_numberOfVehiclesThatWillDrive, junction );

   return score;
}

int AllSubcycleAlgorithm::evalForSimpleJunction( const Junction *junction )
{
    int numberOfVehiclesThatWillDrive = 0;

    /* SouthLeft */
    int numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( junction, VehicleCountManager::SOUTH_LEFT );
    numberOfVehiclesThatWillDrive += howMuchVehiclesAtLaneWillDrive( 0, numberVehiclesOnLane );

    /* SouthRight */
    numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( junction, VehicleCountManager::SOUTH_RIGHT );
    numberOfVehiclesThatWillDrive += howMuchVehiclesAtLaneWillDrive( 0, numberVehiclesOnLane );
    m_magicE = checkAllSubcycles( numberVehiclesOnLane, m_timeVector.at( 0 ) );

    /* EastMiddle */
    numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( junction, VehicleCountManager::EAST_MIDDLE );
    numberOfVehiclesThatWillDrive += howMuchVehiclesAtLaneWillDrive( 1, numberVehiclesOnLane );
    m_magicE += checkAllSubcycles( numberVehiclesOnLane, m_timeVector.at( 1 ) );

    /* WestMiddle */
    numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( junction, VehicleCountManager::WEST_MIDDLE );
    numberOfVehiclesThatWillDrive += howMuchVehiclesAtLaneWillDrive( 2, numberVehiclesOnLane );
    m_magicE += checkAllSubcycles( numberVehiclesOnLane, m_timeVector.at( 2 ) );

    return numberOfVehiclesThatWillDrive;
}

int AllSubcycleAlgorithm::evalForBladzioJunction( const Junction *junction )
{
    int numberOfVehiclesThatWillDrive = 0;

    /* Subcycle 0 */
    evalForBladzioJunctionSubcycle_0( junction, numberOfVehiclesThatWillDrive );

    /* Subcycle 1 */
    evalForBladzioJunctionSubcycle_1( junction, numberOfVehiclesThatWillDrive );

    /* Subcycle 2 */
    evalForBladzioJunctionSubcycle_2( junction, numberOfVehiclesThatWillDrive );

    /* Subcycle 3 */
    evalForBladzioJunctionSubcycle_3( junction, numberOfVehiclesThatWillDrive );

    return numberOfVehiclesThatWillDrive;
}

void AllSubcycleAlgorithm::evalForBladzioJunctionSubcycle_0( const Junction *junction,int& numberOfVehiclesThatWillDrive )
{
    /* South subcycle 0 */
    int numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( junction, VehicleCountManager::SOUTH_MIDDLE );
    numberOfVehiclesThatWillDrive += howMuchVehiclesAtLaneWillDrive( 0, numberVehiclesOnLane );

    numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( junction, VehicleCountManager::SOUTH_RIGHT );
    numberOfVehiclesThatWillDrive += howMuchVehiclesAtLaneWillDrive( 0, numberVehiclesOnLane );

    /* North subcycle 0 */
    numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( junction, VehicleCountManager::NORTH_MIDDLE );
    numberOfVehiclesThatWillDrive += howMuchVehiclesAtLaneWillDrive( 0, numberVehiclesOnLane );

    numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( junction, VehicleCountManager::NORTH_LEFT );
    numberOfVehiclesThatWillDrive += howMuchVehiclesAtLaneWillDrive( 0, numberVehiclesOnLane );

    m_magicE = checkAllSubcycles( numberVehiclesOnLane, m_timeVector.at( 0 ) );
}

void AllSubcycleAlgorithm::evalForBladzioJunctionSubcycle_1( const Junction *junction, int& numberOfVehiclesThatWillDrive )
{
    /* South subcycle 1 */
    int numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( junction, VehicleCountManager::SOUTH_LEFT );
    numberOfVehiclesThatWillDrive += howMuchVehiclesAtLaneWillDrive( 1, numberVehiclesOnLane );

    /* North subcycle 1 */
    numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( junction, VehicleCountManager::NORTH_RIGHT );
    numberOfVehiclesThatWillDrive += howMuchVehiclesAtLaneWillDrive( 1, numberVehiclesOnLane );
    m_magicE = checkAllSubcycles( numberVehiclesOnLane, m_timeVector.at( 1 ) );
}

void AllSubcycleAlgorithm::evalForBladzioJunctionSubcycle_2( const Junction *junction, int& numberOfVehiclesThatWillDrive )
{
    /* West subcycle 2 */
    int numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( junction, VehicleCountManager::WEST_MIDDLE );
    numberOfVehiclesThatWillDrive += howMuchVehiclesAtLaneWillDrive( 2, numberVehiclesOnLane );

    numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( junction, VehicleCountManager::WEST_BOTTOM );
    numberOfVehiclesThatWillDrive += howMuchVehiclesAtLaneWillDrive( 2, numberVehiclesOnLane );

    /* East subcycle 2 */
    numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( junction, VehicleCountManager::EAST_MIDDLE );
    numberOfVehiclesThatWillDrive += howMuchVehiclesAtLaneWillDrive( 2, numberVehiclesOnLane );

    numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( junction, VehicleCountManager::EAST_TOP );
    numberOfVehiclesThatWillDrive += howMuchVehiclesAtLaneWillDrive( 2, numberVehiclesOnLane );
    m_magicE = checkAllSubcycles( numberVehiclesOnLane, m_timeVector.at( 2 ) );
}

void AllSubcycleAlgorithm::evalForBladzioJunctionSubcycle_3( const Junction *junction, int& numberOfVehiclesThatWillDrive )
{
    /* West subcycle 3 */
    int numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( junction, VehicleCountManager::WEST_TOP );
    numberOfVehiclesThatWillDrive += howMuchVehiclesAtLaneWillDrive( 3, numberVehiclesOnLane );

    /* East subcycle 3 */
    numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( junction, VehicleCountManager::EAST_BOTTOM );
    numberOfVehiclesThatWillDrive += howMuchVehiclesAtLaneWillDrive( 3, numberVehiclesOnLane );
    m_magicE = checkAllSubcycles( numberVehiclesOnLane, m_timeVector.at( 3 ) );
}

int AllSubcycleAlgorithm::howMuchVehiclesAtLaneWillDrive( const int &subcycleId, const int& numberVehiclesOnLane )
{
    int score = 0;
    if( numberVehiclesOnLane <= m_timeVector.at( subcycleId ) )
    {
        score = numberVehiclesOnLane;
    }
    else{
        score = m_timeVector.at( subcycleId );
    }
    return score;
}

void AllSubcycleAlgorithm::setAlphaParam( const int& numberOfVehiclesThatWillDrive, Junction * junction )
{
    int minValue = junction->currentNumberOfVehicles() * 0.7;
    int maxValue = junction->currentNumberOfVehicles() * 0.8;

    if( numberOfVehiclesThatWillDrive >= minValue || numberOfVehiclesThatWillDrive <= maxValue )
        m_alpha = 1;
    else
        m_alpha = 0;
}

int AllSubcycleAlgorithm::checkAllSubcycles( const int& vehiclesCountAtSubcycle, const int& time )
{
    if( vehiclesCountAtSubcycle > 0 && time > 0 )
    {
        return 100;
    }
    else if( vehiclesCountAtSubcycle > 0 && time == 0 )
    {
        return -100;
    }
    else if( vehiclesCountAtSubcycle == 0 && time > 0 )
    {
        return -100;
    }
    else if( vehiclesCountAtSubcycle == 0 && time == 0 )
    {
        return 100;
    }

    return 0;
}
