#ifndef VEHICLESTATICCONTAINER_H
#define VEHICLESTATICCONTAINER_H

#include <QMap>
#include <QVector>

class TrafficLight;

struct VehicleStaticContainer
{    
    static QMap< int, QVector<TrafficLight*> > S_LIGHTS;
};

#endif // VEHICLESTATICCONTAINER_H
