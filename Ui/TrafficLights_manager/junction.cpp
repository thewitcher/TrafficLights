#include "junction.h"
#include "../Lights/trafficlight.h"
#include "../Logger/logger.h"
#include "vector"
#include <QTimerEvent>
#include <QLCDNumber>


Junction::Junction( const QVector<TrafficLight *> &junction, QLCDNumber *m_vehicleCounter ):
    QObject( NULL ),
    m_trafficLightVector( junction ),
    m_interval( 500 ),
    m_currentNumberOfVehicles( 0 ),
    m_vehicleCounter( m_vehicleCounter )
{}

Junction::~Junction()
{
}

void Junction::setTimeVector( QVector<int> &time )
{
    m_timeVector = time;
}

void Junction::setTimeVectorByGeneticAlgorithm()
{
}

void Junction::run()
{
}

int Junction::currentNumberOfVehicles() const
{
    return m_currentNumberOfVehicles;
}

void Junction::manageVehicle( uint flags, uchar checkpointId )
{
    Q_UNUSED( checkpointId );

    if( flags & 256 )
    {
        m_currentNumberOfVehicles++;
    }
    else
    {
        m_currentNumberOfVehicles--;
    }

    m_vehicleCounter->display( m_currentNumberOfVehicles );
}
