#ifndef JUNCTIONMANAGER_H
#define JUNCTIONMANAGER_H

#include <QMap>
#include <QVector>
#include <QObject>

class Junction;
class TrafficLight;
class QLCDNumber;
class Vehicle;

class JunctionManager: public QObject
{

    Q_OBJECT

public:
    JunctionManager( QMap< int, QVector<TrafficLight*> >& junctionsMap, QVector<QLCDNumber*>& vehicleCounters );
    ~JunctionManager();

    void sendTimeVector( const uint id, QVector<int> time );

private:
    QVector<Junction*> m_junctionsVector;

    void createJunctions( QMap<int, QVector<TrafficLight *> >& junctionsMap, QVector<QLCDNumber*>& vehicleCounters );

public slots:
    void routeToAppropriateJunction( uint flags, uchar checkpointId, Vehicle* vehicle );
};

#endif // JUNCTIONMANAGER_H
