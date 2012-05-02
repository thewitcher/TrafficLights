#ifndef JUNCTION_H
#define JUNCTION_H

#include <QObject>
#include <QVector>
#include <QHash>

class QLCDNumber;
class TrafficLight;
class Vehicle;
class AlgorithmManager;

/*!
 * This is abstract base class for all junctions in our program.
 */
class Junction: public QObject
{

    Q_OBJECT

public:
    enum JUNCTION_TYPE { BLADZIO, SIMPLE, NO_TYPE };

    Junction( const QVector<TrafficLight*>& junction, QLCDNumber* m_vehicleCounter, int junctionId, JUNCTION_TYPE junctionType );
    virtual ~Junction();

    /// It is called when vehicles arrived or leave junction.
    void manageVehicle( uint flags, int checkpointId, Vehicle* vehicle );
    /// Current number of vehicles on whole junction.
    int currentNumberOfVehicles() const;
    JUNCTION_TYPE junctionType() const;
    bool isVehicleFirst( Vehicle* vehicle );
    int id() const;
    const QHash<int,int> vehicleCountOnLanes() const;
    const QMultiHash<int,Vehicle*> waitingTime() const;

    virtual void runForSubcycles() = 0;

protected:
    Vehicle* firstArrived( int checkpointId );

    /// Contains all traffic lights uses by this junction.
    const QVector<TrafficLight*> m_trafficLightVector;

    /// Time for all cycles in this junction.
    QVector<int> m_timeVectorForSubcycles;

    /// Break between subcycles.
    const int m_pauseBetweenSubcycles;

    /// Specifying the length of times lights activation.
    const int m_interval;

    /// Just number of vehicles before red lights (it counts all vehicles on junction)
    int m_currentNumberOfVehicles;

    /// Counter to show how many vehicles are currently on junction
    QLCDNumber* m_vehicleCounter;
    QHash<int,int> m_vehicleCountOnLanes;
    QMultiHash<int,Vehicle*> m_waitingTime;
    int m_junctionId;
    AlgorithmManager *m_algorithmManager;
    JUNCTION_TYPE m_junctionType;

    void timerEvent( QTimerEvent *event );
    /// If it returns true then time vector should be changed, otherwise it is ok and should not be changed.
    bool changeTimeVector();
    /// It uses genetic algorithm to create appropriate time vector for that junction.
    virtual void setTimeVectorByAlgorithm();

protected slots:
    void addVehicleToStatistic( int checkpointId, Vehicle* vehicle );
    void subtractVehicleFromStatistic( int checkpointId, Vehicle* vehicle );
};

#endif // JUNCTION_H
