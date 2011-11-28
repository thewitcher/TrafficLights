#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class GraphicsView: public QGraphicsView
{

    Q_OBJECT

public:
    explicit GraphicsView( QWidget *parent = 0 );

    void addToScene( QGraphicsItem *item, qreal x, qreal y );

private:
    QGraphicsScene *m_scene;

    void initScene();
    void initGraphicsView();
    void createItems();
};

#endif // GRAPHICSVIEW_H
