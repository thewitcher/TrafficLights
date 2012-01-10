#ifndef VEHICLESTATICCONTAINER_H
#define VEHICLESTATICCONTAINER_H

#include <QList>
#include <QMap>
#include <QVector>

class Vehicle;
class TrafficLight;

struct VehicleStaticContainer
{    
    static QList<Vehicle*> VEHICLES;
    static QMap< int, QVector<TrafficLight*> > S_LIGHTS;
};

#endif // VEHICLESTATICCONTAINER_H
