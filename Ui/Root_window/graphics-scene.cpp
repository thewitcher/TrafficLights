#include "graphics-scene.h"
#include "../Cars/vehicle.h"
#include "../Ui/Lights/trafficlight.h"

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

/*!
 * It adds crossId and vector with TrafficLight pointers to m_trafficLights map. Also adds to scene new TrafficLight items.
 */
void GraphicsScene::addTrafficLightsToScene( int crossID, QVector<TrafficLight*> vector )
{
    m_trafficLights.insert( crossID, vector );

    for( int vectorCount = 0; vectorCount < vector.count(); vectorCount++ )
    {
        addItem( vector.at( vectorCount ) );
    }
}

/*!
 * Returns map all TrafficLight items.
 */
QMap< int, QVector<TrafficLight*> >& GraphicsScene::allTrafficLights()
{
    return m_trafficLights;
}
