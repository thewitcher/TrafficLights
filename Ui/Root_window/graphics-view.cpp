#include "graphics-view.h"
#include "../Logger/logger.h"
#include "qml-helper.h"
#include "../Cars/vehicle.h"
#include "../Checkpoints_manager/checkpoint-manager.h"
#include <QGraphicsItem>

GraphicsView::GraphicsView( QWidget *parent ):
    QGraphicsView( parent )
{
    initScene();
    initGraphicsView();
    createItems();
}

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

void GraphicsView::addToScene( Vehicle *item, const Checkpoint *initCheckpoint )
{
    LOG_INFO( "Start: %s", __FUNCTION__ );

    scene()->addItem( item );
    item->setPos( initCheckpoint->posX(), initCheckpoint->posY() );

    item->init( initCheckpoint );

    LOG_INFO( "Add item on position: (%f, %f)", initCheckpoint->posX(), initCheckpoint->posY() );
}

void GraphicsView::createItems()
{
    // Car with normal speed (1)
//    Vehicle *newVehicle = QmlHelper::createVehicleFromQml( "CarDesign" );
      Vehicle *newVehicle = QmlHelper::createVehicleFromQml( "Auto" );
    newVehicle->setSpeed( 1 );

    if( newVehicle != NULL )
    {
        addToScene( newVehicle, CheckpointManager::checkpointManagerInstance().checkpointById( 0 ) );

        LOG_INFO( "%s was created and added to scene", newVehicle->objectName().toLatin1().data() )
    }

    QMetaObject::invokeMethod(newVehicle, "turnOnLongLight");
    QMetaObject::invokeMethod(newVehicle, "turnOnSignal");

    // Car with normal speed (1.5)
//    newVehicle = QmlHelper::createVehicleFromQml( "CarDesign" );
      newVehicle = QmlHelper::createVehicleFromQml( "Auto" );
    newVehicle->setSpeed( 1.5 );

    if( newVehicle != NULL )
    {
        addToScene( newVehicle, CheckpointManager::checkpointManagerInstance().checkpointById( 0 ) );

        LOG_INFO( "%s was created and added to scene", newVehicle->objectName().toLatin1().data() )
    }

    // Car with normal speed (2)
//    newVehicle = QmlHelper::createVehicleFromQml( "CarDesign" );
    newVehicle = QmlHelper::createVehicleFromQml( "Auto" );
    newVehicle->setSpeed( 2 );

    if( newVehicle != NULL )
    {
        addToScene( newVehicle, CheckpointManager::checkpointManagerInstance().checkpointById( 0 ) );

        LOG_INFO( "%s was created and added to scene", newVehicle->objectName().toLatin1().data() )
    }

    // Car with normal speed (2.5)
//    newVehicle = QmlHelper::createVehicleFromQml( "CarDesign" );
    newVehicle = QmlHelper::createVehicleFromQml( "Auto" );
    newVehicle->setSpeed( 2.5 );

    if( newVehicle != NULL )
    {
        addToScene( newVehicle, CheckpointManager::checkpointManagerInstance().checkpointById( 0 ) );

        LOG_INFO( "%s was created and added to scene", newVehicle->objectName().toLatin1().data() )
    }

    // Car with normal speed (3)
//    newVehicle = QmlHelper::createVehicleFromQml( "CarDesign" );
    newVehicle = QmlHelper::createVehicleFromQml( "Auto" );
    newVehicle->setSpeed( 3 );

    if( newVehicle != NULL )
    {
        addToScene( newVehicle, CheckpointManager::checkpointManagerInstance().checkpointById( 0 ) );

        LOG_INFO( "%s was created and added to scene", newVehicle->objectName().toLatin1().data() )
    }

    // Car with normal speed (3.5)
//    newVehicle = QmlHelper::createVehicleFromQml( "CarDesign" );
    newVehicle = QmlHelper::createVehicleFromQml( "Auto" );
    newVehicle->setSpeed( 3.5 );

    if( newVehicle != NULL )
    {
        addToScene( newVehicle, CheckpointManager::checkpointManagerInstance().checkpointById( 0 ) );

        LOG_INFO( "%s was created and added to scene", newVehicle->objectName().toLatin1().data() )
    }

    // Car with normal speed (4)
//    newVehicle = QmlHelper::createVehicleFromQml( "CarDesign" );
    newVehicle = QmlHelper::createVehicleFromQml( "Auto" );
    newVehicle->setSpeed( 4 );

    if( newVehicle != NULL )
    {
        addToScene( newVehicle, CheckpointManager::checkpointManagerInstance().checkpointById( 0 ) );

        LOG_INFO( "%s was created and added to scene", newVehicle->objectName().toLatin1().data() )
    }

    // Car with normal speed (4.5)
//    newVehicle = QmlHelper::createVehicleFromQml( "CarDesign" );
    newVehicle = QmlHelper::createVehicleFromQml( "Auto" );
    newVehicle->setSpeed( 4.5 );

    if( newVehicle != NULL )
    {
        addToScene( newVehicle, CheckpointManager::checkpointManagerInstance().checkpointById( 0 ) );

        LOG_INFO( "%s was created and added to scene", newVehicle->objectName().toLatin1().data() )
    }

    // Car with normal speed (5)
//    newVehicle = QmlHelper::createVehicleFromQml( "CarDesign" );
    newVehicle = QmlHelper::createVehicleFromQml( "Auto" );
    newVehicle->setSpeed( 5 );

    if( newVehicle != NULL )
    {
        addToScene( newVehicle, CheckpointManager::checkpointManagerInstance().checkpointById( 0 ) );

        LOG_INFO( "%s was created and added to scene", newVehicle->objectName().toLatin1().data() )
    }
}
