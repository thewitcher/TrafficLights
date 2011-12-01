#ifndef VEHICLE_H
#define VEHICLE_H

#include <QGraphicsWidget>

class Checkpoint;
class Path;

/*!
 * Vehicle is a graphics object which can move form one to another checkpoint. To set new vehicles on the scene You need to
 * create new vehicle object and then call init with checkpoint which will be the first on vehicle path. Vehicles are created
 * in GraphicsView.
 */
class Vehicle: public QGraphicsWidget
{

    Q_OBJECT

public:
    explicit Vehicle( QGraphicsItem *parent = 0 );

    void init( const Checkpoint* initCheckpoint );

private:
    const Path *m_currentPath;

private slots:
    void onAnimationFinish();
};

#endif // VEHICLE_H
