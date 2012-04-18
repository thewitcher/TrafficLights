#ifndef JUNCTION_H
#define JUNCTION_H

#include <QObject>
#include <QVector>
#include <QHash>

class QLCDNumber;
class TrafficLight;

/*!
 * This is abstract base class for all junctions in our program.
 */
class Junction: public QObject
{

    Q_OBJECT

public:
    Junction( const QVector<TrafficLight*>& junction, QLCDNumber* m_vehicleCounter );
    virtual ~Junction();

    /// Sets time vector - you can use it to set fixed times at lights.
    void setTimeVector( QVector<int>& time );
    /// It is calles when vehicles arrived or leave junction.
    void manageVehicle( uint flags, uchar checkpointId );
    /// Current number of vehicles on whole junction.
    int currentNumberOfVehicles() const;

    virtual void run() = 0;

protected:
    /// Contains all traffic lights uses by this junction.
    const QVector<TrafficLight*> m_trafficLightVector;
    /// Time for all cycles in this junction.
    QVector<int> m_timeVector;
    const int m_interval;
    /// Just number of vehicles before red lights (it counts all vehicles on junction)
    int m_currentNumberOfVehicles;
    /// Counter to show how many vehicles are currently on junction
    QLCDNumber* m_vehicleCounter;
    /// If it returns true then time vector should be changed, otherwise it is ok and should not be changed.
    bool changeTimeVector();
    /// It uses genetic algorithm to create appropriate time vector for that junction.
    virtual void setTimeVectorByGeneticAlgorithm() = 0;
};

#endif // JUNCTION_H
