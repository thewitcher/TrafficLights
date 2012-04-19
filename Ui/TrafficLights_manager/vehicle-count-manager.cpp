#include "vehicle-count-manager.h"

VehicleCountManager::VehicleCountManager()
{}

VehicleCountManager::~VehicleCountManager()
{}

VehicleCountManager& VehicleCountManager::instance()
{
    static VehicleCountManager S_VEHICLE_COUNT_MANAGER;

    return S_VEHICLE_COUNT_MANAGER;
}

int VehicleCountManager::vehicleCountOnSubcycle( const QHash<uchar, int> &vehicleCountLanes, SubCycle subcycle, bool bigJunction )
{
    int count = 0;

//    if( bigJunction )
//    {
//        switch( cycle )
//        {
//        case SUBCYCLE_0:
//            break;
//        case SUBCYCLE_1:
//            break;
//        case SUBCYCLE_2:
//            break;
//        case SUBCYCLE_3:
//            break;
//        case SUBCYCLE_4:
//            break;
//        case SUBCYCLE_5:
//            break;
//        }
//    }
//    else
//    {
//        switch( cycle )
//        {
//        case SUBCYCLE_0:

//            break;
//        case SUBCYCLE_1:
//            break;
//        case SUBCYCLE_2:
//            break;
//        case SUBCYCLE_3:
//            break;
//        }
//    }

    return count;
}

int VehicleCountManager::vehicleCountOnLane( const QHash<uchar, int> &vehicleCountLanes, LaneOnSimpleJunction lane )
{
    int count = 0;

//    if( bigJunction )
//    {
//        switch( cycle )
//        {
//        case SUBCYCLE_0:
//            break;
//        case SUBCYCLE_1:
//            break;
//        case SUBCYCLE_2:
//            break;
//        case SUBCYCLE_3:
//            break;
//        case SUBCYCLE_4:
//            break;
//        case SUBCYCLE_5:
//            break;
//        }
//    }
//    else
//    {
//        switch( cycle )
//        {
//        case SUBCYCLE_0:

//            break;
//        case SUBCYCLE_1:
//            break;
//        case SUBCYCLE_2:
//            break;
//        case SUBCYCLE_3:
//            break;
//        }
//    }

    return count;
}
