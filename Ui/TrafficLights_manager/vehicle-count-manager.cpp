#include "vehicle-count-manager.h"
#include "../../Logger/logger.h"
#include "../Ui/TrafficLights_manager/junction.h"

int VehicleCountManager::vehicleCountOnSubcycle( const Junction* junction, SubCycle subcycle )
{
    int count = 0;

    if( junction->junctionType() != Junction::BLADZIO )
    {
        count = vehicleCountOnSubcycleForSimpleJunction( junction, subcycle );
    }
    else
    {
        count = vehicleCountOnSubcycleForBladzioJunction( junction, subcycle );
    }

    return count;
}

int VehicleCountManager::vehicleCountOnRestSubcycle( const Junction *junction, SubCycle subcycle )
{
    int count = 0;

    if( junction->junctionType() != Junction::BLADZIO )
    {
        switch( subcycle )
        {
        case SUBCYCLE_0:
            count = vehicleCountOnSubcycleForSimpleJunction( junction, SUBCYCLE_1 )
                    + vehicleCountOnSubcycleForSimpleJunction( junction, SUBCYCLE_2 );
            break;
        case SUBCYCLE_1:
            count = vehicleCountOnSubcycleForSimpleJunction( junction, SUBCYCLE_0 )
                    + vehicleCountOnSubcycleForSimpleJunction( junction, SUBCYCLE_2 );
            break;
        case SUBCYCLE_2:
            count = vehicleCountOnSubcycleForSimpleJunction( junction, SUBCYCLE_0 )
                    + vehicleCountOnSubcycleForSimpleJunction( junction, SUBCYCLE_1 );
            break;
        default:
            LOG_INFO( "Wrong subcycle: %i", subcycle );
            break;
        }
    }
    else
    {
        switch( subcycle )
        {
        case SUBCYCLE_0:
            count = vehicleCountOnSubcycleForSimpleJunction( junction, SUBCYCLE_1 )
                    + vehicleCountOnSubcycleForSimpleJunction( junction, SUBCYCLE_2 )
                    + vehicleCountOnSubcycleForSimpleJunction( junction, SUBCYCLE_3 );
            break;
        case SUBCYCLE_1:
            count = vehicleCountOnSubcycleForSimpleJunction( junction, SUBCYCLE_0 )
                    + vehicleCountOnSubcycleForSimpleJunction( junction, SUBCYCLE_2 )
                    + vehicleCountOnSubcycleForSimpleJunction( junction, SUBCYCLE_3 );
            break;
        case SUBCYCLE_2:
            count = vehicleCountOnSubcycleForSimpleJunction( junction, SUBCYCLE_0 )
                    + vehicleCountOnSubcycleForSimpleJunction( junction, SUBCYCLE_1 )
                    + vehicleCountOnSubcycleForSimpleJunction( junction, SUBCYCLE_3 );
            break;
        case SUBCYCLE_3:
            count = vehicleCountOnSubcycleForSimpleJunction( junction, SUBCYCLE_0 )
                    + vehicleCountOnSubcycleForSimpleJunction( junction, SUBCYCLE_1 )
                    + vehicleCountOnSubcycleForSimpleJunction( junction, SUBCYCLE_2 );
            break;
        default:
            LOG_INFO( "Wrong subcycle: %i", subcycle );
            break;
        }
    }

    return count;
}

float VehicleCountManager::averageVehicleWaitingTimeOnSubcycle( const Junction *junction, SubCycle subcycle )
{
    float wholeWaitingTime = wholeVehicleWaitingTimeForSubcycle( junction, subcycle );
    int vehicleCount = vehicleCountOnSubcycle( junction, subcycle );

    if( vehicleCount == 0 )
    {
        return 0;
    }

    return ( wholeWaitingTime / vehicleCount );
}

int VehicleCountManager::vehicleCountOnSubcycleForSimpleJunction( const Junction* junction, SubCycle subcycle )
{
    int count = 0;
    switch( subcycle )
    {
    case SUBCYCLE_0:
        count = vehicleCountOnLane( junction, SOUTH_LEFT ) + vehicleCountOnLane( junction, SOUTH_RIGHT );
        break;
    case SUBCYCLE_1:
        count = vehicleCountOnLane( junction, EAST_MIDDLE );
        break;
    case SUBCYCLE_2:
        count = vehicleCountOnLane( junction, WEST_MIDDLE );
        break;
    default:
        LOG_WARNING( "There is no junction with %i id", junction->id() );
        break;
    }
    return count;
}

