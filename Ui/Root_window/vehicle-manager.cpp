#include "vehicle-manager.h"

QList<Vehicle*> VehicleManager::m_vehicles;

VehicleManager::VehicleManager()
{
}

VehicleManager::~VehicleManager()
{
}

void VehicleManager::addVehicle( Vehicle *vehicle )
{
    m_vehicles.append( vehicle );
}

const QList<Vehicle*> VehicleManager::vehicles()
{
    return m_vehicles;
}
