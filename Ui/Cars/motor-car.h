#ifndef MOTOR_CAR_H
#define MOTOR_CAR_H

#include "vehicle.h"

class MotorCar: public Vehicle
{

    Q_OBJECT

public:
    explicit MotorCar( QDeclarativeItem *parent = 0 );

    void setDarkDesign( bool dark = false );
};

#endif // MOTOR_CAR_H
