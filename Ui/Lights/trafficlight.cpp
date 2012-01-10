#include "trafficlight.h"
#include <QTimer>

TrafficLight::TrafficLight( QDeclarativeItem *parent ) :
    QDeclarativeItem( parent )
{
}

void TrafficLight::setDirection( TrafficLight* light, const Direction &direct )
{
    switch( direct )
    {
    case RIGHT:
        QMetaObject::invokeMethod( light, "setOnlyRightDirection" );
        break;
    case LEFT:
        QMetaObject::invokeMethod( light, "setOnlyLeftDirection" );
        break;
    case STRAIGHT:
        QMetaObject::invokeMethod( light, "setOnlyStraightDirection" );
        break;
    case STRAIGHT_AND_LEFT:
        QMetaObject::invokeMethod( light, "setLeftAndStraightDirection" );
        break;
    case STRAIGHT_AND_RIGHT:
        QMetaObject::invokeMethod( light, "setRightAndStraightDirection" );
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

