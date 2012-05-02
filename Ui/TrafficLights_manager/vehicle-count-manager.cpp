#include "vehicle-count-manager.h"
#include "../../Logger/logger.h"

int VehicleCountManager::vehicleCountOnSubcycle( const QHash<uchar, int> &vehicleCountLanes, SubCycle subcycle, int junctionId )
{
    int count = 0;

    if( junctionId != 2 )
    {
        count = vehicleCountOnSubcycleForSimpleJunction( vehicleCountLanes, subcycle, junctionId );
    }
    else{
        count = vehicleCountOnSubcycleForBladzioJunction( vehicleCountLanes, subcycle, junctionId );
    }
    return count;
}

int VehicleCountManager::vehicleCountOnSubcycleForSimpleJunction( const QHash<uchar, int> &vehicleCountLanes, SubCycle subcycle, int junctionId )
{
    int count = 0;
    switch( subcycle )
    {
    case SUBCYCLE_0:
        count = vehicleCountOnLane( vehicleCountLanes, SOUTH_LEFT, junctionId ) + vehicleCountOnLane( vehicleCountLanes, SOUTH_RIGHT, junctionId );
        break;
    case SUBCYCLE_1:
        count = vehicleCountOnLane( vehicleCountLanes, EAST_MIDDLE, junctionId );
        break;
    case SUBCYCLE_2:
        count = vehicleCountOnLane( vehicleCountLanes, WEST_MIDDLE, junctionId );
        break;
    default:
        LOG_WARNING( "There is no junction with %i id", junctionId );
        break;
    }
    return count;
}

int VehicleCountManager::vehicleCountOnSubcycleForBladzioJunction( const QHash<uchar, int> &vehicleCountLanes, SubCycle subcycle, int junctionId )
{
    int count = 0;
    switch( subcycle )
    {
    case SUBCYCLE_0:
        count = vehicleCountOnLane( vehicleCountLanes, SOUTH_MIDDLE, junctionId ) + vehicleCountOnLane( vehicleCountLanes, SOUTH_RIGHT, junctionId ) +
                vehicleCountOnLane( vehicleCountLanes, NORTH_MIDDLE, junctionId ) + vehicleCountOnLane( vehicleCountLanes, NORTH_LEFT, junctionId );
        break;
    case SUBCYCLE_1:
        count = vehicleCountOnLane( vehicleCountLanes, SOUTH_LEFT, junctionId ) + vehicleCountOnLane( vehicleCountLanes, NORTH_RIGHT, junctionId );
        break;
    case SUBCYCLE_2:
        count = vehicleCountOnLane( vehicleCountLanes, WEST_MIDDLE, junctionId ) + vehicleCountOnLane( vehicleCountLanes, WEST_BOTTOM, junctionId ) +
                vehicleCountOnLane( vehicleCountLanes, EAST_MIDDLE, junctionId ) + vehicleCountOnLane( vehicleCountLanes, EAST_TOP, junctionId );
        break;
    case SUBCYCLE_3:
        count = vehicleCountOnLane( vehicleCountLanes, WEST_TOP, junctionId ) + vehicleCountOnLane( vehicleCountLanes, EAST_BOTTOM, junctionId );
        break;
    default:
        LOG_WARNING( "There is no junction with %i id", junctionId );
        break;
    }
    return count;
}

int VehicleCountManager::wholeVehicleWaitingTimeForSubcycle( const QMultiHash<uchar,Vehicle*>& waitingTime, SubCycle subcycle, int junctionId )
{
    int count = 0;
    if( junctionId != 2 )
    {
        count = wholeVehicleWaitingTimeForSimpleJunction( waitingTime, subcycle, junctionId );
    }
    else{
        count = wholeVehicleWaitingTimeForBladzioJunction( waitingTime, subcycle, junctionId );
    }
    return count;
}

int VehicleCountManager::wholeVehicleWaitingTimeForSimpleJunction( const QMultiHash<uchar,Vehicle*>& waitingTime, SubCycle subcycle, int junctionId )
{
    int count = 0;
    switch( subcycle )
    {
    case SUBCYCLE_0:
        count = wholeVehicleWaitingTimeOnLane( waitingTime, SOUTH_LEFT, junctionId ) +
                wholeVehicleWaitingTimeOnLane( waitingTime, SOUTH_RIGHT, junctionId );
        break;
    case SUBCYCLE_1:
        count = wholeVehicleWaitingTimeOnLane( waitingTime, EAST_MIDDLE, junctionId );
        break;
    case SUBCYCLE_2:
        count = wholeVehicleWaitingTimeOnLane( waitingTime, WEST_MIDDLE, junctionId );
        break;
    default:
        LOG_WARNING( "There is no junction with %i id", junctionId );
        break;
    }
    return count;
}

