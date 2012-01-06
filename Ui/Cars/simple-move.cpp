#include "simple-move.h"
#include "../Logger/logger.h"
#include "../Root_window/vehicle-static-container.h"
#include "vehicle.h"
#include <QAbstractAnimation>

SimpleMove::SimpleMove( Vehicle *target ):
    m_currentVehicle( target )
{
}

void SimpleMove::collisionDetection()
{
    // Checking collisions
    QList<Vehicle*> vehicles = VehicleStaticContainer::VEHICLES;
    vehicles.removeOne( m_currentVehicle );

    QListIterator<Vehicle*> iterator( vehicles );

    while( iterator.hasNext() )
    {
    }
}
