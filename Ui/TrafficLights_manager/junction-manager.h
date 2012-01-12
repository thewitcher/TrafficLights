#ifndef JUNCTIONMANAGER_H
#define JUNCTIONMANAGER_H

#include <QMap>
#include <QVector>

class Junction;
class TrafficLight;

class JunctionManager
{
public:
    JunctionManager( QMap< int, QVector<TrafficLight*> > &junctionsMap );
    ~JunctionManager();

    /*!
     * Sets time of burning green light in junction with id. Position in vector time suits number of cycle. This vector should be appropriate size,
     * in other case this method return false and do nothing.
     */
    void setGreenLightTime( const unsigned int id, QVector<unsigned char> time );

private:
    /*!
     * Position in this vector is the same like junction id.
     * For example:
     * - junction with 3 id will be placed on 4 position (counted from zero)
     */
    QVector<Junction*> m_junctionsVector;
};

#endif // JUNCTIONMANAGER_H
