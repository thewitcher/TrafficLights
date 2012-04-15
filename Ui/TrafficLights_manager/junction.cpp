#include "junction.h"
#include "../Lights/trafficlight.h"
#include "../Logger/logger.h"
#include "vector"
#include <QTimerEvent>
#include <QLCDNumber>

int Junction::S_TIME_TO_COUNT_AVERAGE = 20000;
int Junction::S_TIME_TO_CHECK_JUNCTION_STATUS = 30000;

Junction::Junction( const QVector<TrafficLight *> &junction, QLCDNumber *m_vehicleCounter, int cyclesNumber ):
    QObject( NULL ),
    m_trafficLightVector( junction ),
    m_interval( 500 ),
    m_currentNumberOfVehicles( 0 ),
    m_vehicleCounter( m_vehicleCounter ),
    m_cyclesNumber( cyclesNumber )
{
    m_averageTimerId = startTimer( S_TIME_TO_COUNT_AVERAGE );
    m_statusTimerId = startTimer( S_TIME_TO_CHECK_JUNCTION_STATUS );
}

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
    if( flags & 256 )
    {
        m_currentNumberOfVehicles++;
        m_directedVehicleCount[ checkpointId ]++;
    }
    else
    {
        m_currentNumberOfVehicles--;
    }

    m_vehicleCounter->display( m_currentNumberOfVehicles );
}

void Junction::timerEvent( QTimerEvent *event )
{
    if( event->timerId() == m_averageTimerId )
    {
        m_averageArrivedVehicles.clear();
        uchar id;
        uint vehicleCount;

        QHashIterator<uchar,uint> iterator( m_directedVehicleCount );

        while( iterator.hasNext() )
        {
            iterator.next();
            id = iterator.key();
            vehicleCount = iterator.value();

            LOG_INFO( "Checkpoint: %i, vehicle arrived from this checkpoint: %i", id, vehicleCount );

            m_averageArrivedVehicles[ id ] = vehicleCount;
        }

        m_directedVehicleCount.clear();
    }
    else if( event->timerId() == m_statusTimerId )
    {
        if( changeTimeVector() )
        {
            setTimeVectorByGeneticAlgorithm();
        }
    }
}

bool Junction::changeTimeVector()
{
    return true;
}
