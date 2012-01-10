#include "graphics-view.h"
#include "../Logger/logger.h"
#include "qml-helper.h"
#include "../Cars/vehicle.h"
#include "../Checkpoints_manager/checkpoint-manager.h"
#include "vehicle-static-container.h"
#include <QTimer>

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

void GraphicsView::createItems()
{
    static int speed = 0;

    if( speed <= 15 )
    {
        int currentSpeed = ( speed % 5 ) + 1;
        addVehicle( currentSpeed );

        QTimer::singleShot( 5000, this, SLOT(createItems()) );
    }

    speed += 1;
}
