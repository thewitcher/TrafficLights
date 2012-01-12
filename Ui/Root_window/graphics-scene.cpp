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
void GraphicsScene::addTrafficLightsToScene( QMap<int, QVector<TrafficLight *> > &junctionsMap )
{
    m_trafficLights = junctionsMap;

    QVector<TrafficLight *> junction;

    for( int map = 0; map < junctionsMap.count(); map++ )
    {
        junction = junctionsMap.value( map );

        for( int traffic = 0 ; traffic < junction.count() ; traffic++ )
        {
            addItem( junction.at( traffic ) );
        }
    }
}

/*!
 * Returns map all TrafficLight items.
 */
QMap< int, QVector<TrafficLight*> >& GraphicsScene::allTrafficLights()
{
    return m_trafficLights;
}
