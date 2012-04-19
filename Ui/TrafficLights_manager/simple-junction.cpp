#include "simple-junction.h"
#include "../Lights/trafficlight.h"
#include "../../Logger/logger.h"
#include "../../Logic/Genetic_algorithm/GA/genome-data.h"
#include "../../Logic/Genetic_algorithm/GA/GA1DArrayGenome.h"
#include "../../Logic/Genetic_algorithm/GA/genetic-algorithm-manager.h"
#include <QTimer>

SimpleJunction::SimpleJunction( const QVector<TrafficLight *> &junction, QLCDNumber* vehicleCounter ):
    Junction( junction, vehicleCounter ),
    m_leftLight( m_trafficLightVector.at( 0 ) ),
    m_rightLight( m_trafficLightVector.at( 1 ) ),
    m_leftAndStraightLight( m_trafficLightVector.at( 2 ) ),
    m_rightAndStraightLight( m_trafficLightVector.at( 3 ) )
{}

SimpleJunction::~SimpleJunction()
{}

void SimpleJunction::runForSubcycles()
{
    uint subcycle_1 = m_timeVectorForSubcycles.at( 0 );
    uint subcycle_2 = m_timeVectorForSubcycles.at( 1 );
    uint subcycle_3 = m_timeVectorForSubcycles.at( 2 );

    /* Subcycle 1 */
    runSubcycle_1( subcycle_1 );

    /* Subcycle 2 */
    runSubcycle_2( subcycle_1, subcycle_2 );

    /* Subcycle 3 */
    runSubcycle_3( subcycle_1, subcycle_2, subcycle_3 );

    /* runForSubcycles function call when all subcycles sum equal 0 */
    exceptionWhenSubcycleSumEqualZero( subcycle_1, subcycle_2, subcycle_3 );
}

void SimpleJunction::runSubcycle_1( uint subcycle_1 )
{
    if( subcycle_1 != 0 )
    {
        firstSubcycle();
        QTimer::singleShot( subcycle_1 + m_interval , this, SLOT(holdFirstSubcycle()) );
    }
}

void SimpleJunction::runSubcycle_2( uint subcycle_1, uint subcycle_2 )
{
    if( subcycle_2 != 0 )
    {
        if( subcycle_1 != 0 ){
            QTimer::singleShot( subcycle_1 + ( m_interval * 2 ) + m_pauseBetweenSubcycles,
                               this, SLOT(secondSubcycle()) );
            QTimer::singleShot( subcycle_1 + ( m_interval * 3 )+ subcycle_2 + m_pauseBetweenSubcycles,
                               this, SLOT(holdSecondSubcycle()) );
        }
        else{
            QTimer::singleShot( 0, this, SLOT(secondSubcycle()) );
            QTimer::singleShot( subcycle_2 + m_interval, this, SLOT(holdSecondSubcycle()) );
        }
    }
}

void SimpleJunction::runSubcycle_3( uint subcycle_1, uint subcycle_2, uint subcycle_3 )
{
    if( subcycle_3 != 0 )
    {
        if( subcycle_2 != 0 && subcycle_1 == 0 ){
            QTimer::singleShot( subcycle_1 + ( m_interval * 4 ) + subcycle_2, this, SLOT(thirdSubcycle()) );
            QTimer::singleShot( subcycle_1 + ( m_interval * 4 ) + subcycle_2 + subcycle_3, this, SLOT(holdThirdSubcycle()) );
        }
        else if( subcycle_2 != 0 && subcycle_1 != 0 ){
            QTimer::singleShot( subcycle_1 + ( m_interval * 4 ) + subcycle_2 + ( m_pauseBetweenSubcycles * 2 ),
                               this, SLOT(thirdSubcycle()) );
            QTimer::singleShot( subcycle_1 + ( m_interval * 4 ) + subcycle_2 + subcycle_3 + ( m_pauseBetweenSubcycles * 2 ),
                               this, SLOT(holdThirdSubcycle()) );
        }
        else if( subcycle_1 != 0 ){  //sub2 == 0
            QTimer::singleShot( subcycle_1 + ( m_interval * 2 ) + m_pauseBetweenSubcycles,
                               this, SLOT(thirdSubcycle()) );
            QTimer::singleShot( subcycle_1 + ( m_interval * 3 ) + subcycle_3 + m_pauseBetweenSubcycles,
                               this, SLOT(holdThirdSubcycle()) );
        }
        else{
            QTimer::singleShot( 0, this, SLOT(thirdSubcycle()) );
            QTimer::singleShot( subcycle_3+m_interval, this, SLOT(holdThirdSubcycle()) );
        }
    }
}

void SimpleJunction::exceptionWhenSubcycleSumEqualZero( uint subcycle_1, uint subcycle_2, uint subcycle_3 )
{
    if( subcycle_1 == 0 && subcycle_2 == 0 && subcycle_3 == 0 )
    {
        m_timeVectorForSubcycles[ 0 ] = 5000;
        m_timeVectorForSubcycles[ 1 ] = 5000;
        m_timeVectorForSubcycles[ 2 ] = 5000;
        runForSubcycles();
    }
}

void SimpleJunction::firstSubcycle()
{
    m_leftLight->letGoVehicles();
    m_rightLight->letGoVehicles();
}

void SimpleJunction::holdFirstSubcycle()
{
    uint subcycle_2 = m_timeVectorForSubcycles.at( 1 );
    uint subcycle_3 = m_timeVectorForSubcycles.at( 2 );
    if( subcycle_2 == 0 ){
        m_rightLight->holdVehicles();
    }
    m_leftLight->holdVehicles();

    if( subcycle_2 == 0 && subcycle_3 == 0 )
        runForSubcycles();
}

void SimpleJunction::secondSubcycle()
{
    m_leftAndStraightLight->letGoVehicles();

    uint subcycle_1 = m_timeVectorForSubcycles.at( 0 );
    if( subcycle_1 == 0 ){
        m_rightLight->letGoVehicles();
    }
}

void SimpleJunction::holdSecondSubcycle()
{
    m_leftAndStraightLight->holdVehicles();
    m_rightLight->holdVehicles();

    uint subcycle_3 = m_timeVectorForSubcycles.at( 2 );
    if( subcycle_3 == 0 )
        runForSubcycles();
}

void SimpleJunction::thirdSubcycle()
{
    m_rightAndStraightLight->letGoVehicles();
}

void SimpleJunction::holdThirdSubcycle()
{
    m_rightAndStraightLight->holdVehicles();
    runForSubcycles();
}

void SimpleJunction::setTimeVectorByGeneticAlgorithm()
{
//    LOG_INFO( "Set new time vector in %s", __FUNCTION__ );

//    /// av - averages on approriate cycle.
//    std::vector< float > av;
//    /// vn - vehicle number on approriate cycle.
//    std::vector< int > vn;

//    for( int i = 0 ; i < m_cyclesNumber ; i++ )
//    {
//        av.push_back( 2 );

//        vn.push_back( 3 );
//    }

//    GeneticAlgorithmManager geneticAlgorithmManager;
//    GAGenome genome = geneticAlgorithmManager.start( new GenomeData( m_cyclesNumber, av, vn ) );

//    GA1DArrayGenome< int > &arrayGenome = ( GA1DArrayGenome< int > & )genome;

//    QVector<int> time;
//    for( int i = 0 ; i < m_cyclesNumber ; i++ )
//    {
//        time.append( arrayGenome.gene( i ) );
//    }

//    m_timeVector = time;
}
