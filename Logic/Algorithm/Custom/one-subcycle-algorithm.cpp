#include "one-subcycle-algorithm.h"
#include "../Ui/TrafficLights_manager/junction.h"
#include "../GA/GASStateGA.h"
#include "../GA/GA1DBinStrGenome.h"
#include "helper.h"
#include "../Logger/logger.h"
#include "../Ui/TrafficLights_manager/vehicle-count-manager.h"

/// GENETIC ALGORITHM FUNCTIONS ///
float objective( GAGenome& genome )
{
    //GA1DBinaryStringGenome &binaryGenome = Helper::genomeToBinaryGenome( genome );
    OneSubcycleAlgorithm* subcycleAlgorithm = Helper::userDataToOneSubcycleAlgorithm( genome );

    float result = 0;

    int greenTime = Helper::toDec( genome );
    int vehicleCountOnTheRestSubcycles = VehicleCountManager::vehicleCountOnRestSubcycle( subcycleAlgorithm->junction(),
                                                                                          subcycleAlgorithm->data().subcycle );
    float averageWaitingTime = VehicleCountManager::averageVehicleWaitingTimeOnSubcycle( subcycleAlgorithm->junction(),
                                                                                         subcycleAlgorithm->data().subcycle );

    /// t1 - how many seconds will be added to total waiting time
    int t1 = greenTime * vehicleCountOnTheRestSubcycles;
    /// t2 - how many seconds will be subtracted from total waiting time
    float t2 = greenTime * averageWaitingTime;

    ( t2 == 0 ) ? ( result = 0 ) : ( result = 10 * t2 - t1 * ( subcycleAlgorithm->ratio() + 0.001 * greenTime ) );

    return result;
}
///////////////////////////////////

OneSubcycleAlgorithm::OneSubcycleAlgorithm( Junction *junction ):
    BaseAlgorithm( junction ),
    m_wholeTime( 0 ),
    m_ratio( 0.0 )
{
}

int OneSubcycleAlgorithm::estimateGreenLight()
{
    GA1DBinaryStringGenome genome( m_genomeSize, objective, this );

    GASteadyStateGA steadyStateGA( genome );

    steadyStateGA.populationSize( m_populationSize );
    steadyStateGA.pReplacement( m_replacementProbability );
    steadyStateGA.nGenerations( m_generations );
    steadyStateGA.pMutation( m_mutation );
    steadyStateGA.pCrossover( m_crossover );
    steadyStateGA.scoreFilename( m_logFile );
    steadyStateGA.scoreFrequency( m_scoreFrequency );
    steadyStateGA.flushFrequency( m_flushFrequency );
    steadyStateGA.selectScores( GAStatistics::AllScores );
    steadyStateGA.evolve();

    LOG_INFO( "Best genome time: %i", Helper::toDec( steadyStateGA.population().best() ) * 1000 );

    return ( Helper::toDec( steadyStateGA.population().best() ) * 1000 );
}

QVector<int> OneSubcycleAlgorithm::startAlgorithm()
{
    clear();

    switch( m_junction->junctionType() )
    {
    case Junction::BLADZIO:
        startBladzio( m_junction );
    case Junction::SIMPLE:
        startSimple( m_junction );
    default:
        break;
    }

    QVector<int> vector;
    /// 4 - subcycles count
    for( int i = 0 ; i < 4 ; i++ )
    {
        if( i == m_data.subcycle )
        {
            vector << m_data.greenTime;
        }
        else
        {
            vector << 0;
        }
    }

    return vector;
}

VehicleCountManager::SubCycle OneSubcycleAlgorithm::chooseTheMostBlockSubcycleForBladzio( Junction *junction )
{
    m_times << VehicleCountManager::wholeVehicleWaitingTimeForSubcycle( junction, VehicleCountManager::SUBCYCLE_0 )
            << VehicleCountManager::wholeVehicleWaitingTimeForSubcycle( junction, VehicleCountManager::SUBCYCLE_1 )
            << VehicleCountManager::wholeVehicleWaitingTimeForSubcycle( junction, VehicleCountManager::SUBCYCLE_2 )
            << VehicleCountManager::wholeVehicleWaitingTimeForSubcycle( junction, VehicleCountManager::SUBCYCLE_3 );

    m_wholeTime = m_times.at( 0 ) + m_times.at( 1 ) + m_times.at( 2 ) + m_times.at( 3 );

    int max = m_times.at( 0 );
    VehicleCountManager::SubCycle result = VehicleCountManager::SUBCYCLE_0;

    if( m_times.at( 0 ) < m_times.at( 1 ) )
    {
        max = m_times.at( 1 );
        result = VehicleCountManager::SUBCYCLE_1;
    }
    if( max < m_times.at( 2 ) )
    {
        max = m_times.at( 2 );
        result = VehicleCountManager::SUBCYCLE_2;
    }
    if( max < m_times.at( 3 ) )
    {
        max = m_times.at( 3 );
        result = VehicleCountManager::SUBCYCLE_3;
    }

    ( m_wholeTime == 0 ) ? ( m_ratio = 0 ) : ( m_ratio = max / m_wholeTime );

    return result;
}

VehicleCountManager::SubCycle OneSubcycleAlgorithm::chooseTheMostBlockSubcycleForSimple( Junction *junction )
{
    m_times << VehicleCountManager::wholeVehicleWaitingTimeForSubcycle( junction, VehicleCountManager::SUBCYCLE_0 )
            << VehicleCountManager::wholeVehicleWaitingTimeForSubcycle( junction, VehicleCountManager::SUBCYCLE_1 )
            << VehicleCountManager::wholeVehicleWaitingTimeForSubcycle( junction, VehicleCountManager::SUBCYCLE_2 );

    m_wholeTime = m_times.at( 0 ) + m_times.at( 1 ) + m_times.at( 2 );

    int max = m_times.at( 0 );
    VehicleCountManager::SubCycle result = VehicleCountManager::SUBCYCLE_0;

    if( m_times.at( 0 ) < m_times.at( 1 ) )
    {
        max = m_times.at( 1 );
        result = VehicleCountManager::SUBCYCLE_1;
    }
    if( max < m_times.at( 2 ) )
    {
        max = m_times.at( 2 );
        result = VehicleCountManager::SUBCYCLE_2;
    }

    ( m_wholeTime == 0 ) ? ( m_ratio = 0 ) : ( m_ratio = max / m_wholeTime );

    return result;
}

void OneSubcycleAlgorithm::clear()
{
    m_times.clear();
    m_wholeTime = 0;
}

void OneSubcycleAlgorithm::startBladzio( Junction* junction )
{
    m_data.subcycle = chooseTheMostBlockSubcycleForBladzio( junction );
    m_data.greenTime = estimateGreenLight();
}

void OneSubcycleAlgorithm::startSimple( Junction *junction )
{
    m_data.subcycle = chooseTheMostBlockSubcycleForSimple( junction );
    m_data.greenTime = estimateGreenLight();
}

float OneSubcycleAlgorithm::ratio() const
{
    return m_ratio;
}

OneSubcycleAlgorithm::Data OneSubcycleAlgorithm::data() const
{
    return m_data;
}
