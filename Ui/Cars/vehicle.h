#ifndef VEHICLE_H
#define VEHICLE_H

#include <QDeclarativeItem>
#include "collision-point.h"

class Checkpoint;
class Path;
class QAbstractAnimation;
class GraphicsScene;

/*!
 * Vehicle is a graphics object which can move form one to another checkpoint. To set new vehicles on the scene You need to
 * create new vehicle object and then call init with checkpoint which will be the first on vehicle path. Vehicles are created
 * in GraphicsView.
 */
class Vehicle: public QDeclarativeItem
{

    Q_OBJECT
    Q_ENUMS( Blinkers )

public:
    explicit Vehicle( QDeclarativeItem *parent = 0 );
    ~Vehicle();

    enum Blinkers { RIGHT_BLINKERS = 90, LEFT_BLINKERS = -90, NO_BLINKERS = 0 };

    void setSpeed( int speed );
    QAbstractAnimation* currentAnimation();
    CollisionPoint collisionPoint() const;
    void setParentScene( GraphicsScene* scene );
    GraphicsScene* parentScene() const;

private:
    const Path *m_currentPath;
    int m_speed;
    Checkpoint* m_currentCheckpoint;
    QAbstractAnimation* m_currentAnimation;
    GraphicsScene *m_parentScene;

    static const int WAIT_ON_PERMISSION;

public slots:
    void init( Checkpoint* initCheckpoint );
    void init();
    void onAnimationFinish();
    virtual void setBlinkers( Blinkers blinkers = NO_BLINKERS );
    virtual void setLongLights( bool longLight = false );
    virtual void setBackLights( bool backLight = false );
    void resumeMove();
    void pauseMove();
};

#endif // VEHICLE_H
