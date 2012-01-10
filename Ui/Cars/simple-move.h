#ifndef SIMPLEMOVE_H
#define SIMPLEMOVE_H

#include <QObject>

class Vehicle;
class DelayCaller;

class SimpleMove
{
public:
    explicit SimpleMove( Vehicle *target );
    ~SimpleMove();

protected:
    Vehicle *m_currentVehicle;
    static int WAIT_FOR_MOVE_TIME;
    DelayCaller* m_delayCaller;

    void collisionDetection();

    friend class DelayCaller;
};

/*!
 * Timer class was implemented to invoke function from B class after some period of time.
 */
class DelayCaller: public QObject
{

    Q_OBJECT

public:
    explicit DelayCaller( SimpleMove* mainObject, QObject *parent = 0 );

private:
    // Funtion will be called on this object.
    SimpleMove* m_mainObject;

    void callAfterDelay( int delay );

public slots:
    void invoke();

    friend class SimpleMove;
};

#endif // SIMPLEMOVE_H
