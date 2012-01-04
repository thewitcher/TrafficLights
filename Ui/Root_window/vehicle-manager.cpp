#include "vehicle-manager.h"

QVector<Vehicle*> VehicleManager::m_vehicles;

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

const QVector<Vehicle*> VehicleManager::vehicles()
{
    return m_vehicles;
}
