#include "graphics-view.h"
#include "../Logger/logger.h"
#include "qml-helper.h"
#include <QGraphicsItem>
#include <QGraphicsWidget>

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

    LOG_INFO( "End: %s", __FUNCTION__ );
}

void GraphicsView::addToScene( QGraphicsItem *item, qreal x, qreal y )
{
    LOG_INFO( "Start: %s", __FUNCTION__ );

    scene()->addItem( item );
    item->setPos( x, y );

    LOG_INFO( "Add item on position: (%f, %f)", x, y );
}

void GraphicsView::createItems()
{
    QGraphicsWidget *graphicsWidget = QmlHelper::createGraphicsWidgetFromQml( "CarDesign" );

    if( graphicsWidget != NULL )
    {
        addToScene( graphicsWidget, 30, 100 );

        LOG_INFO( "%s was created and added to scene", graphicsWidget->objectName().toLatin1().data() )
    }
}
