#ifndef VEHICLEMANAGER_H
#define VEHICLEMANAGER_H

#include <QList>

class Vehicle;

class VehicleManager
{
public:
    static void addVehicle( Vehicle *vehicle );
    static const QList<Vehicle*> vehicles();

private:
    VehicleManager();
    ~VehicleManager();

    static QList<Vehicle*> m_vehicles;
};

#endif // VEHICLEMANAGER_H
