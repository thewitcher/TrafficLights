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

    Vehicle *target;

    bool collision = false;

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
            }
            else
            {
                m_currentVehicle->resumeMove();
            }

            collision = true;
        }
    }

    if( collision == false )
    {
        m_currentVehicle->resumeMove();
    }
}

bool SimpleMove::isGuiltyOfACollision( const Vehicle *target ) const
{
    /*!
     * This function works like this:
     *
     * If m_currentVehicle moves to the west, then we check x coordinates of target and m_currentVehicle:
     * m_currentVehicle->x() - target->x()
     * If above value is greater than zero then m_currentVehicle is behind target (in back of it)
     * In other case m_currentVehicle is in front of target and it is not guilty of this collision.
     *
     * Similar situation is for rest directions.
     */
    switch( m_currentVehicle->direction() )
    {
    case Vehicle::WEST:
        LOG_INFO( "Car direction: WEST (%s)", __FUNCTION__ );
        if( m_currentVehicle->y() == target->y() )
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
        else
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
        break;
    case Vehicle::EAST:
        LOG_INFO( "Car direction: EAST (%s)", __FUNCTION__ );
        if( m_currentVehicle->y() == target->y() )
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
        else
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
        break;
    case Vehicle::NORTH:
        LOG_INFO( "Car direction: NORTH (%s)", __FUNCTION__ );
        if( m_currentVehicle->x() == target->x() )
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
        else
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
        break;
    case Vehicle::SOUTH:
        LOG_INFO( "Car direction: SOUTH (%s)", __FUNCTION__ );
        if( m_currentVehicle->x() == target->x() )
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
        else
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
        break;
    }

    LOG_WARNING( "Probably invalid value in return statement (%s)", __FUNCTION__ );

    return false;
}
