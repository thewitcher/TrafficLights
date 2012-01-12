#ifndef JUNCTION_H
#define JUNCTION_H

#include <QVector>
#include <QObject>

class TrafficLight;

/*!
 * This is abstract base class for all junctions in our program.
 */
class Junction: public QObject
{

    Q_OBJECT

public:
    Junction( const QVector<TrafficLight*>& junction, const QVector<unsigned char>& cycles, QObject *parent = 0 );

    void setGreenLightTime( QVector<unsigned char>& time );
    void createCycles( const QVector<unsigned char>& cycles );

private:
    const QVector<TrafficLight*> m_junction;
    QVector<unsigned char> m_timesForGreenLight;
    unsigned char m_currentCycle;

private slots:
    void run();
    void setAllToRedLight();
    void setCycleToRedLight( unsigned char cycleNumber );
    void setCycleToGreenLight( unsigned char cycleNumber );
};

#endif // JUNCTION_H
