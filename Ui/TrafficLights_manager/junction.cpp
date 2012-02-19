#include "junction.h"
#include "../Lights/trafficlight.h"
#include <QLCDNumber>

Junction::Junction( const QVector<TrafficLight *> &junction, QLCDNumber *m_vehicleCounter ):
    QObject( NULL ),
    m_trafficLightVector( junction ),
    m_interval( 500 ),
    m_currentNumberOfVehicles( 0 ),
    m_vehicleCounter( m_vehicleCounter )
{
}

Junction::~Junction()
{
}

void Junction::setTimeVector( QVector<int> &time )
{
    m_timeVector = time;
}
void Junction::run()
{
}

int Junction::currentNumberOfVehicles() const
{
    return m_currentNumberOfVehicles;
}

void Junction::manageVehicle( uint flags )
{
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
