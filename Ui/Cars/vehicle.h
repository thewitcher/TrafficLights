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

    void init( const Checkpoint* initCheckpoint );
    void setSpeed( double speed );
    bool blinkers();

private:
    const Path *m_currentPath;
    double m_speed;
    bool m_blinkers;
    QAbstractAnimation* m_currentAnimation;

public slots:
    void onAnimationFinish();
    void switchOnOffBlinkers( bool blinkers = false ); // Don't use argument. It's not used.

signals:
    void blinkersChanged();
};

#endif // VEHICLE_H
