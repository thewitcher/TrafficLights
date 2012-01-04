#include "simple-move.h"
#include "../Root_window/vehicle-manager.h"
#include "../Cars/vehicle.h"
#include "../Logger/logger.h"
#include <QAbstractAnimation>
#include <QTimer>

SimpleMove::SimpleMove( Vehicle *currentVehicle ):
    m_currentVehicle( currentVehicle )
{
}

#include <QDebug>
void SimpleMove::doItWhileMoving()
{
    static Vehicle* tempVehicle;

    if( m_currentVehicle != NULL )
    {
        if( m_currentVehicle->checkState() )
        {
            if( m_currentVehicle->currentAnimation() != NULL )
            {
                QList<Vehicle*> vehicles = VehicleManager::vehicles();
                qDebug() << "Lista przed: " << vehicles;
                vehicles.removeOne( m_currentVehicle );
                qDebug() << "Lista po: " << vehicles;
                qDebug() << "Vehicle: " << m_currentVehicle;

                QList<Vehicle*>::iterator i;

                for( i = vehicles.begin() ; i != vehicles.end() ; i++ )
                {
                    if( m_currentVehicle->collidesWithItem( *i ) == true )
                    {
                        tempVehicle = *i;
                        tempVehicle->setCheckState( false );
                        qDebug() << "Pause";
                        m_currentVehicle->currentAnimation()->pause();

                        QTimer::singleShot( 4000, m_currentVehicle, SLOT(startMove()) );
                        QTimer::singleShot( 4000, tempVehicle, SLOT(changeCheckState()) );

                        return;
                    }
                }
            }
        }
    }
    else
    {
        LOG_WARNING( "m_currentVehicle in SimpleMove is NULL: %s", __FUNCTION__ );
    }
}
