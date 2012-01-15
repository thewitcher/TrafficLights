#ifndef SIMPLEMOVE_H
#define SIMPLEMOVE_H

#include <QObject>

class Vehicle;
class DelayCaller;

/*!
 * @file simple-move.h
 *
 * @brief This class implement collision detection feature.
 *
 * @author Marcin Haber
 *
 * Base class for all animation in this program. We use it to collisione detection. It contains DelayCaller to have possibility delay invoke method.
 */
class SimpleMove
{
public:
    /*!
     * Saves pointer to target.
     *
     * @param target Animated object.
     */
    explicit SimpleMove( Vehicle *target );
    virtual ~SimpleMove();

protected:
    /// Vehicle which is animated by this animation.
    Vehicle *m_currentVehicle;
    /// Period of time to wait before resume moving after detecting collision.
    static int WAIT_FOR_MOVE_TIME;
    /// This object allows to call function after some period of time. We can't use QTimer::singleshot() here, becouse we can;t inherit from QObject.
    DelayCaller* m_delayCaller;

    /*!
     * Detects collision. Pause and resume vehicle move when necessary.
     */
    void collisionDetection();

    friend class DelayCaller;
};

/*!
 * @file simple-move.h
 *
 * @brief This class implement calling method with some delay.
 *
 * @author Marcin Haber
 *
 * DelayCaller class was implemented to invoke function from SimpleMove class after some period of time.
 */
class DelayCaller: public QObject
{

    Q_OBJECT

public:
    /*!
     * Standard constructor.
     *
     * @param mainObject Object which contains function to call.
     */
    explicit DelayCaller( SimpleMove* mainObject, QObject *parent = 0 );

private:
    /// Funtion will be called on this object.
    SimpleMove* m_mainObject;

    /*!
     * It calls approriate method from m_mainObject after delay time.
     *
     * @param delay Time to invoke method.
     */
    void callAfterDelay( int delay );

public slots:
    /*!
     * Invokes method. This function is called after delay time.
     */
    void invoke();

    friend class SimpleMove;
};

#endif // SIMPLEMOVE_H
