#include "vehicle-static-container.h"

QList<Vehicle*> VehicleStaticContainer::VEHICLES;

QMap< int, QVector<TrafficLight*> > VehicleStaticContainer::S_LIGHTS ;
