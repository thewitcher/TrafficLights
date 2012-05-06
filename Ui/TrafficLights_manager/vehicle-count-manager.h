#ifndef VEHICLECOUNTMANAGER_H
#define VEHICLECOUNTMANAGER_H

#include <qglobal.h>
#include <QHash>
#include "../Cars/vehicle.h"

class Junction;

class VehicleCountManager
{
public:
    enum SubCycle
    {
        SUBCYCLE_0,
        SUBCYCLE_1,
        SUBCYCLE_2,
        SUBCYCLE_3
    };
    enum Lane
    {
        WEST_TOP,
        WEST_MIDDLE,
        WEST_BOTTOM,
        EAST_TOP,
        EAST_MIDDLE,
        EAST_BOTTOM,
        NORTH_LEFT,
        NORTH_MIDDLE,
        NORTH_RIGHT,
        SOUTH_LEFT,
        SOUTH_MIDDLE,
        SOUTH_RIGHT
    };

    /*! Returns the number vehicles on appropriate Junction for a given subcycle.*/
    static int vehicleCountOnSubcycle( const Junction* junction, SubCycle subcycle );

    /*! Returns the number of vehicles on all Junction without given subcycle.*/
    static int vehicleCountOnRestSubcycle( const Junction* junction, SubCycle subcycle );

    /*! Returns the number vehicles on appropriate Junction for a given lane. */    
    static int vehicleCountOnLane( const Junction* junction, Lane lane );

    /*! Returns the total waiting time vehicles on appropriate Junction for a given subcycle. */
    static int wholeVehicleWaitingTimeForSubcycle( const Junction* junction, SubCycle subcycle );
    
    /*! Returns the total waiting time vehicles on appropriate Junction for a given lane. */    
    static int wholeVehicleWaitingTimeOnLane( const Junction* junction, Lane lane );

    /*! Returns the average waiting vehicles time on appropriate Junction for a given subcycle. */
    static float averageVehicleWaitingTimeOnSubcycle( const Junction* junction, SubCycle subcycle );

private:
    /// static int vehicleCountOnLaneI - I is a junction id
    static int vehicleCountOnLane0( const QHash<int,int>& vehicleCountLanes, Lane lane );
    static int vehicleCountOnLane1( const QHash<int,int>& vehicleCountLanes, Lane lane );
    static int vehicleCountOnLane2( const QHash<int,int>& vehicleCountLanes, Lane lane );
    static int vehicleCountOnLane3( const QHash<int,int>& vehicleCountLanes, Lane lane );
    static int vehicleCountOnLane4( const QHash<int,int>& vehicleCountLanes, Lane lane );
    static int vehicleCountOnLane5( const QHash<int,int>& vehicleCountLanes, Lane lane );
    static int vehicleCountOnLane6( const QHash<int,int>& vehicleCountLanes, Lane lane );

    static int vehicleWaitingTime0( const QMultiHash<int,Vehicle*>& waitingTime, Lane lane );
    static int vehicleWaitingTime1( const QMultiHash<int,Vehicle*>& waitingTime, Lane lane );
    static int vehicleWaitingTime2( const QMultiHash<int,Vehicle*>& waitingTime, Lane lane );
    static int vehicleWaitingTime3( const QMultiHash<int,Vehicle*>& waitingTime, Lane lane );
    static int vehicleWaitingTime4( const QMultiHash<int,Vehicle*>& waitingTime, Lane lane );
    static int vehicleWaitingTime5( const QMultiHash<int,Vehicle*>& waitingTime, Lane lane );
    static int vehicleWaitingTime6( const QMultiHash<int,Vehicle*>& waitingTime, Lane lane );

    static int sumWaitingTime( const QList<Vehicle*>& vehicleList );

    /* auxiliary function for vehicleCountOnSubcycle and wholeVehicleWaitingTimeForSubcycle */
    static int vehicleCountOnSubcycleForSimpleJunction( const Junction* junction, SubCycle subcycle );
    static int vehicleCountOnSubcycleForBladzioJunction( const Junction* junction, SubCycle subcycle );
    static int wholeVehicleWaitingTimeForSimpleJunction( const Junction* junction, SubCycle subcycle );
    static int wholeVehicleWaitingTimeForBladzioJunction( const Junction* junction, SubCycle subcycle );
};

#endif // VEHICLECOUNTMANAGER_H
