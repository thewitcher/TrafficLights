#include "graphics-view.h"
#include "../Logger/logger.h"
#include "qml-helper.h"
#include "../Cars/vehicle.h"
#include "../Lights/trafficlight.h"
#include "../Checkpoints_manager/checkpoint-manager.h"
#include "vehicle-static-container.h"
#include <QTimer>

int GraphicsView::S_NEW_CAR_FREQUENCY = 5000;
int GraphicsView::S_CAR_COUNT = 15;

/*!
 * GraphicsView is a subclass of QGraphicsView. It was created for convenience. In constructor there are already four method, which
 * initialize scene and graphics view. For more info see appriopriate method description.
 */
GraphicsView::GraphicsView( QWidget *parent ):
    QGraphicsView( parent ),
    m_scene( NULL ),
    m_checkpointManager( NULL )
{
    initScene();
    initGraphicsView();
    createCheckpointsManager();
    setLights();
    createItems();
}

GraphicsView::~GraphicsView()
{
    if( m_checkpointManager != NULL )
    {
        delete m_checkpointManager;
    }
}

/*!
 * Creates new scene and adds it to view. It also sets some properties such size and item index method.
 */
void GraphicsView::initScene()
{
    LOG_INFO( "Start: %s", __FUNCTION__ );

    m_scene = new QGraphicsScene( this );
    /*!
     * This is set to NoIndex becouse of many animations on the scene.
     */
    m_scene->setItemIndexMethod( QGraphicsScene::NoIndex );
    /*!
     * Size of main png file.
     */
    m_scene->setSceneRect( 0, 0, 1326, 1070 );

    setScene(m_scene);

    LOG_INFO( "End: %s", __FUNCTION__ );
}

/*!
 * Sets some view properties.
 */
void GraphicsView::initGraphicsView()
{
    LOG_INFO( "Start: %s", __FUNCTION__ );

    viewport()->setObjectName( "viewPortWidget" );

    setRenderHint( QPainter::Antialiasing );
    setBackgroundBrush( QPixmap( ":/graphics/viewport_background" ) );
    setCacheMode( QGraphicsView::CacheBackground );
    setDragMode( QGraphicsView::ScrollHandDrag );
    resize( 1326, 1070 );
    setMaximumSize( 1340, 1084 );
    //scale( 2, 2 );

    LOG_INFO( "End: %s", __FUNCTION__ );
}

/*!
 * You can add new vehicle to the scene in initCheckpoint. This function is used in createItems method
 * and You don't need to use it manually.
 */
void GraphicsView::addToScene( Vehicle *item, Checkpoint *initCheckpoint )
{
    LOG_INFO( "Start: %s", __FUNCTION__ );

    scene()->addItem( item );
    item->setPos( initCheckpoint->posX(), initCheckpoint->posY() );

    item->init( initCheckpoint );

    LOG_INFO( "Add item on position: (%f, %f)", initCheckpoint->posX(), initCheckpoint->posY() );
}
/*!
 * This is overload function. It adds new item to the scene in appropriate coordinates, properly x and y.
 * Also set item in appropriate direction.
 */
void GraphicsView::addToScene( TrafficLight *item, qreal x, qreal y, qreal angle )
{
    LOG_INFO( "Start: %s", __FUNCTION__ );

    scene()->addItem( item );

    if( angle != 0 )
    {
        item->setRotation( angle );
    }

    item->setPos( x, y );

    LOG_INFO( "Add item on position: (%f, %f)", x, y );
}

void GraphicsView::createCheckpointsManager()
{
    m_checkpointManager = new CheckpointManager;
}

/*!
 * It creates new vehicle from qml file and adds it to the scene.
 */
void GraphicsView::addVehicle( int speed )
{
    Vehicle *newVehicle = QmlHelper::createVehicleFromQml( "MotorCar" );
    newVehicle->setSpeed( speed );

    if( newVehicle != NULL )
    {
        addToScene( newVehicle, m_checkpointManager->checkpointById( 36 ) );

        VehicleStaticContainer::VEHICLES.append( newVehicle );

        LOG_INFO( "%s was created and added to scene", newVehicle->objectName().toLatin1().data() )
    }
}

/*!
 * It creates new TrafficLight object from qml file and adds this item to the scene.
 */
TrafficLight* GraphicsView::addTrafficLight( qreal x, qreal y, qreal angle )
{
    TrafficLight *newLight = QmlHelper::createLightsFromQml( "Lights" );

    if( newLight != NULL )
    {
        addToScene( newLight, x, y, angle );

        LOG_INFO( "%s was created and added to scene", newLight->objectName().toLatin1().data() )
    }

    return newLight;
}

void GraphicsView::createItems()
{
    static int count = 0;

    if( count <= S_CAR_COUNT )
    {
        int currentSpeed = ( count % 5 ) + 1;
        addVehicle( currentSpeed );

        QTimer::singleShot( S_NEW_CAR_FREQUENCY, this, SLOT(createItems()) );
    }

    count += 1;
}

