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

private:
    const QVector<TrafficLight*> m_trafficLightVector;
    QVector<int> m_timeVector;

    virtual void run() = 0;
};

#endif // JUNCTION_H
