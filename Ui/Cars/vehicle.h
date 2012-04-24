#ifndef VEHICLE_H
#define VEHICLE_H

#include <QDeclarativeItem>
#include <QTime>
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
    /// Vehicle can be in two type of direction: horizontal and vertical. There is a bonus enum to set if any error will happend.
    enum VehicleDirection { Unknown = 0, Horizontal = 1, Vertical = 2 };

    /// This static variable is used to give new unique id to new car in constructor
    static int S_VEHICLE_ID;

    /*!
     * Sets vehicle speed. For bigger value of speed car move slower. There is no checking that speed value is less than 0 in order
     * to increase performance, so You need to be care about this. We have checked that value 0 will crash program, values less than
     * 0 can behave very strench. We preffer to use values from 1 to 10. It is save and checked. For this program purpose it should
     * be enough. For other values You should check behaviour.
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
     * Sets pointer to scene where vehicle has added to. It is very convenience if You want to compare some other vehicles to this.
     * Having pointer to the scence You have acces to all vehicles and traffic lights. It sometimes very helps.
     *
     * @param scene Scene which contains vehicle.
     */
    void setParentScene( GraphicsScene* scene );
    /*!
     * Returns scene which contains vehicle.
     */
    GraphicsScene* parentScene() const;
    /*!
     * This function is very tricky. The base for all vehicles is a 20x20 square. Various type of vehicles can have other geometry.
     * This method was created for counting the real size of vehicle.

     * For example base for bus is also this small square, but natural size of bus is bigger. And it changes becouse of
     * bus direction. For more descriprion see graphical vehicle description.
     */
    QSize size() const;
    /*!
     * Base for every vehicle is square 20x20. Normal position is a top right point of this square. But sometimes
     * there is need to have modified position becouse of other size of vehicle. For example bus is bigger than
     * this square, so his position is move to right top side. This new position is counted from simply formula.
     */
    QPoint topLeftPoint() const;
    QPoint bottomRightPoint() const;
    /*!
     * It is a possibility to switch off collision detection. This method is now used to switch off collision on BladzioJunction.
     * It is necassary there becouse bad architecture of this junction. Cars which turn left arrived from north and south
     * shouldn't be in collision normally. But in this junction they are. We found up we don't want to change cross, so we
     * switch off collision in this case. This allows to working this junction properly.
     */
    void setCheckCollisions( bool check = true );
    /*!
     * Returns true if collision detection is switched on, otherwise returns false.
     */
    bool checkCollisions() const;
    /*!
     * Returns direction of vehicle. See VehicleDirection description for more.
     */
    VehicleDirection direction() const;
    /*!
     * Base implementation do nothing.
     */
    virtual void setDarkDesign( bool dark = false );
    int vehicleId() const { return m_vehicleId; }
    void updateWaitingTime();
    int waitingTimeInSeconds();

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
    /// If it is true then vehicle is initialised by new checkpoint.
    bool m_first;
    /// Collision detection is switched on or switched off.
    bool m_checkCollisions;
    /// Vehicle id
    int m_vehicleId;
    /// Time on junction
    QTime m_startWaitingTime;

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
