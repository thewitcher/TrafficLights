#include "simple-move.h"
#include "../Logger/logger.h"
#include "../Root_window/vehicle-static-container.h"
#include "vehicle.h"
#include <QAbstractAnimation>
#include <QTimer>

int SimpleMove::WAIT_FOR_MOVE_TIME = 3000;

SimpleMove::SimpleMove( Vehicle *target ):
    m_currentVehicle( target ),
    m_delayCaller( new DelayCaller( this ) )
{
}

SimpleMove::~SimpleMove()
{
    if( m_delayCaller != NULL )
    {
        delete m_delayCaller;
    }
}

void SimpleMove::collisionDetection()
{
    // Checking collisions
    QList<Vehicle*> vehicles = VehicleStaticContainer::VEHICLES;

    vehicles.removeOne( m_currentVehicle );

    QListIterator<Vehicle*> iterator( vehicles );

    Vehicle *target;

    while( iterator.hasNext() )
    {
        target = iterator.next();

        if( m_currentVehicle->updateCollisionPoint()->collidesWithItem( target ) == true )
        {
            m_currentVehicle->pauseMove();

            m_delayCaller->callAfterDelay( WAIT_FOR_MOVE_TIME );

            return;
        }
    }

    m_currentVehicle->resumeMove();
}

// DELAYCALLER
DelayCaller::DelayCaller( SimpleMove *mainObject, QObject *parent ):
    QObject(parent),
    m_mainObject( mainObject )
{
}

void DelayCaller::callAfterDelay( int delay )
{
    QTimer::singleShot( delay, this, SLOT(invoke()) );
}

void DelayCaller::invoke()
{
    LOG_INFO( "Start %s", __FUNCTION__ );

    m_mainObject->collisionDetection();
}
