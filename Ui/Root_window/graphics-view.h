#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class Checkpoint;
class Vehicle;
class CheckpointManager;
class GraphicsScene;
class JunctionManager;

class GraphicsView: public QGraphicsView
{

    Q_OBJECT

public:
    explicit GraphicsView( QWidget *parent = 0 );
    ~GraphicsView();

    void addToScene( Vehicle *item, Checkpoint* initCheckpoint );

private:
    GraphicsScene *m_scene;
    CheckpointManager *m_checkpointManager;
    JunctionManager *m_junctionManager;

    static int S_NEW_CAR_FREQUENCY;
    static int S_CAR_COUNT;
    static int S_BUS_COUNT;
    static int S_CAR_SPEED;
    static int S_BUS_SPEED;

private slots:
    void initScene();
    void createDeployTrafficLights();
    void initGraphicsView();
    void createItems();
    void createCheckpointsManager();
    void addVehicle( int speed );
    void addBus( int speed );
    void createJunctionManager();
    void createConnections();
};

#endif // GRAPHICSVIEW_H
