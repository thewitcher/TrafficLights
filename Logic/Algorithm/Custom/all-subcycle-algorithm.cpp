#include "all-subcycle-algorithm.h"
#include "../Ui/TrafficLights_manager/junction.h"
//#include "../Ui/TrafficLights_manager/vehicle-count-manager.h"
#include "genetic-algorithm-functions.h"

AllSubcycleAlgorithm::AllSubcycleAlgorithm()
{
}

QVector<int> AllSubcycleAlgorithm::start( Junction *junction )
{
    QVector<int> timeVector;
    switch( junction->junctionType() )
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

int AllSubcycleAlgorithm::evalForSimple( QVector<int> vector, Junction *junction )
{
    int currentScore = 0;
    int numberOfVehiclesAtJunction = junction->currentNumberOfVehicles();
    int totalTimes;

    for( int i = 0; i < vector.size(); i++ )
    {
        totalTimes += vector.at( i );
    }

    currentScore = ( numberOfVehiclesAtJunction / totalTimes ) * 1000;

    return currentScore;
}

int AllSubcycleAlgorithm::theSumOfTheRemainingVehiclesAtJunction( const QVector<int> &vector, const int &numberOfVehiclesAtJunction, Junction *junction  )
{
    Q_UNUSED( vector );
    Q_UNUSED( numberOfVehiclesAtJunction );
//   int numberOfVehiclesThatWillDrive = 0;

   //SouthLeft
//   int numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( junction->m_vehicleCountOnLanes, VehicleCountManager::SOUTH_LEFT, junction->m_junctionId );
//   if( numberVehiclesOnLane <= vector.at( 0 ) )
//   {
//       numberOfVehiclesThatWillDrive = numberVehiclesOnLane;
//   }
//   else{
//       numberOfVehiclesThatWillDrive = vector.at( 0 );
//   }

//   //SouthRight
//   numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( junction->m_vehicleCountOnLanes, VehicleCountManager::SOUTH_RIGHT, junction->m_junctionId );
//   if( numberVehiclesOnLane <= vector.at( 0 ) )
//   {
//       numberOfVehiclesThatWillDrive = numberVehiclesOnLane;
//   }
//   else{
//       numberOfVehiclesThatWillDrive = vector.at( 0 );
//   }

//   //EastMiddle
//   numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( junction->m_vehicleCountOnLanes, VehicleCountManager::EAST_MIDDLE, junction->m_junctionId );
//   if( numberVehiclesOnLane <= vector.at( 1 ) )
//   {
//       numberOfVehiclesThatWillDrive = numberVehiclesOnLane;
//   }
//   else{
//       numberOfVehiclesThatWillDrive = vector.at( 1 );
//   }

//   //WestMiddle
//   numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( junction->m_vehicleCountOnLanes, VehicleCountManager::WEST_MIDDLE, junction->m_junctionId );
//   if( numberVehiclesOnLane <= vector.at( 2 ) )
//   {
//       numberOfVehiclesThatWillDrive = numberVehiclesOnLane;
//   }
//   else{
//       numberOfVehiclesThatWillDrive = vector.at( 2 );
//   }
    return 3; // zmienic
}

int AllSubcycleAlgorithm::theSumOfTheRemainingVehiclesAtLane( VehicleCountManager::Lane, int subcycleId )
{
    Q_UNUSED( subcycleId );
    return 3; // zmienic
}
