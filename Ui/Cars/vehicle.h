#ifndef VEHICLE_H
#define VEHICLE_H

#include <QDeclarativeItem>

class Checkpoint;
class Path;
class QAbstractAnimation;

/*!
 * Vehicle is a graphics object which can move form one to another checkpoint. To set new vehicles on the scene You need to
 * create new vehicle object and then call init with checkpoint which will be the first on vehicle path. Vehicles are created
 * in GraphicsView.
 */
class Vehicle: public QDeclarativeItem
{

    Q_OBJECT
    Q_PROPERTY( Blinkers blinkers READ blinkers WRITE setBlinkers )
    Q_PROPERTY( bool longLigths READ longLigths WRITE setLongLights )
    Q_ENUMS( Blinkers )

public:
    explicit Vehicle( QDeclarativeItem *parent = 0 );
    ~Vehicle();

    enum Blinkers { RIGHT_BLINKERS, LEFT_BLINKERS, NO_BLINKERS };

    void setSpeed( int speed );
    Blinkers blinkers();
    bool longLigths();
    void setLongLights( bool light );
    QAbstractAnimation* currentAnimation();

private:
    const Path *m_currentPath;
    int m_speed;
    Blinkers m_blinkers;
    Checkpoint* m_currentCheckpoint;
    QAbstractAnimation* m_currentAnimation;
    bool m_longLights;

    static const int WAIT_ON_PERMISSION;

public slots:
    void init( Checkpoint* initCheckpoint );
    void init();
    void onAnimationFinish();
    void setBlinkers( Blinkers blinkers = NO_BLINKERS );
    void resumeMove();
    void pauseMove();
};

#endif // VEHICLE_H
