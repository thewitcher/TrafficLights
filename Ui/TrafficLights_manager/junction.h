#ifndef JUNCTION_H
#define JUNCTION_H

#include <QVector>

class TrafficLight;

/*!
 * This is abstract base class for all junctions in our program.
 */
class Junction
{
public:
    Junction( const QVector<TrafficLight*>& junction );

    void setTimeVector( QVector<int>& time );

protected:
    const QVector<TrafficLight*> m_trafficLightVector;
    QVector<int> m_timeVector;

    virtual void run();
};

#endif // JUNCTION_H
