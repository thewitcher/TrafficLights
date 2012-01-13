#include "junction-manager.h"
#include "simple-junction.h"
#include "bladzio-junction.h"
#include "../Logger/logger.h"

JunctionManager::JunctionManager( QMap<int, QVector<TrafficLight *> >& junctionsMap )
{
    createJunctions( junctionsMap );
    QVector<int> vector;
    vector << 5000 << 5000 << 5000 << 5000;
    sendTimeVector( 0, vector );
    m_junctionsVector.at(0)->run();

    vector << 6000 << 6000;
    sendTimeVector( 2, vector );
    m_junctionsVector.at(2)->run();
}

JunctionManager::~JunctionManager()
{
    qDeleteAll( m_junctionsVector );
}

void JunctionManager::sendTimeVector( const unsigned int id, QVector<int> time )
{
    if( id < ( unsigned char )m_junctionsVector.count() )
    {
        m_junctionsVector.at( id )->setTimeVector( time );
    }
    else
    {
        LOG_WARNING( "Id is not recognized. There is no junction with that id (id: %i)", id );
    }
}

/*!
 * Creates 7 objects with responsibility for manage signallers on each junction. 6 of them is SimpleJunction type and one BladzioJunction type.
 * BladzioJunction is the largest cross in the map.
 */
void JunctionManager::createJunctions( QMap<int, QVector<TrafficLight *> > &junctionsMap )
{
    LOG_INFO( "Creating 7 junctions in %s", __FUNCTION__ );

    for( int i = 0 ; i < junctionsMap.count() ; i++ )
    {
        if( i == 2 ) // Case for BladzioJunction
        {
            m_junctionsVector.append( new BladzioJunction( junctionsMap.value( i ) ) );
        }
        else // SimpleJunction
        {
            m_junctionsVector.append( new SimpleJunction( junctionsMap.value( i ) ) );
        }
    }
}