int VehicleCountManager::wholeVehicleWaitingTimeForBladzioJunction( const QMultiHash<uchar,Vehicle*>& waitingTime, SubCycle subcycle, int junctionId )
{
    int count = 0;
    switch( subcycle )
    {
    case SUBCYCLE_0:
        count = wholeVehicleWaitingTimeOnLane( waitingTime, SOUTH_MIDDLE, junctionId ) +
                wholeVehicleWaitingTimeOnLane( waitingTime, SOUTH_RIGHT, junctionId ) +
                wholeVehicleWaitingTimeOnLane( waitingTime, NORTH_MIDDLE, junctionId ) +
                wholeVehicleWaitingTimeOnLane( waitingTime, NORTH_LEFT, junctionId );
        break;
    case SUBCYCLE_1:
        count = wholeVehicleWaitingTimeOnLane( waitingTime, SOUTH_LEFT, junctionId ) +
                wholeVehicleWaitingTimeOnLane( waitingTime, NORTH_RIGHT, junctionId );
        break;
    case SUBCYCLE_2:
        count = wholeVehicleWaitingTimeOnLane( waitingTime, WEST_MIDDLE, junctionId ) +
                wholeVehicleWaitingTimeOnLane( waitingTime, WEST_BOTTOM, junctionId ) +
                wholeVehicleWaitingTimeOnLane( waitingTime, EAST_MIDDLE, junctionId ) +
                wholeVehicleWaitingTimeOnLane( waitingTime, EAST_TOP, junctionId );
        break;
    case SUBCYCLE_3:
        count = wholeVehicleWaitingTimeOnLane( waitingTime, WEST_TOP, junctionId ) +
                wholeVehicleWaitingTimeOnLane( waitingTime, EAST_BOTTOM, junctionId );
        break;
    default:
        LOG_WARNING( "There is no junction with %i id", junctionId );
        break;
    }
    return count;
}

