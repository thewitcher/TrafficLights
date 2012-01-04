#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class Checkpoint;
class Vehicle;
class CheckpointManager;

class GraphicsView: public QGraphicsView
{

    Q_OBJECT

public:
    explicit GraphicsView( QWidget *parent = 0 );
    ~GraphicsView();

    void addToScene( Vehicle *item, const Checkpoint* initCheckpoint );

private:
    QGraphicsScene *m_scene;
    CheckpointManager *m_checkpointManager;

private slots:
    void initScene();
    void initGraphicsView();
    void createItems();
    void addVehicle( double speed );
    void createCheckpointsManager();
};

#endif // GRAPHICSVIEW_H
