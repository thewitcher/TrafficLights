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
    enum LaneOnSimpleJunction
    {

    };

    static int vehicleCountOnSubcycle( const QHash<uchar,int>& vehicleCountLanes, SubCycle subcycle, bool bigJunction );
    static int vehicleCountOnLane( const QHash<uchar,int>& vehicleCountLanes, LaneOnSimpleJunction lane );

private:
    VehicleCountManager();
    ~VehicleCountManager();

    VehicleCountManager& instance();
};

#endif // VEHICLECOUNTMANAGER_H
