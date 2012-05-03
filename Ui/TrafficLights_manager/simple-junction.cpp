#include "simple-junction.h"
#include "../Lights/trafficlight.h"
#include "../../Logger/logger.h"
#include <QTimer>

SimpleJunction::SimpleJunction( const QVector<TrafficLight *> &junction, QLCDNumber* vehicleCounter, int junctionId ):
    Junction( junction, vehicleCounter, junctionId, SIMPLE ),
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
        runSingleShotForSubcycle_1_WhenTimeIsDiferrentThanZero( subcycle_1 );
    }
}

void SimpleJunction::runSubcycle_2( uint subcycle_1, uint subcycle_2 )
{
    if( subcycle_2 != 0 )
    {
        if( subcycle_1 != 0 ){
            runSingleShotForSubcycle_2_WhenTimeIsDiferrentThanZero( subcycle_1, subcycle_2 );
        }
        else{
            runSingleShotForSubcycle_2_WhenTimeAreEqualZero( subcycle_2 );
        }
    }
}

void SimpleJunction::runSubcycle_3( uint subcycle_1, uint subcycle_2, uint subcycle_3 )
{
    if( subcycle_3 != 0 )
    {
        if( subcycle_2 != 0 && subcycle_1 != 0 ){
            runSingleShotForSubcycle_3_WhenAllTimesAreDiferrentThanZero( subcycle_1, subcycle_2, subcycle_3 );
        }
        else if( subcycle_2 != 0 && subcycle_1 == 0 ){
            runSingleShotForSubcycle_3_WhenOneTimeIsDiferrentThanZero( subcycle_2, subcycle_3 );
        }
        else if( subcycle_1 != 0 && subcycle_2 == 0 ){
            runSingleShotForSubcycle_3_WhenOneTimeIsDiferrentThanZero( subcycle_1, subcycle_3 );
        }
        else if( subcycle_1 == 0 && subcycle_2 == 0 ){
            runSingleShotForSubcycle_3_WhenAllTimesAreEqualZero( subcycle_3 );
        }
    }
}

void SimpleJunction::runSingleShotForSubcycle_1_WhenTimeIsDiferrentThanZero( uint time )
{
    firstSubcycle();
    QTimer::singleShot( time + m_interval, this, SLOT(holdFirstSubcycle()));
}

void SimpleJunction::runSingleShotForSubcycle_2_WhenTimeAreEqualZero( uint time )
{
    secondSubcycle();
    QTimer::singleShot( time + m_interval, this, SLOT(holdSecondSubcycle()));
}

void SimpleJunction::runSingleShotForSubcycle_2_WhenTimeIsDiferrentThanZero( uint time_1, uint time_2 )
{
    QTimer::singleShot( time_1 + ( m_interval * 2 ) + m_pauseBetweenSubcycles, this, SLOT(secondSubcycle()));
    QTimer::singleShot( time_1 + time_2 + ( m_interval * 3 ) + m_pauseBetweenSubcycles,
                        this, SLOT(holdSecondSubcycle()));
}

void SimpleJunction::runSingleShotForSubcycle_3_WhenAllTimesAreEqualZero( uint time )
{
    QTimer::singleShot( 0, this, SLOT(thirdSubcycle()) );
    QTimer::singleShot( time + m_interval, this, SLOT(holdThirdSubcycle()) );
}

void SimpleJunction::runSingleShotForSubcycle_3_WhenAllTimesAreDiferrentThanZero( uint time_1, uint time_2, uint time_3 )
{
    QTimer::singleShot( time_1 + time_2 + ( m_interval * 4 ) + ( m_pauseBetweenSubcycles * 2 ),
                       this, SLOT(thirdSubcycle()) );
    QTimer::singleShot( time_1 + time_2 + time_3 + ( m_interval * 5 ) + ( m_pauseBetweenSubcycles * 2 ),
                       this, SLOT(holdThirdSubcycle()) );
}

void SimpleJunction::runSingleShotForSubcycle_3_WhenOneTimeIsDiferrentThanZero( uint time_1, uint time_2 )
{
    QTimer::singleShot( time_1 + ( m_interval * 2 ) + m_pauseBetweenSubcycles,
                       this, SLOT(thirdSubcycle()) );
    QTimer::singleShot( time_1 + time_2 + ( m_interval * 3 ) + m_pauseBetweenSubcycles,
                       this, SLOT(holdThirdSubcycle()) );
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
    {
        startAlgorithm();
        runForSubcycles();
    }
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
    {
        startAlgorithm();
        runForSubcycles();
    }
}

void SimpleJunction::thirdSubcycle()
{
    m_rightAndStraightLight->letGoVehicles();
}

void SimpleJunction::holdThirdSubcycle()
{
    m_rightAndStraightLight->holdVehicles();
    startAlgorithm();
    runForSubcycles();
}
