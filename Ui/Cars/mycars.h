#ifndef MYCARS_H
#define MYCARS_H

#include "vehicle.h"

class MyCars : public Vehicle
{
    Q_OBJECT
    Q_PROPERTY(TurnSignal m_turnSignal READ m_turnSignal())
    Q_ENUMS(TurnSignal)

public:
    explicit MyCars(QDeclarativeItem *parent = 0);
    enum TurnSignal { TurnLeft, TurnRight, OffLight };
    const TurnSignal& m_turnSignal() const;

private:
    TurnSignal m_direction;

public slots:
    void change();
};

#endif // MYCARS_H
