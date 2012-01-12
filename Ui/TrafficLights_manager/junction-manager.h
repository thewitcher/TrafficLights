#ifndef JUNCTIONMANAGER_H
#define JUNCTIONMANAGER_H

#include <QMap>
#include <QVector>

class Junction;
class TrafficLight;

class JunctionManager
{
public:
    JunctionManager( QMap< int, QVector<TrafficLight*> >& junctionsMap );
    ~JunctionManager();

    void sendTimeVector( const unsigned int id, QVector<int> time );

private:
    QVector<Junction*> m_junctionsVector;
};

#endif // JUNCTIONMANAGER_H
