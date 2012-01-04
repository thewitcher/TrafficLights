#ifndef VEHICLEMANAGER_H
#define VEHICLEMANAGER_H

#include <QVector>

class Vehicle;

class VehicleManager
{
public:
    static void addVehicle( Vehicle *vehicle );
    static const QVector<Vehicle*> vehicles();

private:
    VehicleManager();
    ~VehicleManager();

    static QVector<Vehicle*> m_vehicles;
};

#endif // VEHICLEMANAGER_H
