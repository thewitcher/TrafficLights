#include "junction.h"
#include "../Lights/trafficlight.h"
#include "../Logger/logger.h"
#include "../../Logic/Genetic_algorithm/GA/genome-data.h"
#include "../../Logic/Genetic_algorithm/GA/GA1DArrayGenome.h"
#include "../../Logic/Genetic_algorithm/GA/genetic-algorithm-manager.h"
#include "vector"
#include <QTimerEvent>
#include <QLCDNumber>

int Junction::S_TIME_TO_COUNT_AVERAGE = 20000;

Junction::Junction( const QVector<TrafficLight *> &junction, QLCDNumber *m_vehicleCounter ):
    QObject( NULL ),
    m_trafficLightVector( junction ),
    m_interval( 500 ),
    m_currentNumberOfVehicles( 0 ),
    m_vehicleCounter( m_vehicleCounter )
{
    m_timerId = startTimer( S_TIME_TO_COUNT_AVERAGE );
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
    std::vector< float > av;
    av.push_back( 2 );
    av.push_back( 3 );
    std::vector< int > vn;
    vn.push_back( 3 );
    vn.push_back( 9 );

    GeneticAlgorithmManager geneticAlgorithmManager;
    geneticAlgorithmManager.start( new GenomeData( 2, av, vn ) );
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
    if( event->timerId() == m_timerId )
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
}
