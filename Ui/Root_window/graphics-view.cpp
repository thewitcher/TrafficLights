#include "graphics-view.h"
#include "../Logger/logger.h"

GraphicsView::GraphicsView( QWidget *parent ):
    QGraphicsView( parent )
{
    initScene();
}

void GraphicsView::initScene()
{
    LOG_INFO( "Start: %s", __FUNCTION__ );

    m_scene = new QGraphicsScene( this );

    setScene(m_scene);

    LOG_INFO( "End: %s", __FUNCTION__ );
}
