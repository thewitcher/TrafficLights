#include "trafficlight.h"
#include "../Checkpoints_manager/checkpoint.h"
#include <QTimer>

TrafficLight::TrafficLight( QDeclarativeItem *parent ) :
    QDeclarativeItem( parent ),
    m_checkpoint( NULL )
{
}

void TrafficLight::setDirection( const Direction &direct )
{
    switch( direct )
    {
    case RIGHT:
        QMetaObject::invokeMethod( this, "setOnlyRightDirection" );
        break;
    case LEFT:
        QMetaObject::invokeMethod( this, "setOnlyLeftDirection" );
        break;
    case STRAIGHT:
        QMetaObject::invokeMethod( this, "setOnlyStraightDirection" );
        break;
    case STRAIGHT_AND_LEFT:
        QMetaObject::invokeMethod( this, "setLeftAndStraightDirection" );
        break;
    case STRAIGHT_AND_RIGHT:
        QMetaObject::invokeMethod( this, "setRightAndStraightDirection" );
    }
}

Checkpoint * TrafficLight::checkpoint() const
{
    return m_checkpoint;
}

void TrafficLight::createCheckpoint( Checkpoint *checkpoint )
{
    m_checkpoint = checkpoint;
}

void TrafficLight::letGoVehicles()
{
    QMetaObject::invokeMethod( this, "letGo" );
//    m_checkpoint->setMovePermission( true );
}

void TrafficLight::holdVehicles()
{
    QMetaObject::invokeMethod( this, "hold" );
//        m_checkpoint->setMovePermission( false );

}



