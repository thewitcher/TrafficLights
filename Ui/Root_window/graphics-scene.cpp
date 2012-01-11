#include "graphics-scene.h"
#include "../Cars/vehicle.h"

GraphicsScene::GraphicsScene( QObject *parent ):
    QGraphicsScene( parent )
{
}

void GraphicsScene::addVehicle( Vehicle *newVehicle )
{
    m_vehicles.append( newVehicle );

    newVehicle->setParentScene( this );

    addItem( newVehicle );
}

QList<Vehicle*>& GraphicsScene::allVehicles()
{
    return m_vehicles;
}
