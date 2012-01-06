#ifndef VEHICLESTATICCONTAINER_H
#define VEHICLESTATICCONTAINER_H

#include <QList>

class Vehicle;

struct VehicleStaticContainer
{    
    static QList<Vehicle*> VEHICLES;
};

#endif // VEHICLESTATICCONTAINER_H
