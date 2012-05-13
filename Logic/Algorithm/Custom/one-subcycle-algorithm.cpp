#include "one-subcycle-algorithm.h"
#include "../Ui/TrafficLights_manager/junction.h"
#include "../GA/GASStateGA.h"
#include "../GA/GA1DBinStrGenome.h"
#include "helper.h"
#include "../Logger/logger.h"
#include "../Ui/TrafficLights_manager/vehicle-count-manager.h"
#include <math.h>

float OneSubcycleAlgorithm::S_MAX = 1.2;
float OneSubcycleAlgorithm::S_MIN = 0.8;
float OneSubcycleAlgorithm::S_PASS_RATE = 1;

/// GENETIC ALGORITHM FUNCTIONS ///
float objective( GAGenome& genome )
{
    OneSubcycleAlgorithm* subcycleAlgorithm = Helper::userDataToOneSubcycleAlgorithm( genome );

    int beginRange = OneSubcycleAlgorithm::S_MIN * subcycleAlgorithm->m_vehicleCount;
    int endRange = OneSubcycleAlgorithm::S_MAX * subcycleAlgorithm->m_vehicleCount;
    int estimateVehicleCountInFuture = GARandomInt( beginRange, endRange );

    float greenLight = Helper::toDec( genome );

    float difference = abs( greenLight * OneSubcycleAlgorithm::S_PASS_RATE
                            - subcycleAlgorithm->m_vehicleCountOnSubcycle.at( int( subcycleAlgorithm->m_currentSubcycle ) ) );
    float newVehiclesOnRestSubcycles = 0;
    float newVehiclesOnChoosenSubcycles = 0;

    if( subcycleAlgorithm->m_vehicleCount == 0 )
    {
        subcycleAlgorithm->m_vehicleCount = 1;
    }

    for( int i = 0 ; i < subcycleAlgorithm->m_vehicleCountOnSubcycle.count() ; i++ )
    {
        if( i == int( subcycleAlgorithm->m_currentSubcycle ) )
        {
            newVehiclesOnChoosenSubcycles = subcycleAlgorithm->m_vehicleCountOnSubcycle.at( i ) * estimateVehicleCountInFuture
                                          / subcycleAlgorithm->m_vehicleCount;
        }
        else
        {
            newVehiclesOnRestSubcycles += subcycleAlgorithm->m_vehicleCountOnSubcycle.at( i ) * estimateVehicleCountInFuture
                                        / subcycleAlgorithm->m_vehicleCount;
        }
    }

    float denominator = newVehiclesOnChoosenSubcycles * difference
                      + ( greenLight - newVehiclesOnChoosenSubcycles ) * newVehiclesOnRestSubcycles;

    if( denominator == 0 )
    {
        return 0.0;
    }

    float fitness = abs( greenLight / denominator ) + 0.5;

    return fitness;
}
///////////////////////////////////

OneSubcycleAlgorithm::OneSubcycleAlgorithm( Junction *junction ):
    BaseAlgorithm( junction, "ONE_SUBCYCLE_ALGORITHM" ),
    m_currentSubcycle( VehicleCountManager::SUBCYCLE_0 ),
    m_firstRun( true ),
    m_vehicleCount( 0 )
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
    steadyStateGA.scoreFilename( m_logFile.toAscii().constData() );
    steadyStateGA.scoreFrequency( m_scoreFrequency );
    steadyStateGA.flushFrequency( m_flushFrequency );
    steadyStateGA.selectScores( GAStatistics::AllScores );
    steadyStateGA.evolve();

    LOG_INFO( "#%i# Best chromsome on junction with id: %i (best: %i)",
              m_junction->id(),
              m_junction->id(),
              Helper::toDec( steadyStateGA.population().best() ) * 1000 );

    return ( Helper::toDec( steadyStateGA.population().best() ) * 1000 );
}

QVector<int> OneSubcycleAlgorithm::startAlgorithm()
{
    if( m_firstRun == true )
    {
        m_firstRun = false;
        return QVector<int>() << 3000 << 3000 << 3000 << 3000;
    }

    int greenTime = 0;

    switch( m_junction->junctionType() )
    {
    case Junction::SIMPLE:
        chooseTheMostBlockSubcycleForSimple();
        loadDataForSimple();
        if( m_vehicleCount == 0 )
        {
            return QVector<int>() << 1000 << 1000 << 1000 << 1000;
        }
        greenTime = estimateGreenLight();
        break;
    case Junction::BLADZIO:
        chooseTheMostBlockSubcycleForBladzio();
        loadDataForBladzio();
        if( m_vehicleCount == 0 )
        {
            return QVector<int>() << 1000 << 1000 << 1000 << 1000;
        }
        greenTime = estimateGreenLight();
        break;
    default:
        break;
    }

    QVector<int> vector;
    /// 4 - subcycles count
    for( int i = 0 ; i < 4 ; i++ )
    {
        if( i == int( m_currentSubcycle ) )
        {
            vector << greenTime;
        }
        else
        {
            vector << 0;
        }
    }

    return vector;
}

