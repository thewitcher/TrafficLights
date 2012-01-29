#include "junction.h"
#include "../Lights/trafficlight.h"

Junction::Junction( const QVector<TrafficLight *>& junction ):
    QObject( NULL ),
    m_trafficLightVector( junction ),
    m_interval( 500 ),
    m_currentNumberOfVehicles( 0 )
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
    if( flags & 128 )
    {
        m_currentNumberOfVehicles++;
    }
    else
    {
        m_currentNumberOfVehicles--;
    }
}
