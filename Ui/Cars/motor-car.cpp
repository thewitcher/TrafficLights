#include "motor-car.h"

MotorCar::MotorCar( QDeclarativeItem *parent ):
    Vehicle( parent )
{
}

void MotorCar::setDarkDesign( bool dark )
{
    if( dark )
    {
        setProperty( "imageSource", "qrc:/graphics/Graphics/motor_car_small_dark.png" );
    }
    else
    {
        setProperty( "imageSource", "qrc:/graphics/Graphics/motor_car_small_bright.png" );
    }
}