void OneSubcycleAlgorithm::chooseTheMostBlockSubcycleForBladzio()
{
    QVector<int> times;

    times << VehicleCountManager::wholeVehicleWaitingTimeForSubcycle( m_junction, VehicleCountManager::SUBCYCLE_0 )
          << VehicleCountManager::wholeVehicleWaitingTimeForSubcycle( m_junction, VehicleCountManager::SUBCYCLE_1 )
          << VehicleCountManager::wholeVehicleWaitingTimeForSubcycle( m_junction, VehicleCountManager::SUBCYCLE_2 )
          << VehicleCountManager::wholeVehicleWaitingTimeForSubcycle( m_junction, VehicleCountManager::SUBCYCLE_3 );

    int max = times.at( 0 );
    VehicleCountManager::SubCycle result = VehicleCountManager::SUBCYCLE_0;

    if( times.at( 0 ) < times.at( 1 ) )
    {
        max = times.at( 1 );
        result = VehicleCountManager::SUBCYCLE_1;
    }
    if( max < times.at( 2 ) )
    {
        max = times.at( 2 );
        result = VehicleCountManager::SUBCYCLE_2;
    }
    if( max < times.at( 3 ) )
    {
        max = times.at( 3 );
        result = VehicleCountManager::SUBCYCLE_3;
    }

    m_currentSubcycle = result;
}

void OneSubcycleAlgorithm::chooseTheMostBlockSubcycleForSimple()
{
    QVector<int> times;

    times << VehicleCountManager::wholeVehicleWaitingTimeForSubcycle( m_junction, VehicleCountManager::SUBCYCLE_0 )
            << VehicleCountManager::wholeVehicleWaitingTimeForSubcycle( m_junction, VehicleCountManager::SUBCYCLE_1 )
            << VehicleCountManager::wholeVehicleWaitingTimeForSubcycle( m_junction, VehicleCountManager::SUBCYCLE_2 );

    int max = times.at( 0 );
    VehicleCountManager::SubCycle result = VehicleCountManager::SUBCYCLE_0;

    if( times.at( 0 ) < times.at( 1 ) )
    {
        max = times.at( 1 );
        result = VehicleCountManager::SUBCYCLE_1;
    }
    if( max < times.at( 2 ) )
    {
        max = times.at( 2 );
        result = VehicleCountManager::SUBCYCLE_2;
    }

    LOG_INFO( "#%i# Current subcycle on junction with id: %i (subcycle: %i)",
              m_junction->id(),
              m_junction->id(),
              m_currentSubcycle );

    m_currentSubcycle = result;
}

void OneSubcycleAlgorithm::loadDataForBladzio()
{
    m_vehicleCountOnSubcycle.clear();

    m_vehicleCountOnSubcycle << VehicleCountManager::vehicleCountOnSubcycle( m_junction, VehicleCountManager::SUBCYCLE_0 )
                             << VehicleCountManager::vehicleCountOnSubcycle( m_junction, VehicleCountManager::SUBCYCLE_1 )
                             << VehicleCountManager::vehicleCountOnSubcycle( m_junction, VehicleCountManager::SUBCYCLE_2 )
                             << VehicleCountManager::vehicleCountOnSubcycle( m_junction, VehicleCountManager::SUBCYCLE_3 );

    m_vehicleCount = m_vehicleCountOnSubcycle.at( 0 )
                   + m_vehicleCountOnSubcycle.at( 1 )
                   + m_vehicleCountOnSubcycle.at( 2 )
                   + m_vehicleCountOnSubcycle.at( 3 );
}

void OneSubcycleAlgorithm::loadDataForSimple()
{
    m_vehicleCountOnSubcycle.clear();

    m_vehicleCountOnSubcycle << VehicleCountManager::vehicleCountOnSubcycle( m_junction, VehicleCountManager::SUBCYCLE_0 )
                             << VehicleCountManager::vehicleCountOnSubcycle( m_junction, VehicleCountManager::SUBCYCLE_1 )
                             << VehicleCountManager::vehicleCountOnSubcycle( m_junction, VehicleCountManager::SUBCYCLE_2 );

    m_vehicleCount = m_vehicleCountOnSubcycle.at( 0 )
                   + m_vehicleCountOnSubcycle.at( 1 )
                   + m_vehicleCountOnSubcycle.at( 2 );
}
