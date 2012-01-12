#include "trafficlight.h"
#include <QTimer>

TrafficLight::TrafficLight( QDeclarativeItem *parent ) :
    QDeclarativeItem( parent )
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

void TrafficLight::changeState()
{
    QMetaObject::invokeMethod( this, "letGo" );
    QTimer::singleShot( 6000, this, SLOT( holdVehicles() ) );
    QTimer::singleShot( 12000, this, SLOT( letGoVehicles() ) );
}

void TrafficLight::letGoVehicles()
{
    QMetaObject::invokeMethod( this, "letGo" );
}

void TrafficLight::holdVehicles()
{
    QMetaObject::invokeMethod( this, "hold" );
}
