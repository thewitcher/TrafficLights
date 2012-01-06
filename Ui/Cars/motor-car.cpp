#include "motor-car.h"
#include <QTimer>

MotorCar::MotorCar( QDeclarativeItem *parent ):
    Vehicle(parent)
{
    m_direction = TurnRight;
    QTimer::singleShot(8000,this,SLOT(change()));
}


const MotorCar::TurnSignal& MotorCar::m_turnSignal() const
{
    return m_direction;
}

void MotorCar::change()
{
    m_direction = TurnLeft;
}
