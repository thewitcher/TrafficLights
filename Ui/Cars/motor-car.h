#ifndef MOTOR_CAR_H
#define MOTOR_CAR_H

#include "vehicle.h"

class MotorCar: public Vehicle
{

    Q_OBJECT
    Q_PROPERTY(TurnSignal m_turnSignal READ m_turnSignal())
    Q_ENUMS(TurnSignal)

public:
    explicit MotorCar( QDeclarativeItem *parent = 0 );

    enum TurnSignal { TurnLeft, TurnRight, OffLight };

    const TurnSignal& m_turnSignal() const;

private:
    TurnSignal m_direction;

public slots:
    void change();
};

#endif // MOTOR_CAR_H
