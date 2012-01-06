#include "mycars.h"
#include <QTimer>

MyCars::MyCars( QDeclarativeItem *parent ):
    Vehicle(parent)
{
    m_direction = TurnRight;
    QTimer::singleShot(8000,this,SLOT(change()));
}


const MyCars::TurnSignal& MyCars::m_turnSignal() const
{
    return m_direction;
}

void MyCars::change()
{
    m_direction = TurnLeft;
}
