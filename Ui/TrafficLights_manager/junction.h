#ifndef JUNCTION_H
#define JUNCTION_H

#include <QObject>
#include <QVector>

class TrafficLight;

/*!
 * This is abstract base class for all junctions in our program.
 */
class Junction: public QObject
{

    Q_OBJECT

public:
    Junction( const QVector<TrafficLight*>& junction );
    virtual ~Junction();

    void setTimeVector( QVector<int>& time );

    virtual void run() = 0;
protected:
    const QVector<TrafficLight*> m_trafficLightVector;
    QVector<int> m_timeVector;
    const int m_interval;

};

#endif // JUNCTION_H
