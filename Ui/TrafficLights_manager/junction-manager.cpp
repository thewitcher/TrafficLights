#include "junction-manager.h"
#include "simple-junction.h"
#include "bladzio-junction.h"
#include "../Logger/logger.h"

JunctionManager::JunctionManager( QMap<int, QVector<TrafficLight *> > &junctionsMap,
                                  QVector<QLCDNumber *> &vehicleCounters ): QObject( NULL )
{
    createJunctions( junctionsMap, vehicleCounters );
    runForSubcycles();
}

JunctionManager::~JunctionManager()
{
    qDeleteAll( m_junctionsVector );
}

void JunctionManager::runForSubcycles()
{
    for( int i = 0 ; i < m_junctionsVector.count() ; i++ )
    {
        m_junctionsVector.at( i )->runForSubcycles();
    }
}

/*! Creates 7 objects with responsibility for manage signallers on each junction.
    6 of them is SimpleJunction type and one BladzioJunction type.
    BladzioJunction is the largest cross in the map. */

void JunctionManager::createJunctions( QMap<int, QVector<TrafficLight *> > &junctionsMap, QVector<QLCDNumber *> &vehicleCounters )
{
    LOG_INFO( "Creating 7 junctions in %s", __FUNCTION__ );

    Junction *junction = NULL;

    // SimpleJunction
    junction = new SimpleJunction( junctionsMap.value( 0 ), vehicleCounters.at( 0 ), 0 );
    m_junctionsVector.append( junction );

    // SimpleJunction
    junction = new SimpleJunction( junctionsMap.value( 1 ), vehicleCounters.at( 1 ), 1 );
    m_junctionsVector.append( junction );

    // BladzioJunction
    junction = new BladzioJunction( junctionsMap.value( 2 ), vehicleCounters.at( 2 ), 2 );
    m_junctionsVector.append( junction );

    // SimpleJunction
    junction = new SimpleJunction( junctionsMap.value( 3 ), vehicleCounters.at( 3 ), 3 );
    m_junctionsVector.append( junction );

    // SimpleJunction
    junction = new SimpleJunction( junctionsMap.value( 4 ), vehicleCounters.at( 4 ), 4 );
    m_junctionsVector.append( junction );

    // SimpleJunction
    junction = new SimpleJunction( junctionsMap.value( 5 ), vehicleCounters.at( 5 ), 5 );
    m_junctionsVector.append( junction );

    // SimpleJunction
    junction = new SimpleJunction( junctionsMap.value( 6 ), vehicleCounters.at( 6 ), 6 );
    m_junctionsVector.append( junction );
}

void JunctionManager::routeToAppropriateJunction( uint flags, int checkpointId, Vehicle* vehicle )
{
    uint pow2 = 2;
    int junction = 0;

    while( ( flags & pow2 ) == false )
    {
        Q_ASSERT( junction < 7 );

        junction++;
        pow2 *= 2;
    }

    m_junctionsVector.at( junction )->manageVehicle( flags, checkpointId, vehicle );
}

const QVector<Junction*>& JunctionManager::junctionsVector() const
{
    return m_junctionsVector;
}
