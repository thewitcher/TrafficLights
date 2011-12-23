#ifndef VEHICLE_H
#define VEHICLE_H

#include <QDeclarativeItem>

class Checkpoint;
class Path;

/*!
 * Vehicle is a graphics object which can move form one to another checkpoint. To set new vehicles on the scene You need to
 * create new vehicle object and then call init with checkpoint which will be the first on vehicle path. Vehicles are created
 * in GraphicsView.
 */
class Vehicle: public QDeclarativeItem
{

    Q_OBJECT
    Q_PROPERTY( bool blinkers READ blinkers WRITE setBlinkers NOTIFY blinkersChanged )

public:
    explicit Vehicle( QDeclarativeItem *parent = 0 );

    void init( const Checkpoint* initCheckpoint );
    void setSpeed( double speed );
    bool blinkers();

private:
    const Path *m_currentPath;
    double m_speed;
    bool m_blinkers;

public slots:
    void onAnimationFinish();
    void setBlinkers( bool blinkers = false );

signals:
    void blinkersChanged();
};

#endif // VEHICLE_H
