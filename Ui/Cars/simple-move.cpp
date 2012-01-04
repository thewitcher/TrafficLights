#include "simple-move.h"
#include "QDebug"

SimpleMove::SimpleMove( Vehicle *currentVehicle ):
    m_currentVehicle( currentVehicle )
{
}

void SimpleMove::doItWhileMoving()
{
    qDebug() << "Jestem";
}
