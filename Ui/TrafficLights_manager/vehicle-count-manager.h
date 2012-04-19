#ifndef VEHICLECOUNTMANAGER_H
#define VEHICLECOUNTMANAGER_H

#include <qglobal.h>
#include <QHash>

class VehicleCountManager
{
public:
    enum SubCycle
    {
        SUBCYCLE_0,
        SUBCYCLE_1,
        SUBCYCLE_2,
        SUBCYCLE_3,
        SUBCYCLE_4,
        SUBCYCLE_5
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

    static int vehicleCountOnSubcycle( const QHash<uchar,int>& vehicleCountLanes, SubCycle subcycle, bool bigJunction );
    static int vehicleCountOnLane( const QHash<uchar,int>& vehicleCountLanes, Lane lane, int junctionId );

private:
    /// static int vehicleCountOnLaneI - I is a junction id
    static int vehicleCountOnLane0( const QHash<uchar,int>& vehicleCountLanes, Lane lane );
    static int vehicleCountOnLane1( const QHash<uchar,int>& vehicleCountLanes, Lane lane );
    static int vehicleCountOnLane2( const QHash<uchar,int>& vehicleCountLanes, Lane lane );
    static int vehicleCountOnLane3( const QHash<uchar,int>& vehicleCountLanes, Lane lane );
    static int vehicleCountOnLane4( const QHash<uchar,int>& vehicleCountLanes, Lane lane );
    static int vehicleCountOnLane5( const QHash<uchar,int>& vehicleCountLanes, Lane lane );
    static int vehicleCountOnLane6( const QHash<uchar,int>& vehicleCountLanes, Lane lane );
};

#endif // VEHICLECOUNTMANAGER_H
