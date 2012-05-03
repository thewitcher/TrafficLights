#include "one-subcycle-algorithm.h"
#include "../Ui/TrafficLights_manager/junction.h"
#include "../GA/GAGenome.h"
#include "../GA/GASStateGA.h"

/// GENETIC ALGORITHM FUNCTIONS ///
float objective( GAGenome& genome )
{
    Q_UNUSED( genome );

    return 0.0;
}
///////////////////////////////////

OneSubcycleAlgorithm::OneSubcycleAlgorithm( Junction *junction ):
    BaseAlgorithm( junction )
{
}

int OneSubcycleAlgorithm::estimateGreenLight()
{
    return 6000;
}

QVector<int> OneSubcycleAlgorithm::startAlgorithm()
{
    clear();

    Data data;
    data.greenLine = 6000;
    data.subcycle = VehicleCountManager::SUBCYCLE_0;

    switch( m_junction->junctionType() )
    {
    case Junction::BLADZIO:
        data = startBladzio( m_junction );
    case Junction::SIMPLE:
        data = startSimple( m_junction );
    default:
        break;
    }

    QVector<int> vector;
    /// 4 - subcycles count
    for( int i = 0 ; i < 4 ; i++ )
    {
        if( i == data.subcycle )
        {
            vector << data.greenLine;
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

    return result;
}

void OneSubcycleAlgorithm::clear()
{
    m_times.clear();
    m_wholeTime = 0;
}

OneSubcycleAlgorithm::Data OneSubcycleAlgorithm::startBladzio( Junction* junction )
{
    Data data;
    data.greenLine = estimateGreenLight();
    data.subcycle = chooseTheMostBlockSubcycleForBladzio( junction );

    return data;
}

OneSubcycleAlgorithm::Data OneSubcycleAlgorithm::startSimple( Junction *junction )
{
    Data data;
    data.greenLine = estimateGreenLight();
    data.subcycle = chooseTheMostBlockSubcycleForSimple( junction );

    return data;
}