int VehicleCountManager::vehicleCountOnSubcycleForBladzioJunction( const Junction* junction, SubCycle subcycle )
{
    int count = 0;
    switch( subcycle )
    {
    case SUBCYCLE_0:
        count = vehicleCountOnLane( junction, SOUTH_MIDDLE ) + vehicleCountOnLane( junction, SOUTH_RIGHT ) +
                vehicleCountOnLane( junction, NORTH_MIDDLE ) + vehicleCountOnLane( junction, NORTH_LEFT );
        break;
    case SUBCYCLE_1:
        count = vehicleCountOnLane( junction, SOUTH_LEFT ) + vehicleCountOnLane( junction, NORTH_RIGHT );
        break;
    case SUBCYCLE_2:
        count = vehicleCountOnLane( junction, WEST_MIDDLE ) + vehicleCountOnLane( junction, WEST_BOTTOM ) +
                vehicleCountOnLane( junction, EAST_MIDDLE ) + vehicleCountOnLane( junction, EAST_TOP );
        break;
    case SUBCYCLE_3:
        count = vehicleCountOnLane( junction, WEST_TOP ) + vehicleCountOnLane( junction, EAST_BOTTOM );
        break;
    default:
        LOG_WARNING( "There is no junction with %i id", junction->id() );
        break;
    }
    return count;
}

int VehicleCountManager::wholeVehicleWaitingTimeForSubcycle( const Junction* junction, SubCycle subcycle )
{
    int count = 0;
    if( junction->id() != 2 )
    {
        count = wholeVehicleWaitingTimeForSimpleJunction( junction, subcycle );
    }
    else{
        count = wholeVehicleWaitingTimeForBladzioJunction( junction, subcycle );
    }
    return count;
}

int VehicleCountManager::wholeVehicleWaitingTimeForSimpleJunction( const Junction* junction, SubCycle subcycle )
{
    int count = 0;
    switch( subcycle )
    {
    case SUBCYCLE_0:
        count = wholeVehicleWaitingTimeOnLane( junction, SOUTH_LEFT ) +
                wholeVehicleWaitingTimeOnLane( junction, SOUTH_RIGHT );
        break;
    case SUBCYCLE_1:
        count = wholeVehicleWaitingTimeOnLane( junction, EAST_MIDDLE );
        break;
    case SUBCYCLE_2:
        count = wholeVehicleWaitingTimeOnLane( junction, WEST_MIDDLE );
        break;
    default:
        LOG_WARNING( "There is no junction with %i id", junction->id() );
        break;
    }
    return count;
}

int VehicleCountManager::wholeVehicleWaitingTimeForBladzioJunction( const Junction* junction, SubCycle subcycle )
{
    int count = 0;
    switch( subcycle )
    {
    case SUBCYCLE_0:
        count = wholeVehicleWaitingTimeOnLane( junction, SOUTH_MIDDLE ) +
                wholeVehicleWaitingTimeOnLane( junction, SOUTH_RIGHT ) +
                wholeVehicleWaitingTimeOnLane( junction, NORTH_MIDDLE ) +
                wholeVehicleWaitingTimeOnLane( junction, NORTH_LEFT );
        break;
    case SUBCYCLE_1:
        count = wholeVehicleWaitingTimeOnLane( junction, SOUTH_LEFT ) +
                wholeVehicleWaitingTimeOnLane( junction, NORTH_RIGHT );
        break;
    case SUBCYCLE_2:
        count = wholeVehicleWaitingTimeOnLane( junction, WEST_MIDDLE ) +
                wholeVehicleWaitingTimeOnLane( junction, WEST_BOTTOM ) +
                wholeVehicleWaitingTimeOnLane( junction, EAST_MIDDLE ) +
                wholeVehicleWaitingTimeOnLane( junction, EAST_TOP );
        break;
    case SUBCYCLE_3:
        count = wholeVehicleWaitingTimeOnLane( junction, WEST_TOP ) +
                wholeVehicleWaitingTimeOnLane( junction, EAST_BOTTOM );
        break;
    default:
        LOG_WARNING( "There is no junction with %i id", junction->id() );
        break;
    }
    return count;
}

