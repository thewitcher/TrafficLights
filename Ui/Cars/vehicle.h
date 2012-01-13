#ifndef VEHICLE_H
#define VEHICLE_H

#include <QDeclarativeItem>
#include "collision-point.h"

class Checkpoint;
class Path;
class QAbstractAnimation;
class GraphicsScene;

/*!
 * @file vehicle.h
 *
 * @brief Base class for all vehicle.
 *
 * @author Marcin Haber
 *
 * Vehicle is a graphics object which can move from one to antoher point. You can animate it and switch on many fetures like
 * different types of lights. To set new car on the scene You need to create new vehicle object and call init with checkpoint which will
 * be the first on vehicle path. Vehicles are created in GraphicsView.
 */
class Vehicle: public QDeclarativeItem
{

    Q_OBJECT
    Q_ENUMS( Blinkers )

public:
    /*!
     * Create Vehicle object.
     *
     * @param parent Sets parent. In constructor transform origin point is set.
     */
    explicit Vehicle( QDeclarativeItem *parent = 0 );
    ~Vehicle();

    /// Enum describing blinkers.
    enum Blinkers { RIGHT_BLINKERS = 90, LEFT_BLINKERS = -90, NO_BLINKERS = 0 };

    /*!
     * Sets vehicle speed. For bigger value of speed car move slower.
     *
     * @param speed Vehicle speed.
     */
    void setSpeed( int speed );
    /*!
     * Returns current animation associated with vehicle.
     */
    QAbstractAnimation* currentAnimation();
    /*!
     * Returns collisionPoint. It works like a bumper.
     */
    CollisionPoint collisionPoint() const;
    /*!
     * Sets pointer to scene where vehicle has added to.
     *
     * @param scene Scene which contains vehicle.
     */
    void setParentScene( GraphicsScene* scene );
    /*!
     * Returns scene which contains vehicle.
     */
    GraphicsScene* parentScene() const;

private:
    /// It is a description of current path to new checkpoint.
    const Path *m_currentPath;
    /// Vehicle speed. If this value is smaller then vehicle move faster.
    int m_speed;
    /// Current position of vehicle.
    Checkpoint* m_currentCheckpoint;
    /// Animation for this vehicle.
    QAbstractAnimation* m_currentAnimation;
    /// Pointer to scene the vehicle has added to.
    GraphicsScene *m_parentScene;

    /// After this time vehicle will ask for permission to move again.
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
