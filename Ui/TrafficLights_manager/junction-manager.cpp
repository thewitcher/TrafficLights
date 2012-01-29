#include "junction-manager.h"
#include "simple-junction.h"
#include "bladzio-junction.h"
#include "../Logger/logger.h"

JunctionManager::JunctionManager( QMap<int, QVector<TrafficLight *> >& junctionsMap ):
    QObject( NULL )
{
    createJunctions( junctionsMap );
    QVector<int> vector;
    vector << 5000 << 5000 << 5000 << 5000;
    sendTimeVector( 0, vector );
    m_junctionsVector.at(0)->run();
    sendTimeVector( 1, vector );
    m_junctionsVector.at(1)->run();
    sendTimeVector( 3, vector );
    m_junctionsVector.at(3)->run();
    sendTimeVector( 4, vector );
    m_junctionsVector.at(4)->run();
    sendTimeVector( 5, vector );
    m_junctionsVector.at(5)->run();
    sendTimeVector( 6, vector );
    m_junctionsVector.at(6)->run();

    vector << 6000 << 5000;
    sendTimeVector( 2, vector );
    m_junctionsVector.at(2)->run();
}

JunctionManager::~JunctionManager()
{
    qDeleteAll( m_junctionsVector );
}

void JunctionManager::sendTimeVector( const uint id, QVector<int> time )
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

    Junction *junction = NULL;

    // SimpleJunction
    junction = new SimpleJunction( junctionsMap.value( 0 ) );
    m_junctionsVector.append( junction );

    // SimpleJunction
    junction = new SimpleJunction( junctionsMap.value( 1 ) );
    m_junctionsVector.append( junction );

    // BladzioJunction
    junction = new BladzioJunction( junctionsMap.value( 2 ) );
    m_junctionsVector.append( junction );

    // SimpleJunction
    junction = new SimpleJunction( junctionsMap.value( 3 ) );
    m_junctionsVector.append( junction );

    // SimpleJunction
    junction = new SimpleJunction( junctionsMap.value( 4 ) );
    m_junctionsVector.append( junction );

    // SimpleJunction
    junction = new SimpleJunction( junctionsMap.value( 5 ) );
    m_junctionsVector.append( junction );

    // SimpleJunction
    junction = new SimpleJunction( junctionsMap.value( 6 ) );
    m_junctionsVector.append( junction );
}

void JunctionManager::routeToAppropriateJunction( uint flags )
{
    uint pow2 = 2;
    uchar junction = 0;

    while( ( flags & pow2 ) == false )
    {
        junction++;
        pow2 *= 2;

        Q_ASSERT( junction > 6 );
    }

    m_junctionsVector.at( junction )->manageVehicle( flags );
}