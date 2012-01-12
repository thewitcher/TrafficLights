#ifndef MOTOR_CAR_H
#define MOTOR_CAR_H

#include "vehicle.h"

class MotorCar: public Vehicle
{

    Q_OBJECT

public:
    explicit MotorCar( QDeclarativeItem *parent = 0 );

    void setBlinkers( Blinkers blinkers = NO_BLINKERS );
    void setBackLights( bool backLight = false );
    void setLongLights( bool longLight = false );
};

#endif // MOTOR_CAR_H
