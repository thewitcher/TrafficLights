#include "junction-manager.h"
#include "junction.h"
#include <QDebug>

JunctionManager::JunctionManager( QMap<int, QVector<TrafficLight *> >& junctionsMap )
{
    for( int i = 0 ; i < junctionsMap.count() ; i++ )
    {
        if( i == 2 ) // Large junction
        {
            m_junctionsVector.append( new Junction( junctionsMap.value( i ), QVector<unsigned char>() << 0 << 0 << 0 << 0 << 1
                                                    << 1 << 1 << 1 << 1 << 1 << 1 << 1 ) );
        }
        else
        {
            m_junctionsVector.append( new Junction( junctionsMap.value( i ), QVector<unsigned char>() << 1 << 1 << 1 << 1 ) );
        }
    }
}

JunctionManager::~JunctionManager()
{
    qDeleteAll( m_junctionsVector );
}

void JunctionManager::setGreenLightTime( const unsigned int id, QVector<unsigned char> time )
{
    // Checks that junction with id id exists.
    if( id < (unsigned char)m_junctionsVector.count() )
    {
        m_junctionsVector.at( id )->setGreenLightTime( time );
    }
}