int VehicleCountManager::vehicleCountOnLane( const Junction* junction, Lane lane )
{
    int count = 0;

    switch( junction->id() )
    {
    case 0:
        count = vehicleCountOnLane0( junction->vehicleCountOnLanes(), lane );
        break;
    case 1:
        count = vehicleCountOnLane1( junction->vehicleCountOnLanes(), lane );
        break;
    case 2:
        count = vehicleCountOnLane2( junction->vehicleCountOnLanes(), lane );
        break;
    case 3:
        count = vehicleCountOnLane3( junction->vehicleCountOnLanes(), lane );
        break;
    case 4:
        count = vehicleCountOnLane4( junction->vehicleCountOnLanes(), lane );
        break;
    case 5:
        count = vehicleCountOnLane5( junction->vehicleCountOnLanes(), lane );
        break;
    case 6:
        count = vehicleCountOnLane6( junction->vehicleCountOnLanes(), lane );
        break;
    default:
        LOG_WARNING( "There is no junction with %i id", junction->id() );
        break;
    }
      return count;
}

int VehicleCountManager::sumVehiclesAtJunction( const Junction *junction )
{
    int score = 0;
    QList<SubCycle> list;

    if( junction->id() != 2 )
    {
        list << SUBCYCLE_0 << SUBCYCLE_1 << SUBCYCLE_2;
        for( int i = 0; i < list.size(); i++ )
        {
            score += vehicleCountOnSubcycleForSimpleJunction( junction, list.at( i ) );
        }
    }
    else
    {
        list << SUBCYCLE_0 << SUBCYCLE_1 << SUBCYCLE_2 << SUBCYCLE_3;
        for( int i = 0; i < list.size(); i++ )
        {
            score += vehicleCountOnSubcycleForBladzioJunction( junction, list.at( i ) );
//            qDebug() << "score: " << score << ", junctionId: " << junction->id();
        }
    }

    return score;
}

/*!
 * Undermentioned static methods return number of vehicles on lane. To more clarify like these methods work
 * I describe all of junctions:
 *
 * Junction with id = 0
 * We have four lanes:
 * - WEST_MIDDLE - checkpoints: 6
 * - EAST_MIDDLE - checkpoints: 107
 * - SOUTH_LEFT - checkpoints: 38
 * - SOUTH_RIGHT - checkpoints: 48
 *
 * Junction with id = 1
 * We have four lanes:
 * - NORTH_MIDDLE - checkpoints: 0
 * - SOUTH_MIDDLE - checkpoints: 11
 * - EAST_TOP - checkpoints: 20
 * - EAST_BOTTOM - checkpoints: 21
 *
 * Junction with id = 2
 * We have four lanes:
 * - WEST_TOP - checkpoints: 2, 8
 * - WEST_MIDDLE - checkpoints: 3, 9
 * - WEST_BOTTOM - checkpoints: 4, 10
 * - EAST_TOP - checkpoints: 119
 * - EAST_MIDDLE - checkpoints: 102
 * - EAST_BOTTOM - checkpoints: 104
 * - NORTH_LEFT - checkpoints: 17, 18
 * - NORTH_MIDDLE - checkpoints: 26, 27
 * - NORTH_RIGHT - checkpoints: 32, 33
 * - SOUTH_LEFT - checkpoints: 42, 43
 * - SOUTH_MIDDLE - checkpoints: 45, 44
 * - SOUTH_RIGHT - checkpoints: 53, 54
 *
 * Junction with id = 3
 * We have four lanes:
 * - WEST_MIDDLE - checkpoints: 5
 * - EAST_MIDDLE - checkpoints: 101
 * - NORTH_LEFT - checkpoints: 23
 * - NORTH_RIGHT - checkpoints: 29
 *
 * Junction with id = 4
 * We have four lanes:
 * - WEST_MIDDLE - checkpoints: 100
 * - EAST_MIDDLE - checkpoints: 72
 * - NORTH_LEFT - checkpoints: 90
 * - NORTH_RIGHT - checkpoints: 103
 *
 * Junction with id = 5
 * We have four lanes:
 * - NORTH_MIDDLE - checkpoints: 81
 * - SOUTH_MIDDLE - checkpoints: 71
 * - WEST_TOP - checkpoints: 105
 * - WEST_BOTTOM - checkpoints: 108
 *
 * Junction with id = 6
 * We have four lanes:
 * - WEST_MIDDLE - checkpoints: 82
 * - EAST_MIDDLE - checkpoints: 139
 * - SOUTH_LEFT - checkpoints: 106
 * - SOUTH_RIGHT - checkpoints: 121
 */
