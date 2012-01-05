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
    Q_PROPERTY( bool blinkers READ blinkers WRITE switchOnOffBlinkers NOTIFY blinkersChanged )

public:
    explicit Vehicle( QDeclarativeItem *parent = 0 );
    ~Vehicle();

    void setSpeed( int speed );
    bool blinkers();
    QAbstractAnimation* currentAnimation();
    void setPredecessor( Vehicle* predecessor );
    const Vehicle* predecessor() const;
    void setConsquent( Vehicle* consequent );
    const Vehicle* consequent() const;
    bool isVehicleInNextCheckpoint();
    int timeToCollision();

private:
    const Path *m_currentPath;
    int m_speed;
    bool m_blinkers;
    Checkpoint* m_currentCheckpoint;
    QAbstractAnimation* m_currentAnimation;
    Vehicle *m_consequent; // Vehicle in front of this vehicle
    Vehicle *m_predecessor;

    static const int WAIT_ON_PERMISSION;

public slots:
    void init( Checkpoint* initCheckpoint );
    void init();
    void onAnimationFinish();
    void switchOnOffBlinkers( bool blinkers = false ); // Don't use argument. It's not used.
    void checkConsequence();
    void moveAndStop();
    void resumeMove();
    void pauseMove();

signals:
    void blinkersChanged();
};

#endif // VEHICLE_H
