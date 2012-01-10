#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class Checkpoint;
class Vehicle;
class CheckpointManager;
class TrafficLight;

class GraphicsView: public QGraphicsView
{

    Q_OBJECT

public:
    explicit GraphicsView( QWidget *parent = 0 );
    ~GraphicsView();

    void addToScene( Vehicle *item, Checkpoint* initCheckpoint );
    void addToScene( TrafficLight* item, qreal x, qreal y, qreal angle );

private:
    QGraphicsScene *m_scene;
    CheckpointManager *m_checkpointManager;

private slots:
    void initScene();
    void initGraphicsView();
    void createItems();
    void setLights();
    void templateSimpleCross( QVector<qreal> vector, unsigned int id );
    void templatecomplexCross( QVector<qreal> vector, unsigned int id );
    void addVehicle( int speed );
    TrafficLight* addTrafficLight( qreal x = 0, qreal y = 0, qreal angle = 0 );
    void createCheckpointsManager();
};

#endif // GRAPHICSVIEW_H