/*!
 * This function sets coordinates for all TrafficLight items in cross.
 */

void GraphicsView::setLights()
{

    QVector<qreal> cross1;           /* Cross 1 */
    cross1 << 286 << 90 << 0
              << 372 << 90 << 0
                 << 380 << -8.5 << -90
                    << 160 << 72 << 90;
    templateSimpleCross( cross1, 1 );

    QVector<qreal> cross2;           /* Cross 2 */
    cross2 << 101 << 471 << -90
              << 101 << 386 << -90
                 << 3.5 << 376 << 180
                    << 88 << 600 << 0;
    templateSimpleCross( cross2, 2 );

    QVector<qreal> cross3;           /* Cross 3 */
    cross3 << 286.5 << 372 << 180                   /* 3 a */
              << 170 << 372 << 180
                 << 150 << 372 << 180
           << 158 << 469 << 90                      /* 3 b */
              << 158 << 583 << 90
                 << 158 << 603 << 90
           << 254 << 599 << 0                       /* 3 c */
              << 370 << 599 << 0
                 << 390 << 599 << 0
           << 381 << 501 << -90                     /* 3 d */
              << 381 << 386 << -90
                 << 381 << 366 << -90;
    templatecomplexCross( cross3, 3 );

    QVector<qreal> cross4;           /* Cross 4 */
    cross4 << 255 << 940 << 180
              << 171 << 940 << 180
                 << 160 << 1038 << 90
                    << 385 << 955 << -90;
    templateSimpleCross( cross4, 4 );

    QVector<qreal> cross5;           /* Cross 5 */
    cross5 << 751 << 940 << 180
              << 666 << 940 << 180
                 << 652 << 1038 << 90
                    << 880 << 955 << -90;
    templateSimpleCross( cross5, 5 );

    QVector<qreal> cross6;           /* Cross 6 */
    cross6 << 1212 << 500 << 90
              << 1212 << 585 << 90
                 << 1307 << 596 << 0
                    << 1227 << 370 << 180;
    templateSimpleCross( cross6, 6 );

    QVector<qreal> cross7;           /* Cross 7 */
    cross7 << 780 << 90 << 0
              << 865 << 90 << 0
                 << 883 << -8.5 << -90
                    << 652.5 << 72 << 90;
    templateSimpleCross( cross7, 7 );
}

/*!
 * It's simple template for creates TrafficLight item for simple cross. Additionaly writes to static member S_LIGHTS
 * cross id and vector which contain TrafficLight item.
 */

void GraphicsView::templateSimpleCross( QVector<qreal> vector, unsigned int id )
{
    QVector<TrafficLight*> container;

    if( vector.count() == 12 )
    {
        TrafficLight * light1 = addTrafficLight( vector.at(0), vector.at(1), vector.at(2) );
        light1->setDirection( light1, TrafficLight::LEFT );

        TrafficLight * light2 = addTrafficLight( vector.at(3), vector.at(4), vector.at(5) );
        light2->setDirection( light2, TrafficLight::RIGHT );

        TrafficLight * light3 = addTrafficLight( vector.at(6), vector.at(7), vector.at(8) );
        light3->setDirection( light3, TrafficLight::STRAIGHT_AND_LEFT );

        TrafficLight * light4 = addTrafficLight( vector.at(9), vector.at(10), vector.at(11) );
        light4->setDirection( light4, TrafficLight::STRAIGHT_AND_RIGHT );

        light1->changeState();   // for test
        container << light1 << light2 << light3 << light4;
        VehicleStaticContainer::S_LIGHTS.insert( id, container );
    }
}

/*!
 * It's more complex template which creates TrafficLigth item for big crosses. Additionaly writes to static member S_LIGHTS
 * cross id and vector which contain TrafficLight item.
 */

void GraphicsView::templatecomplexCross( QVector<qreal> vector, unsigned int id )
{
    if( vector.count() == 36 ){

        unsigned int x = 0;
        unsigned int y = 1;
        unsigned int angle = 2;
        QVector<TrafficLight*> container;

        for(unsigned int i = 0; i < 4; i++)
        {
            TrafficLight * light1 = addTrafficLight( vector.at( x ), vector.at( y ), vector.at( angle ) );
            light1->setDirection( light1, TrafficLight::LEFT );

            x += 3, y += 3, angle += 3;

            TrafficLight * light2 = addTrafficLight( vector.at( x ), vector.at( y ), vector.at( angle ) );
            light2->setDirection( light2, TrafficLight::STRAIGHT );

            x += 3, y += 3, angle += 3;

            TrafficLight * light3 = addTrafficLight( vector.at( x ), vector.at( y ), vector.at( angle ) );
            light3->setDirection( light3, TrafficLight::RIGHT );

            x += 3, y += 3, angle += 3;

            container << light1 << light2 << light3;
        }

        VehicleStaticContainer::S_LIGHTS.insert( id, container );
    }
}
