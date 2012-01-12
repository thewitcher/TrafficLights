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

private slots:
    void initScene();
    void createDeployTrafficLights();
    void initGraphicsView();
    void createItems();
    void createCheckpointsManager();
    void addVehicle( int speed );
    void createJunctionManager();
};

#endif // GRAPHICSVIEW_H
