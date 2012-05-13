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
    JunctionManager( QMap< int, QVector<TrafficLight*> >& junctionsMap,
                     QVector<QLCDNumber*>& vehicleCounters );
    ~JunctionManager();

    const QVector<Junction*>& junctionsVector() const;

private:
    QVector<Junction*> m_junctionsVector;
    void createJunctions( QMap<int, QVector<TrafficLight *> >& junctionsMap, QVector<QLCDNumber*>& vehicleCounters );
    void runForSubcycles();

public slots:
    void routeToAppropriateJunction( uint flags, int checkpointId, Vehicle* vehicle );
};

#endif // JUNCTIONMANAGER_H
