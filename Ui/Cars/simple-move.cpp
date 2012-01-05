#include "simple-move.h"
#include "../Root_window/vehicle-manager.h"
#include "../Cars/vehicle.h"
#include "../Logger/logger.h"

SimpleMove::SimpleMove( Vehicle *currentVehicle ):
    m_currentVehicle( currentVehicle )
{
}

void SimpleMove::collisionDetection()
{
}