int VehicleCountManager::vehicleCountOnLane( const QHash<uchar, int> &vehicleCountLanes, Lane lane, int junctionId )
{
    int count = 0;

    switch( junctionId )
    {
    case 0:
        count = vehicleCountOnLane0( vehicleCountLanes, lane );
        break;
    case 1:
        count = vehicleCountOnLane1( vehicleCountLanes, lane );
        break;
    case 2:
        count = vehicleCountOnLane2( vehicleCountLanes, lane );
        break;
    case 3:
        count = vehicleCountOnLane3( vehicleCountLanes, lane );
        break;
    case 4:
        count = vehicleCountOnLane4( vehicleCountLanes, lane );
        break;
    case 5:
        count = vehicleCountOnLane5( vehicleCountLanes, lane );
        break;
    case 6:
        count = vehicleCountOnLane6( vehicleCountLanes, lane );
        break;
    default:
        LOG_WARNING( "There is no junction with %i id", junctionId );
        break;
    }
      return count;
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
int VehicleCountManager::vehicleCountOnLane0( const QHash<uchar, int> &vehicleCountLanes, Lane lane )
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

int VehicleCountManager::vehicleCountOnLane1( const QHash<uchar, int> &vehicleCountLanes, Lane lane )
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

int VehicleCountManager::vehicleCountOnLane2( const QHash<uchar, int> &vehicleCountLanes, Lane lane )
{
    int count = 0;
    switch( lane )
    {
    case WEST_TOP:
        count = vehicleCountLanes.value( 2 ) + vehicleCountLanes.value( 8 );
        break;
    case WEST_MIDDLE:
        count = vehicleCountLanes.value( 3 ) + vehicleCountLanes.value( 9 );
        break;
    case WEST_BOTTOM:
        count = vehicleCountLanes.value( 4 ) + vehicleCountLanes.value( 10 );
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
        count = vehicleCountLanes.value( 17 ) + vehicleCountLanes.value( 18 );
        break;
    case NORTH_MIDDLE:
        count = vehicleCountLanes.value( 26 ) + vehicleCountLanes.value( 27 );
        break;
    case NORTH_RIGHT:
        count = vehicleCountLanes.value( 32 ) + vehicleCountLanes.value( 33 );
        break;
    case SOUTH_LEFT:
        count = vehicleCountLanes.value( 42 ) + vehicleCountLanes.value( 43 );
        break;
    case SOUTH_MIDDLE:
        count = vehicleCountLanes.value( 44 ) + vehicleCountLanes.value( 45 );
        break;
    case SOUTH_RIGHT:
        count = vehicleCountLanes.value( 53 ) + vehicleCountLanes.value( 54 );
        break;
    default:
        LOG_WARNING( "Wrong lane (%i) for this junction (id = 2)", lane );
        break;
    }

    return count;
}

int VehicleCountManager::vehicleCountOnLane3( const QHash<uchar, int> &vehicleCountLanes, Lane lane )
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

int VehicleCountManager::vehicleCountOnLane4( const QHash<uchar, int> &vehicleCountLanes, Lane lane )
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

int VehicleCountManager::vehicleCountOnLane5( const QHash<uchar, int> &vehicleCountLanes, Lane lane )
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

int VehicleCountManager::vehicleCountOnLane6( const QHash<uchar, int> &vehicleCountLanes, Lane lane )
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

int VehicleCountManager::wholeVehicleWaitingTimeOnLane( const QMultiHash<uchar, Vehicle *> &waitingTime, Lane lane, int junctionId )
{
    int time = 0;

    switch( junctionId )
    {
    case 0:
        time = vehicleWaitingTime0( waitingTime, lane );
        break;
    case 1:
        time = vehicleWaitingTime1( waitingTime, lane );
        break;
    case 2:
        time = vehicleWaitingTime2( waitingTime, lane );
        break;
    case 3:
        time = vehicleWaitingTime3( waitingTime, lane );
        break;
    case 4:
        time = vehicleWaitingTime4( waitingTime, lane );
        break;
    case 5:
        time = vehicleWaitingTime5( waitingTime, lane );
        break;
    case 6:
        time = vehicleWaitingTime6( waitingTime, lane );
        break;
    default:
        LOG_WARNING( "There is no junction with %i id", junctionId );
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

int VehicleCountManager::vehicleWaitingTime0( const QMultiHash<uchar, Vehicle *> &waitingTime, Lane lane )
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

int VehicleCountManager::vehicleWaitingTime1( const QMultiHash<uchar, Vehicle *> &waitingTime, Lane lane )
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

int VehicleCountManager::vehicleWaitingTime2( const QMultiHash<uchar, Vehicle *> &waitingTime, Lane lane )
{
    int time = 0;

    switch( lane )
    {
    case WEST_TOP:
        time = sumWaitingTime( waitingTime.values( 2 ) ) + sumWaitingTime( waitingTime.values( 8 ) );
        break;
    case WEST_MIDDLE:
        time = sumWaitingTime( waitingTime.values( 3 ) ) + sumWaitingTime( waitingTime.values( 9 ) );
        break;
    case WEST_BOTTOM:
        time = sumWaitingTime( waitingTime.values( 4 ) ) + sumWaitingTime( waitingTime.values( 10 ) );
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
        time = sumWaitingTime( waitingTime.values( 17 ) ) + sumWaitingTime( waitingTime.values( 18 ) );
        break;
    case NORTH_MIDDLE:
        time = sumWaitingTime( waitingTime.values( 26 ) ) + sumWaitingTime( waitingTime.values( 27 ) );
        break;
    case NORTH_RIGHT:
        time = sumWaitingTime( waitingTime.values( 32 ) ) + sumWaitingTime( waitingTime.values( 33 ) );
        break;
    case SOUTH_LEFT:
        time = sumWaitingTime( waitingTime.values( 42 ) ) + sumWaitingTime( waitingTime.values( 43 ) );
        break;
    case SOUTH_MIDDLE:
        time = sumWaitingTime( waitingTime.values( 44 ) ) + sumWaitingTime( waitingTime.values( 45 ) );
        break;
    case SOUTH_RIGHT:
        time = sumWaitingTime( waitingTime.values( 53 ) ) + sumWaitingTime( waitingTime.values( 54 ) );
        break;
    default:
        LOG_WARNING( "Wrong lane (%i) for this junction (id = 2)", lane );
        break;
    }

    return time;
}

int VehicleCountManager::vehicleWaitingTime3( const QMultiHash<uchar, Vehicle *> &waitingTime, Lane lane )
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

int VehicleCountManager::vehicleWaitingTime4( const QMultiHash<uchar, Vehicle *> &waitingTime, Lane lane )
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

int VehicleCountManager::vehicleWaitingTime5( const QMultiHash<uchar, Vehicle *> &waitingTime, Lane lane )
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

int VehicleCountManager::vehicleWaitingTime6( const QMultiHash<uchar, Vehicle *> &waitingTime, Lane lane )
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
