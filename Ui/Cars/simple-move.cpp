#include "simple-move.h"
#include "../Root_window/vehicle-manager.h"
#include "../Cars/vehicle.h"
#include "../Logger/logger.h"

SimpleMove::SimpleMove( Vehicle *currentVehicle ):
    m_currentVehicle( currentVehicle )
{
}

void SimpleMove::doItWhileMoving()
{
    if( m_currentVehicle != NULL )
    {
        QList<Vehicle*> vehicles = VehicleManager::vehicles();
        vehicles.removeOne( m_currentVehicle );

        QList<Vehicle*>::iterator i;

        for( i = vehicles.begin() ; i != vehicles.end() ; i++ )
        {
            if( m_currentVehicle->collidesWithItem( *i ) == true )
            {
                return;
            }
        }
    }
    else
    {
        LOG_WARNING( "m_currentVehicle in SimpleMove is NULL: %s", __FUNCTION__ );
    }
}
