#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class Checkpoint;
class Vehicle;
class CheckpointManager;
class GraphicsScene;
class JunctionManager;
class EventTimer;

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
#ifdef EVENTS
    EventTimer* m_eventTimer;
#endif

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
    void addVehicle( int speed, bool dark = false, const QString& type = "MotorCar" );
    void createJunctionManager();
    void createConnections();
    void changeBackgroundPixmap( bool dark = false );
    void setDay();
    void setNight();
#ifdef EVENTS
    void initEventTimer();
#endif
};

#endif // GRAPHICSVIEW_H
