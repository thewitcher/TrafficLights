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
        qDebug() << "pr: " << blinkers;
        QMetaObject::invokeMethod( this, "turnOnRightBlinkers" );
        break;
    case NO_BLINKERS:
        qDebug() << "not: " << blinkers;
        QMetaObject::invokeMethod( this, "stopBlinkers" );
        break;
    }
}
