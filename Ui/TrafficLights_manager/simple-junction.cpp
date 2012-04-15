#include "simple-junction.h"
#include "../Lights/trafficlight.h"
#include "../../Logger/logger.h"
#include "../../Logic/Genetic_algorithm/GA/genome-data.h"
#include "../../Logic/Genetic_algorithm/GA/GA1DArrayGenome.h"
#include "../../Logic/Genetic_algorithm/GA/genetic-algorithm-manager.h"
#include <QTimer>

SimpleJunction::SimpleJunction( const QVector<TrafficLight *> &junction, QLCDNumber* vehicleCounter ):
    Junction( junction, vehicleCounter, 4 ),
    m_leftLight( m_trafficLightVector.at( 0 ) ),
    m_rightLight( m_trafficLightVector.at( 1 ) ),
    m_leftAndStraightLight( m_trafficLightVector.at( 2 ) ),
    m_rightAndStraightLight( m_trafficLightVector.at( 3 ) )
{
    run();
}

SimpleJunction::~SimpleJunction()
{
//    delete leftLight;
}

void SimpleJunction::run()
{
    if( m_timeVector.count() != 0 ){

    uint rightTime = m_timeVector.at( 1 );
    uint rightAndStraightTime = m_timeVector.at( 3 );
    m_leftTime = m_timeVector.at( 0 );
    m_leftAndStraightTime = m_timeVector.at( 2 );

    if( rightTime >= m_leftTime )
    {
        rightTime -= m_leftTime;
    }
    if( m_leftTime != 0 ){
        firstSeries();
        }                                                                       /* Series 1 */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if( m_leftAndStraightTime >= rightTime )
    {
        rightTime = m_leftAndStraightTime;
    }
    else{
        m_leftAndStraightTime = rightTime;
    }
    if( m_leftAndStraightTime > 0 )
    {
        if( m_leftTime > 0 ){
            QTimer::singleShot( ( m_leftTime + m_interval ), this, SLOT( holdFirst() ) );
        }
        QTimer::singleShot( ( m_leftTime + ( m_interval*2 ) ), this, SLOT( secondSeries() ) );       /* Series 2 */
     }
    else{
        if( m_leftTime > 0 )
        {
            QTimer::singleShot( ( m_leftTime + m_interval ), this, SLOT( holdFirstTwoCondition() ) );
        }
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if( rightAndStraightTime > 0 )
    {
        if( m_leftAndStraightTime > 0 )
        {
            QTimer::singleShot( ( m_leftTime + ( m_interval*2 ) + m_leftAndStraightTime ), this, SLOT( holdSecond() ) );
        }
        int timeThirdSeries = m_leftTime + (m_interval*3) + m_leftAndStraightTime ;
        QTimer::singleShot( timeThirdSeries, this, SLOT( thirdSeries() ) );       /* Series 3 */

        timeThirdSeries += rightAndStraightTime;
        QTimer::singleShot( timeThirdSeries, this, SLOT( holdThird() ) );       /* Series 4 */
    }
    else{
        if( m_leftAndStraightTime > 0 )
        {
            int timeThirdSeries = m_leftTime + ( m_interval*2 ) + m_leftAndStraightTime;
            QTimer::singleShot( timeThirdSeries, this, SLOT( holdSecond() ) );
        }
    }
    }
}

void SimpleJunction::firstSeries()
{
    m_leftLight->letGoVehicles();
    m_rightLight->letGoVehicles();
}

void SimpleJunction::secondSeries()
{
    if( m_leftTime == 0 )
        m_rightLight->letGoVehicles();

    m_leftAndStraightLight->letGoVehicles();
}

void SimpleJunction::thirdSeries()
{
    if( m_leftAndStraightTime > 0 )
    {
        m_rightLight->holdVehicles();
        m_leftAndStraightLight->holdVehicles();
    }
    m_rightAndStraightLight->letGoVehicles();
}

void SimpleJunction::holdFirst()
{
    m_leftLight->holdVehicles();
}

void SimpleJunction::holdFirstTwoCondition()
{
    m_leftLight->holdVehicles();
    m_rightLight->holdVehicles();
}

void SimpleJunction::holdSecond()
{
    m_rightLight->holdVehicles();
    m_leftAndStraightLight->holdVehicles();
}

void SimpleJunction::holdThird()
{
    m_rightAndStraightLight->holdVehicles();
    run();
}

void SimpleJunction::setTimeVectorByGeneticAlgorithm()
{
    LOG_INFO( "Set new time vector in %s", __FUNCTION__ );

    /// av - averages on approriate cycle.
    std::vector< float > av;
    /// vn - vehicle number on approriate cycle.
    std::vector< int > vn;

    for( int i = 0 ; i < m_cyclesNumber ; i++ )
    {
        av.push_back( 2 );

        vn.push_back( 3 );
    }


    GeneticAlgorithmManager geneticAlgorithmManager;
    GAGenome genome = geneticAlgorithmManager.start( new GenomeData( m_cyclesNumber, av, vn ) );

    GA1DArrayGenome< int > &arrayGenome = ( GA1DArrayGenome< int > & )genome;

    QVector<int> time;
    for( int i = 0 ; i < m_cyclesNumber ; i++ )
    {
        time.append( arrayGenome.gene( i ) );
    }

    m_timeVector = time;
}