int VehicleCountManager::vehicleCountOnLane0( const QHash<int, int> &vehicleCountLanes, Lane lane )
{
    int count = 0;

    switch( lane )
    {
    case WEST_MIDDLE:
        count = vehicleCountLanes.value( 6 );
        break;
    case EAST_MIDDLE:
        count = vehicleCountLanes.value( 107 );
        break;
    case SOUTH_LEFT:
        count = vehicleCountLanes.value( 38 );
        break;
    case SOUTH_RIGHT:
        count = vehicleCountLanes.value( 48 );
        break;
    default:
        LOG_WARNING( "Wrong lane (%i) for this junction (id = 0)", lane );
        break;
    }

    return count;
}

int VehicleCountManager::vehicleCountOnLane1( const QHash<int, int> &vehicleCountLanes, Lane lane )
{
    int count = 0;

    switch( lane )
    {
    case EAST_MIDDLE:
        count = vehicleCountLanes.value( 0 );
        break;
    case WEST_MIDDLE:
        count = vehicleCountLanes.value( 11 );
        break;
    case SOUTH_RIGHT:
        count = vehicleCountLanes.value( 20 );
        break;
    case SOUTH_LEFT:
        count = vehicleCountLanes.value( 21 );
        break;
    default:
        LOG_WARNING( "Wrong lane (%i) for this junction (id = 1)", lane );
        break;
    }

    return count;
}

int VehicleCountManager::vehicleCountOnLane2( const QHash<int, int> &vehicleCountLanes, Lane lane )
{
    int count = 0;
    switch( lane )
    {
    case WEST_TOP:
        count = vehicleCountLanes.value( 2080 );
        break;
    case WEST_MIDDLE:
        count = vehicleCountLanes.value( 3090 );
        break;
    case WEST_BOTTOM:
        count = vehicleCountLanes.value( 4010 );
        break;
    case EAST_TOP:
        count = vehicleCountLanes.value( 119 );
        break;
    case EAST_MIDDLE:
        count = vehicleCountLanes.value( 102 );
        break;
    case EAST_BOTTOM:
        count = vehicleCountLanes.value( 104 );
        break;
    case NORTH_LEFT:
        count = vehicleCountLanes.value( 1718 );
        break;
    case NORTH_MIDDLE:
        count = vehicleCountLanes.value( 2627 );
        break;
    case NORTH_RIGHT:
        count = vehicleCountLanes.value( 3233 );
        break;
    case SOUTH_LEFT:
        count = vehicleCountLanes.value( 4243 );
        break;
    case SOUTH_MIDDLE:
        count = vehicleCountLanes.value( 4445 );
        break;
    case SOUTH_RIGHT:
        count = vehicleCountLanes.value( 5354 );
        break;
    default:
        LOG_WARNING( "Wrong lane (%i) for this junction (id = 2)", lane );
        break;
    }

    return count;
}

int VehicleCountManager::vehicleCountOnLane3( const QHash<int, int> &vehicleCountLanes, Lane lane )
{
    int count = 0;

    switch( lane )
    {
    case EAST_MIDDLE:
        count = vehicleCountLanes.value( 5 );
        break;
    case WEST_MIDDLE:
        count = vehicleCountLanes.value( 101 );
        break;
    case SOUTH_RIGHT:
        count = vehicleCountLanes.value( 23 );
        break;
    case SOUTH_LEFT:
        count = vehicleCountLanes.value( 29 );
        break;
    default:
        LOG_WARNING( "Wrong lane (%i) for this junction (id = 3)", lane );
        break;
    }

    return count;
}

int VehicleCountManager::vehicleCountOnLane4( const QHash<int, int> &vehicleCountLanes, Lane lane )
{
    int count = 0;

    switch( lane )
    {
    case EAST_MIDDLE:
        count = vehicleCountLanes.value( 100 );
        break;
    case WEST_MIDDLE:
        count = vehicleCountLanes.value( 72 );
        break;
    case SOUTH_RIGHT:
        count = vehicleCountLanes.value( 90 );
        break;
    case SOUTH_LEFT:
        count = vehicleCountLanes.value( 103 );
        break;
    default:
        LOG_WARNING( "Wrong lane (%i) for this junction (id = 4)", lane );
        break;
    }

    return count;
}

