#include "motor-car.h"

MotorCar::MotorCar( QDeclarativeItem *parent ):
    Vehicle( parent )
{
}

void MotorCar::setBlinkers( Blinkers blinkers )
{
    switch( blinkers )
    {
    case LEFT_BLINKERS:
        QMetaObject::invokeMethod( this, "turnOnLeftBlinkers" );
        break;
    case RIGHT_BLINKERS:
        QMetaObject::invokeMethod( this, "turnOnRightBlinkers" );
        break;
    case NO_BLINKERS:
        QMetaObject::invokeMethod( this, "stopBlinkers" );
        break;
    }
}

void MotorCar::setBackLights( bool backLight )
{
    if( backLight )
        QMetaObject::invokeMethod( this, "onBackLights" );
    else
        QMetaObject::invokeMethod( this, "offBackLights" );
}

void MotorCar::setLongLights( bool longLight )
{
    if( longLight )
        QMetaObject::invokeMethod( this, "turnOnLongLights" );
    else
        QMetaObject::invokeMethod( this, "turnOffLongLights" );
}
