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

        if( m_currentVehicle->collidesWithItem( target ) )
        {
            // Collision
            LOG_INFO( "Collision detected (%s)", __FUNCTION__ );

            if( isGuiltyOfACollision( target ) )
            {
                m_currentVehicle->pauseMove();

                m_delayCaller->callAfterDelay( WAIT_FOR_MOVE_TIME );

                return;
            }
        }
    }

    m_currentVehicle->resumeMove();
}

bool SimpleMove::isGuiltyOfACollision( const Vehicle *target ) const
{
    Vehicle::Direction currentVehicleDirection = m_currentVehicle->direction();
    Vehicle::Direction targetVehicleDirection = target->direction();

    /*!
     * Horizontal line
     */
    if( identifyCase( m_currentVehicle, target ) )
    {
        // *******************************************
        if( ( currentVehicleDirection == Vehicle::WEST ) && ( targetVehicleDirection == Vehicle::NORTH ) )
        {
            return true;
        }
        else if( ( currentVehicleDirection == Vehicle::NORTH ) && ( targetVehicleDirection == Vehicle::WEST ) )
        {
            return false;
        }
        // *******************************************
        else if( ( currentVehicleDirection == Vehicle::SOUTH ) && ( targetVehicleDirection == Vehicle::WEST ) )
        {
            return true;
        }
        else if( ( currentVehicleDirection == Vehicle::WEST ) && ( targetVehicleDirection == Vehicle::SOUTH ) )
        {
            return false;
        }
        // *******************************************
        else if( ( currentVehicleDirection == Vehicle::EAST ) && ( targetVehicleDirection == Vehicle::NORTH ) )
        {
            return true;
        }
        else if( ( currentVehicleDirection == Vehicle::NORTH ) && ( targetVehicleDirection == Vehicle::EAST ) )
        {
            return false;
        }
        // *******************************************
        else if( ( currentVehicleDirection == Vehicle::EAST ) && ( targetVehicleDirection == Vehicle::SOUTH ) )
        {
            return true;
        }
        else if( ( currentVehicleDirection == Vehicle::SOUTH ) && ( targetVehicleDirection == Vehicle::EAST ) )
        {
            return false;
        }
        // *******************************************
    }
    /*!
     * Vertical line
     */
    else
    {
        // *******************************************
        if( ( currentVehicleDirection == Vehicle::WEST ) && ( targetVehicleDirection == Vehicle::NORTH ) )
        {
            return false;
        }
        else if( ( currentVehicleDirection == Vehicle::NORTH ) && ( targetVehicleDirection == Vehicle::WEST ) )
        {
            return true;
        }
        // *******************************************
        else if( ( currentVehicleDirection == Vehicle::SOUTH ) && ( targetVehicleDirection == Vehicle::WEST ) )
        {
            return false;
        }
        else if( ( currentVehicleDirection == Vehicle::WEST ) && ( targetVehicleDirection == Vehicle::SOUTH ) )
        {
            return true;
        }
        // *******************************************
        else if( ( currentVehicleDirection == Vehicle::EAST ) && ( targetVehicleDirection == Vehicle::NORTH ) )
        {
            return false;
        }
        else if( ( currentVehicleDirection == Vehicle::NORTH ) && ( targetVehicleDirection == Vehicle::EAST ) )
        {
            return true;
        }
        // *******************************************
        else if( ( currentVehicleDirection == Vehicle::EAST ) && ( targetVehicleDirection == Vehicle::SOUTH ) )
        {
            return false;
        }
        else if( ( currentVehicleDirection == Vehicle::SOUTH ) && ( targetVehicleDirection == Vehicle::EAST ) )
        {
            return true;
        }
        // *******************************************
    }

    // We compare only approriate coordinates
    if( ( currentVehicleDirection == Vehicle::EAST ) && ( targetVehicleDirection == Vehicle::EAST ) )
    {
        if( m_currentVehicle->x() - target->x() > 0 )
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else if( ( currentVehicleDirection == Vehicle::WEST ) && ( targetVehicleDirection == Vehicle::WEST ) )
    {
        if( m_currentVehicle->x() - target->x() > 0 )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if( ( currentVehicleDirection == Vehicle::NORTH ) && ( targetVehicleDirection == Vehicle::SOUTH ) )
    {
        if( m_currentVehicle->y() - target->y() > 0 )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if( ( currentVehicleDirection == Vehicle::SOUTH ) && ( targetVehicleDirection == Vehicle::SOUTH ) )
    {
        if( m_currentVehicle->y() - target->y() > 0 )
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    LOG_INFO( "Return statement is probalby invalid (%s)", __FUNCTION__ );

    return false;
}

// Returns true if vector is almost horizontal
bool SimpleMove::identifyCase( const Vehicle *current, const Vehicle *target ) const
{
    qreal result = ( current->y() - target->y() ) / ( current->x() - target->x() );

    // 0.7 is aproximately value of cos(45)
    if( abs( result ) < 0.7 )
    {
        return false;
    }

    return true;
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

    qDebug() << "Invoke";
}