int VehicleCountManager::vehicleCountOnLane5( const QHash<int, int> &vehicleCountLanes, Lane lane )
{
    int count = 0;

    switch( lane )
    {
    case WEST_MIDDLE:
        count = vehicleCountLanes.value( 81 );
        break;
    case EAST_MIDDLE:
        count = vehicleCountLanes.value( 71 );
        break;
    case SOUTH_LEFT:
        count = vehicleCountLanes.value( 105 );
        break;
    case SOUTH_RIGHT:
        count = vehicleCountLanes.value( 108 );
        break;
    default:
        LOG_WARNING( "Wrong lane (%i) for this junction (id = 5)", lane );
        break;
    }

    return count;
}

int VehicleCountManager::vehicleCountOnLane6( const QHash<int, int> &vehicleCountLanes, Lane lane )
{
    int count = 0;

    switch( lane )
    {
    case WEST_MIDDLE:
        count = vehicleCountLanes.value( 139 );
        break;
    case EAST_MIDDLE:
        count = vehicleCountLanes.value( 82 );
        break;
    case SOUTH_LEFT:
        count = vehicleCountLanes.value( 106 );
        break;
    case SOUTH_RIGHT:
        count = vehicleCountLanes.value( 121 );
        break;
    default:
        LOG_WARNING( "Wrong lane (%i) for this junction (id = 6)", lane );
        break;
    }
    return count;
}

int VehicleCountManager::wholeVehicleWaitingTimeOnLane( const Junction* junction, Lane lane )
{
    int time = 0;

    switch( junction->id() )
    {
    case 0:
        time = vehicleWaitingTime0( junction->waitingTime(), lane );
        break;
    case 1:
        time = vehicleWaitingTime1( junction->waitingTime(), lane );
        break;
    case 2:
        time = vehicleWaitingTime2( junction->waitingTime(), lane );
        break;
    case 3:
        time = vehicleWaitingTime3( junction->waitingTime(), lane );
        break;
    case 4:
        time = vehicleWaitingTime4( junction->waitingTime(), lane );
        break;
    case 5:
        time = vehicleWaitingTime5( junction->waitingTime(), lane );
        break;
    case 6:
        time = vehicleWaitingTime6( junction->waitingTime(), lane );
        break;
    default:
        LOG_WARNING( "There is no junction with %i id", junction->id() );
        break;
    }

    return time;
}

int VehicleCountManager::sumWaitingTime( const QList<Vehicle *> & vehicleList )
{
    int sumTime = 0;

    QListIterator<Vehicle*> vehicleIterator( vehicleList );

    while( vehicleIterator.hasNext() )
    {
        sumTime += vehicleIterator.next()->waitingTimeInSeconds();
    }

    return sumTime;
}

int VehicleCountManager::vehicleWaitingTime0( const QMultiHash<int, Vehicle *> &waitingTime, Lane lane )
{
    int time = 0;

    switch( lane )
    {
    case WEST_MIDDLE:
        time = sumWaitingTime( waitingTime.values( 6 ) );
        break;
    case EAST_MIDDLE:
        time = sumWaitingTime( waitingTime.values( 107 ) );
        break;
    case SOUTH_LEFT:
        time = sumWaitingTime( waitingTime.values( 38 ) );
        break;
    case SOUTH_RIGHT:
        time = sumWaitingTime( waitingTime.values( 48 ) );
        break;
    default:
        LOG_WARNING( "Wrong lane (%i) for this junction (id = 0)", lane );
        break;
    }

    return time;
}

int VehicleCountManager::vehicleWaitingTime1( const QMultiHash<int, Vehicle *> &waitingTime, Lane lane )
{
    int time = 0;

    switch( lane )
    {
    case EAST_MIDDLE:
        time = sumWaitingTime( waitingTime.values( 0 ) );
        break;
    case WEST_MIDDLE:
        time = sumWaitingTime( waitingTime.values( 11 ) );
        break;
    case SOUTH_RIGHT:
        time = sumWaitingTime( waitingTime.values( 20 ) );
        break;
    case SOUTH_LEFT:
        time = sumWaitingTime( waitingTime.values( 21 ) );
        break;
    default:
        LOG_WARNING( "Wrong lane (%i) for this junction (id = 1)", lane );
        break;
    }

    return time;
}

