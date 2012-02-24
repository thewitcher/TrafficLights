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
    enum VehicleDirection { Unknown = 0, Horizontal = 1, Vertical = 2 };

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
    QSize size() const;
    /*!
     * Base for every vehicle is square 20x20. Normal position is a top right point of this square. But sometimes
     * there is need to have modified position becouse of other size of vehicle. For example bus is bigger than
     * this square, so his position is move to right top side. This new position is counted from simply formula.
     */
    QPoint topLeftPoint() const;
    QPoint bottomRightPoint() const;
    void setCheckCollisions( bool check = true );
    bool checkCollisions() const;
    VehicleDirection direction() const;
    virtual void setDarkDesign( bool dark = false );

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
    bool m_first;
    bool m_checkCollisions;

    /// After this time vehicle will ask for permission to move again.
    static const int WAIT_ON_PERMISSION;

public slots:
    /*!
     * Initialises vehicle on approriate position and chose random path for it.
     *
     * @param initCheckpoint From this point vehicle gets new path. Vehicle also get position from this checkpoint.
     */
    void init( Checkpoint* initCheckpoint );
    /*!
     * This is reimplementaion of init() function:
     *
     * init() = init( m_currentCheckpoint )
     */
    void init();
    /*!
     * When animation is finished this slot is called. It initialises vehicle with new checkpoint.
     */
    void onAnimationFinish();
    /*!
     * In this implementation this method does nothing.
     *
     * @param blinkers Left, right or no blinkers.
     */
    virtual void setBlinkers( Blinkers blinkers = NO_BLINKERS );
    /*!
     * In this implementation this method does nothing.
     *
     * @param longLight Switch on or off
     */
    virtual void setLongLights( bool longLight = false );
    /*!
     * In this implementation this method does nothing.
     *
     * @param backLight Switch on or off
     */
    virtual void setBackLights( bool backLight = false );
    /*!
     * If animation is paused the resumes animation.
     */
    void resumeMove();
    /*!
     * If animation is running the pauses animation.
     */
    void pauseMove();
};

#endif // VEHICLE_H
