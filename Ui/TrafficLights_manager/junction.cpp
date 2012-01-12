#include "junction.h"
#include "../Lights/trafficlight.h"

Junction::Junction( const QVector<TrafficLight *>& junction ):
    m_trafficLightVector( junction )
{
    run();
}

void Junction::setTimeVector( QVector<int> &time )
{
    m_timeVector = time;
}

void Junction::run()
{
}