int VehicleCountManager::vehicleWaitingTime2( const QMultiHash<int, Vehicle *> &waitingTime, Lane lane )
{
    int time = 0;

    switch( lane )
    {
    case WEST_TOP:
        time = sumWaitingTime( waitingTime.values( 2080 ) );
        break;
    case WEST_MIDDLE:
        time = sumWaitingTime( waitingTime.values( 3090 ) );
        break;
    case WEST_BOTTOM:
        time = sumWaitingTime( waitingTime.values( 4010 ) );
        break;
    case EAST_TOP:
        time = sumWaitingTime( waitingTime.values( 119 ) );
        break;
    case EAST_MIDDLE:
        time = sumWaitingTime( waitingTime.values( 102 ) );
        break;
    case EAST_BOTTOM:
        time = sumWaitingTime( waitingTime.values( 104 ) );
        break;
    case NORTH_LEFT:
        time = sumWaitingTime( waitingTime.values( 1718 ) );
        break;
    case NORTH_MIDDLE:
        time = sumWaitingTime( waitingTime.values( 2627 ) );
        break;
    case NORTH_RIGHT:
        time = sumWaitingTime( waitingTime.values( 3233 ) );
        break;
    case SOUTH_LEFT:
        time = sumWaitingTime( waitingTime.values( 4243 ) );
        break;
    case SOUTH_MIDDLE:
        time = sumWaitingTime( waitingTime.values( 4445 ) );
        break;
    case SOUTH_RIGHT:
        time = sumWaitingTime( waitingTime.values( 5354 ) );
        break;
    default:
        LOG_WARNING( "Wrong lane (%i) for this junction (id = 2)", lane );
        break;
    }

    return time;
}

int VehicleCountManager::vehicleWaitingTime3( const QMultiHash<int, Vehicle *> &waitingTime, Lane lane )
{
    int time = 0;

    switch( lane )
    {
    case EAST_MIDDLE:
        time = sumWaitingTime( waitingTime.values( 5 ) );
        break;
    case WEST_MIDDLE:
        time = sumWaitingTime( waitingTime.values( 101 ) );
        break;
    case SOUTH_RIGHT:
        time = sumWaitingTime( waitingTime.values( 23 ) );
        break;
    case SOUTH_LEFT:
        time = sumWaitingTime( waitingTime.values( 29 ) );
        break;
    default:
        LOG_WARNING( "Wrong lane (%i) for this junction (id = 3)", lane );
        break;
    }

    return time;
}

int VehicleCountManager::vehicleWaitingTime4( const QMultiHash<int, Vehicle *> &waitingTime, Lane lane )
{
    int time = 0;

    switch( lane )
    {
    case WEST_MIDDLE:
        time = sumWaitingTime( waitingTime.values( 100 ) );
        break;
    case EAST_MIDDLE:
        time = sumWaitingTime( waitingTime.values( 72 ) );
        break;
    case SOUTH_RIGHT:
        time = sumWaitingTime( waitingTime.values( 90 ) );
        break;
    case SOUTH_LEFT:
        time = sumWaitingTime( waitingTime.values( 103 ) );
        break;
    default:
        LOG_WARNING( "Wrong lane (%i) for this junction (id = 4)", lane );
        break;
    }

    return time;
}

int VehicleCountManager::vehicleWaitingTime5( const QMultiHash<int, Vehicle *> &waitingTime, Lane lane )
{
    int time = 0;

    switch( lane )
    {
    case WEST_MIDDLE:
        time = sumWaitingTime( waitingTime.values( 81 ) );
        break;
    case EAST_MIDDLE:
        time = sumWaitingTime( waitingTime.values( 71 ) );
        break;
    case SOUTH_LEFT:
        time = sumWaitingTime( waitingTime.values( 105 ) );
        break;
    case SOUTH_RIGHT:
        time = sumWaitingTime( waitingTime.values( 108 ) );
        break;
    default:
        LOG_WARNING( "Wrong lane (%i) for this junction (id = 5)", lane );
        break;
    }
    return time;
}

int VehicleCountManager::vehicleWaitingTime6( const QMultiHash<int, Vehicle *> &waitingTime, Lane lane )
{
    int time = 0;

    switch( lane )
    {
    case WEST_MIDDLE:
        time = sumWaitingTime( waitingTime.values( 139 ) );
        break;
    case EAST_MIDDLE:
        time = sumWaitingTime( waitingTime.values( 82 ) );
        break;
    case SOUTH_LEFT:
        time = sumWaitingTime( waitingTime.values( 106 ) );
        break;
    case SOUTH_RIGHT:
        time = sumWaitingTime( waitingTime.values( 121 ) );
        break;
    default:
        LOG_WARNING( "Wrong lane (%i) for this junction (id = 6)", lane );
        break;
    }

    return time;
}
