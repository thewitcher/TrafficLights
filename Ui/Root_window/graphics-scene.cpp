#include "graphics-scene.h"
#include "../Cars/vehicle.h"
#include "../Lights/trafficlight.h"

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
void GraphicsScene::addTrafficLightsToScene( QMap<int, QVector<TrafficLight *> > &junctionsMap,
                                             QVector<Checkpoint*> checkpoinVector )
{
    m_trafficLights = junctionsMap;

    QVector<TrafficLight *> junction;

    unsigned int checkPoint = 0;

    for( int id = 0; id < junctionsMap.count(); id++ )
    {
        junction = junctionsMap.value( id );

        for( int light = 0 ; light < junction.count() ; light++ )
        {
            TrafficLight *item = junction.at( light );
            addItem( item );
            item->createCheckpoint( checkpoinVector.at( checkPoint ) );
            checkPoint++;
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
