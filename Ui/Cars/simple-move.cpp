#include "simple-move.h"
#include "../Logger/logger.h"
#include "../Root_window/vehicle-static-container.h"
#include "vehicle.h"
#include "../Root_window/graphics-scene.h"
#include <QAbstractAnimation>
#include <QTimer>

int SimpleMove::WAIT_FOR_MOVE_TIME = 1000;

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

    QListIterator<Vehicle*> iterator( m_currentVehicle->parentScene()->allVehicles() );

    Vehicle *target;

    while( iterator.hasNext() )
    {
        target = iterator.next();

        // We don't compare vehicle to the same vehicle.
        if( m_currentVehicle == target )
        {
            continue;
        }

        if( m_currentVehicle->collisionPoint().collideWithItem( target ) )
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
