#ifndef JUNCTIONMANAGER_H
#define JUNCTIONMANAGER_H

#include <QMap>
#include <QVector>
#include <QObject>

class Junction;
class TrafficLight;

class JunctionManager: public QObject
{

    Q_OBJECT

public:
    JunctionManager( QMap< int, QVector<TrafficLight*> >& junctionsMap );
    ~JunctionManager();

    void sendTimeVector( const uint id, QVector<int> time );

private:
    QVector<Junction*> m_junctionsVector;

    void createJunctions( QMap<int, QVector<TrafficLight *> >& junctionsMap );

public slots:
    void routeToAppropriateJunction( uint flags );
};

#endif // JUNCTIONMANAGER_H
