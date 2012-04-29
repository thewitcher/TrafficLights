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

void GraphicsScene::addVehicleCounter()
{
    QLCDNumber *counter = NULL;

    QPalette Pal;
    Pal.setColor(QPalette::Normal, QPalette::WindowText, Qt::green);
    Pal.setColor(QPalette::Normal, QPalette::Window, Qt::black);

    // First counter - cross 0
    counter = new QLCDNumber;
    counter->move( QPoint( 280, 1 ) );
    counter->setMaximumSize( 30, 20 );
    counter->setPalette( Pal );
    m_vehicleCouters.append( counter );
    addWidget( counter );

    // Second counter - cross 1
    counter = new QLCDNumber;
    counter->move( QPoint( 1, 480 ) );
    counter->setMaximumSize( 20, 20 );
    counter->setPalette( Pal );
    m_vehicleCouters.append( counter );
    addWidget( counter );

    // Third counter - cross 2
    counter = new QLCDNumber;
    counter->move( QPoint( 265, 490 ) );
    counter->setMaximumSize( 30, 20 );
    counter->setPalette( Pal );
    m_vehicleCouters.append( counter );
    addWidget( counter );

    // Fourth counter - cross 3
    counter = new QLCDNumber;
    counter->move( QPoint( 250, 1049 ) );
    counter->setMaximumSize( 30, 20 );
    counter->setPalette( Pal );
    m_vehicleCouters.append( counter );
    addWidget( counter );

    // Fifth counter - cross 4
    counter = new QLCDNumber;
    counter->move( QPoint( 757, 1049 ) );
    counter->setMaximumSize( 30, 20 );
    counter->setPalette( Pal );
    m_vehicleCouters.append( counter );
    addWidget( counter );

    // Sixth counter - cross 5
    counter = new QLCDNumber;
    counter->move( QPoint( 1305, 495 ) );
    counter->setMaximumSize( 20, 20 );
    counter->setPalette( Pal );
    m_vehicleCouters.append( counter );
    addWidget( counter );

    // Seventh counter - cross 6
    counter = new QLCDNumber;
    counter->move( QPoint( 757, 1 ) );
    counter->setMaximumSize( 30, 20 );
    counter->setPalette( Pal );
    m_vehicleCouters.append( counter );
    addWidget( counter );
}

QVector<QLCDNumber*>& GraphicsScene::allVehicleCounters()
{
    return m_vehicleCouters;
}

/*!
 * It adds crossId and vector with TrafficLight pointers to m_trafficLights map. Also adds to scene new TrafficLight items.
 */
void GraphicsScene::addTrafficLightsToScene( QMap<int, QVector<TrafficLight *> > &junctionsMap,
                                             QVector<Checkpoint*> checkpoinVector )
{
    m_trafficLights = junctionsMap;

    QVector<TrafficLight *> junction;

    uint checkPoint = 0;

    for( int id = 0; id < junctionsMap.count(); id++ )
    {
        junction = junctionsMap.value( id );

        for( int light = 0 ; light < junction.count() ; light++ )
        {
            TrafficLight *item = junction.at( light );
            addItem( item );
            item->setParent( this );
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

void GraphicsScene::setDark( bool dark )
{
    QListIterator<Vehicle*> iterator( m_vehicles );

    Vehicle* vehicle;

    while( iterator.hasNext() )
    {
        vehicle = iterator.next();

        vehicle->setDarkDesign( dark );
#ifdef LIGHTS
        vehicle->setLongLights( dark );
#endif
    }
}
