#include "simple-move.h"
#include "../Logger/logger.h"
#include "../Root_window/vehicle-static-container.h"
#include "vehicle.h"
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
            }
            else
            {
                m_currentVehicle->resumeMove();
            }

            return;
        }
    }

    m_currentVehicle->resumeMove();
}

bool SimpleMove::isGuiltyOfACollision( const Vehicle *target ) const
{
//    /*!
//     * This function works like this:
//     *
//     * If m_currentVehicle moves to the west, then we check x coordinates of target and m_currentVehicle:
//     * m_currentVehicle->x() - target->x()
//     * If above value is greater than zero then m_currentVehicle is behind target (in back of it)
//     * In other case m_currentVehicle is in front of target and it is not guilty of this collision.
//     *
//     * Similar situation is for rest directions.
//     */
//    switch( m_currentVehicle->direction() )
//    {
//    case Vehicle::WEST:
//        LOG_INFO( "Car direction: WEST (%s)", __FUNCTION__ );
//        if( m_currentVehicle->y() == target->y() )
//        {
//            if( m_currentVehicle->x() - target->x() > 0 )
//            {
//                return true;
//            }
//            else
//            {
//                return false;
//            }
//        }
//        else
//        {
//            if( m_currentVehicle->y() - target->y() > 0 )
//            {
//                return true;
//            }
//            else
//            {
//                return false;
//            }
//        }
//        break;
//    case Vehicle::EAST:
//        LOG_INFO( "Car direction: EAST (%s)", __FUNCTION__ );
//        if( m_currentVehicle->y() == target->y() )
//        {
//            if( m_currentVehicle->x() - target->x() > 0 )
//            {
//                return false;
//            }
//            else
//            {
//                return true;
//            }
//        }
//        else
//        {
//            if( m_currentVehicle->y() - target->y() > 0 )
//            {
//                return false;
//            }
//            else
//            {
//                return true;
//            }
//        }
//        break;
//    case Vehicle::NORTH:
//        LOG_INFO( "Car direction: NORTH (%s)", __FUNCTION__ );
//        if( m_currentVehicle->x() == target->x() )
//        {
//            if( m_currentVehicle->y() - target->y() > 0 )
//            {
//                return true;
//            }
//            else
//            {
//                return false;
//            }
//        }
//        else
//        {
//            if( m_currentVehicle->x() - target->x() > 0 )
//            {
//                return false;
//            }
//            else
//            {
//                return true;
//            }
//        }
//        break;
//    case Vehicle::SOUTH:
//        LOG_INFO( "Car direction: SOUTH (%s)", __FUNCTION__ );
//        if( m_currentVehicle->x() == target->x() )
//        {
//            if( m_currentVehicle->y() - target->y() > 0 )
//            {
//                return false;
//            }
//            else
//            {
//                return true;
//            }
//        }
//        else
//        {
//            if( m_currentVehicle->x() - target->x() > 0 )
//            {
//                return true;
//            }
//            else
//            {
//                return false;
//            }
//        }
//        break;
//    }

//    LOG_WARNING( "Probably invalid value in return statement (%s)", __FUNCTION__ );

//    return false;

    Vehicle::Direction currentVehicleDirection = m_currentVehicle->direction();
    Vehicle::Direction targetVehicleDirection = target->direction();

    /*!
     * One
     */
    if( ( currentVehicleDirection == Vehicle::WEST ) && ( targetVehicleDirection == Vehicle::NORTH ) )
    {
        if( !identifyCase( m_currentVehicle, target ) )
        {
            return true;
        }
    }
    else if( ( currentVehicleDirection == Vehicle::NORTH ) && ( targetVehicleDirection == Vehicle::WEST ) )
    {

    }

    /*!
     * Two
     */
    else if( ( currentVehicleDirection == Vehicle::SOUTH ) && ( targetVehicleDirection == Vehicle::WEST ) )
    {
        if( identifyCase( m_currentVehicle, target ) == true )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if( ( currentVehicleDirection == Vehicle::WEST ) && ( targetVehicleDirection == Vehicle::SOUTH ) )
    {
        if( identifyCase( m_currentVehicle, target ) == false )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /*!
     * Three
     */
    else if( ( currentVehicleDirection == Vehicle::EAST ) && ( targetVehicleDirection == Vehicle::NORTH ) )
    {

    }
    else if( ( currentVehicleDirection == Vehicle::NORTH ) && ( targetVehicleDirection == Vehicle::EAST ) )
    {

    }

    /*!
     * Four
     */
    else if( ( currentVehicleDirection == Vehicle::EAST ) && ( targetVehicleDirection == Vehicle::SOUTH ) )
    {

    }
    else if( ( currentVehicleDirection == Vehicle::SOUTH ) && ( targetVehicleDirection == Vehicle::EAST ) )
    {

    }

    // We compare only approriate coordinates
    else if( ( currentVehicleDirection == Vehicle::EAST ) && ( targetVehicleDirection == Vehicle::EAST ) )
    {

    }
    else if( ( currentVehicleDirection == Vehicle::WEST ) && ( targetVehicleDirection == Vehicle::WEST ) )
    {

    }
    else if( ( currentVehicleDirection == Vehicle::NORTH ) && ( targetVehicleDirection == Vehicle::SOUTH ) )
    {

    }
    else if( ( currentVehicleDirection == Vehicle::SOUTH ) && ( targetVehicleDirection == Vehicle::SOUTH ) )
    {

    }

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
