#include "junction-manager.h"
#include "junction.h"

JunctionManager::JunctionManager( QMap<int, QVector<TrafficLight *> >& junctionsMap )
{
}

JunctionManager::~JunctionManager()
{
    qDeleteAll( m_junctionsVector );
}

void JunctionManager::sendTimeVector( const unsigned int id, QVector<int> time )
{
}
