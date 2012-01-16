#include "junction.h"
#include "../Lights/trafficlight.h"

Junction::Junction( const QVector<TrafficLight *>& junction ):
    QObject( NULL ),
    m_trafficLightVector( junction ),
    m_interval( 500 )
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

