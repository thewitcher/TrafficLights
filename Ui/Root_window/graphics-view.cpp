#include "graphics-view.h"
#include "../Logger/logger.h"
#include "qml-helper.h"
#include "../Cars/vehicle.h"
#include "../Checkpoints_manager/checkpoint-manager.h"
#include "../TrafficLights_manager/deploy-trafficlights.h"
#include "graphics-scene.h"
#include "../TrafficLights_manager/junction-manager.h"
#include "event-timer.h"
#include <QTimer>


int GraphicsView::S_NEW_CAR_FREQUENCY = 5000;
int GraphicsView::S_CAR_COUNT = 50;
int GraphicsView::S_CAR_SPEED = 5;
int GraphicsView::S_BUS_SPEED = 5;
int GraphicsView::S_BUS_COUNT = 4;

/*!
 * GraphicsView is a subclass of QGraphicsView. It was created for convenience. In constructor there are already four method, which
 * initialize scene and graphics view. For more info see appriopriate method description.
 */
GraphicsView::GraphicsView( QWidget *parent ):
    QGraphicsView( parent ),
    m_scene( NULL ),
    m_checkpointManager( NULL ),
    m_junctionManager( NULL )
{
    initScene();
    initGraphicsView();
    createCheckpointsManager();
    createDeployTrafficLights();
    createJunctionManager();
    createConnections();
    initEventTimer();
    createItems();
}

GraphicsView::~GraphicsView()
{
    if( m_checkpointManager != NULL )
    {
        delete m_checkpointManager;
    }

    if( m_junctionManager != NULL )
    {
        delete m_junctionManager;
    }
}

void GraphicsView::createConnections()
{
    connect( m_checkpointManager, SIGNAL(checkpointReached(uint,uchar,Vehicle*)),
             m_junctionManager, SLOT(routeToAppropriateJunction(uint,uchar,Vehicle*)) );
}

/*!
 * Creates new scene and adds it to view. It also sets some properties such size and item index method.
 */
void GraphicsView::initScene()
{
    LOG_INFO( "Start: %s", __FUNCTION__ );

    m_scene = new GraphicsScene( this );
    /*!
     * This is set to NoIndex becouse of many animations on the scene.
     */
    m_scene->setItemIndexMethod( QGraphicsScene::NoIndex );
    /*!
     * Size of main png file.
     */
    m_scene->setSceneRect( 0, 0, 1326, 1070 );
    m_scene->setObjectName( "graphicsScene" );

    setScene(m_scene);

    QTimer::singleShot(5000, m_scene, SLOT(setDark()));

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
    changeBackgroundPixmap( false );
    setCacheMode( QGraphicsView::CacheBackground );
    setDragMode( QGraphicsView::ScrollHandDrag );
    resize( 1326, 1070 );
    setMaximumSize( 1340, 1084 );
    //scale( 2, 2 );

    LOG_INFO( "End: %s", __FUNCTION__ );
}

void GraphicsView::changeBackgroundPixmap( bool dark )
{
    if( dark )
    {
        setBackgroundBrush( QPixmap( ":/graphics/darkBackground" ) );
    }
    else
    {
        setBackgroundBrush( QPixmap( ":/graphics/brightBackground" ) );
    }
}

/*!
 * You can add new vehicle to the scene in initCheckpoint. This function is used in createItems method
 * and You don't need to use it manually.
 */
void GraphicsView::addToScene( Vehicle *item, Checkpoint *initCheckpoint )
{
    LOG_INFO( "Start: %s", __FUNCTION__ );

    m_scene->addVehicle( item );

    item->setPos( initCheckpoint->posX(), initCheckpoint->posY() );

    item->init( initCheckpoint );

    LOG_INFO( "Add item on position: (%f, %f)", initCheckpoint->posX(), initCheckpoint->posY() );
}

void GraphicsView::createCheckpointsManager()
{
    m_checkpointManager = new CheckpointManager;
}

/*!
 * It calls function from GraphicsScene - addTrafficLightsToScene with relevant arguments.
 */
void GraphicsView::createDeployTrafficLights()
{
    DeployTrafficLights deploy( m_checkpointManager );
    QMap< int, QVector<TrafficLight*> > map = deploy.trafficLightsMap();

    m_scene->addTrafficLightsToScene( map, deploy.allCheckpointForLights() );
}

/*!
 * It creates new vehicle from qml file and adds it to the scene.
 */
void GraphicsView::addVehicle( int speed, bool dark, const QString &type )
{
    Vehicle *newVehicle = QmlHelper::createVehicleFromQml( type );
    newVehicle->setSpeed( speed );
    newVehicle->setDarkDesign( dark );
    newVehicle->setLongLights( dark );

    if( newVehicle != NULL )
    {
        addToScene( newVehicle, m_checkpointManager->checkpointById( 82 ) );

        LOG_INFO( "%s was created and added to scene", newVehicle->objectName().toLatin1().data() )
    }
}

void GraphicsView::createItems()
{
    static int carCount = 0;
    static int busCount = 0;

    bool createBus = false;
    bool dark = false;

    if( m_eventTimer->isDark() )
    {
        dark = true;
    }

    if( carCount < S_CAR_COUNT )
    {
        addVehicle( S_CAR_SPEED, dark, "MotorCar" );

        carCount++;

        QTimer::singleShot( S_NEW_CAR_FREQUENCY, this, SLOT(createItems()) );
    }
    else
    {
        createBus = true;
    }

    if( ( createBus == true ) && ( busCount < S_BUS_COUNT ) )
    {
        addVehicle( S_BUS_SPEED, dark, "Bus" );

        busCount++;

        QTimer::singleShot( S_NEW_CAR_FREQUENCY, this, SLOT(createItems()) );
    }
}

void GraphicsView::createJunctionManager()
{   
    m_scene->addVehicleCounter();

    m_junctionManager = new JunctionManager( m_scene->allTrafficLights(), m_scene->allVehicleCounters() );
}

void GraphicsView::initEventTimer()
{
    m_eventTimer = new EventTimer( this );
    connect( m_eventTimer, SIGNAL(day()), this, SLOT(setDay()) );
    connect( m_eventTimer, SIGNAL(night()), this, SLOT(setNight()));

    m_eventTimer->startDayTimeTimer();
}

void GraphicsView::setDay()
{
    changeBackgroundPixmap( false );
    m_scene->setDark( false );
}

void GraphicsView::setNight()
{
    changeBackgroundPixmap( true );
    m_scene->setDark( true );
}
