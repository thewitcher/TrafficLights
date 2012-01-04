#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class Checkpoint;
class Vehicle;

class GraphicsView: public QGraphicsView
{

    Q_OBJECT

public:
    explicit GraphicsView( QWidget *parent = 0 );

    void addToScene( Vehicle *item, const Checkpoint* initCheckpoint );

private:
    QGraphicsScene *m_scene;

private slots:
    void initScene();
    void initGraphicsView();
    void createItems();
    void addVehicle( double speed );
};

#endif // GRAPHICSVIEW_H
