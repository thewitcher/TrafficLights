#include "bladzio-junction.h"
#include "../Lights/trafficlight.h"
#include "../../Logger/logger.h"
//#include "../../Logic/Genetic_algorithm/GA/genome-data.h"
//#include "../../Logic/Genetic_algorithm/GA/GA1DArrayGenome.h"
//#include "../../Logic/Genetic_algorithm/GA/genetic-algorithm-manager.h"
#include <QTimer>

BladzioJunction::BladzioJunction( const QVector<TrafficLight *> &junction, QLCDNumber* vehicleCounter, int junctionId ):
    Junction( junction, vehicleCounter, junctionId, BLADZIO ),
    m_leftLight2a( junction.at( 0 ) ),
    m_straightLight2a( junction.at( 1 ) ),
    m_rightLight2a( junction.at( 2 ) ),
    m_leftLight2b( junction.at( 3 ) ),
    m_straightLight2b( junction.at( 4 ) ),
    m_rightLight2b( junction.at( 5 ) ),
    m_leftLight2c( junction.at( 6 ) ),
    m_straightLight2c( junction.at( 7 ) ),
    m_rightLight2c( junction.at( 8 ) ),
    m_leftLight2d( junction.at( 9 ) ),
    m_straightLight2d( junction.at( 10 ) ),
    m_rightLight2d( junction.at( 11 ) )
{}

BladzioJunction::~BladzioJunction()
{}

void BladzioJunction::runForSubcycles()
{
    uint subcycle_1 = m_timeVectorForSubcycles.at( 0 );
    uint subcycle_2 = m_timeVectorForSubcycles.at( 1 );
    uint subcycle_3 = m_timeVectorForSubcycles.at( 2 );
    uint subcycle_4 = m_timeVectorForSubcycles.at( 3 );

    /* Series 1 */
    runFirstSubcycle( subcycle_1 );

    /* Series 2 */
    runSecondSubcycle( subcycle_1, subcycle_2 );

    /* Series 3 */
    runThirdSubcycle( subcycle_1, subcycle_2, subcycle_3 );

    /* Series 4 */
    runFourthSubcycle( subcycle_1, subcycle_2, subcycle_3, subcycle_4 );

    // Exception
    exceptionWhenSubcycleSumEqualZero( subcycle_1, subcycle_2, subcycle_3, subcycle_4 );
}

void BladzioJunction::runFirstSubcycle( uint subcycle_1 )
{
    if( subcycle_1 != 0 )
    {
        runSingleShotForSubcycle_1_WhenTimeIsDiferrentThanZero( subcycle_1 );
    }
}

void BladzioJunction::runSecondSubcycle( uint subcycle_1, uint subcycle_2 )
{
    if( subcycle_2 != 0 )
    {
        if( subcycle_1 != 0 )
        {
            runSingleShotForSubcycle_2_WhenTimeIsDiferrentThanZero( subcycle_1, subcycle_2 );
        }
        else{
            runSingleShotForSubcycle_2_WhenTimeAreEqualZero( subcycle_2 );
        }
    }
}

void BladzioJunction::runThirdSubcycle( uint subcycle_1, uint subcycle_2, uint subcycle_3 )
{
    if( subcycle_3 != 0 )
    {
        if( subcycle_1 != 0 && subcycle_2 != 0 )
        {
            runSingleShotForSubcycle_3_WhenAllTimesAreDiferrentThanZero( subcycle_1, subcycle_2, subcycle_3 );
        }
        else if( subcycle_1 == 0 && subcycle_2 != 0 )
        {
            runSingleShotForSubcycle_3_WhenOneTimeIsDiferrentThanZero( subcycle_2, subcycle_3 );
        }
        else if( subcycle_1 != 0 && subcycle_2 == 0 )
        {
            runSingleShotForSubcycle_3_WhenOneTimeIsDiferrentThanZero( subcycle_1, subcycle_3 );
        }
        else if( subcycle_1 == 0 && subcycle_2 == 0 )
        {
            runSingleShotForSubcycle_3_WhenAllTimesAreEqualZero( subcycle_3 );
        }
    }
}

void BladzioJunction::runFourthSubcycle( uint subcycle_1, uint subcycle_2, uint subcycle_3, uint subcycle_4 )
{
    if( subcycle_4 != 0 )
    {
        if( subcycle_1 != 0 && subcycle_2 != 0 && subcycle_3 != 0 )
        {
            runSingleShotForSubcycle_4_WhenAllTimesAreDiferrentThanZero( subcycle_1, subcycle_2, subcycle_3, subcycle_4 );
        }
        else if( subcycle_1 != 0 && subcycle_2 != 0 && subcycle_3 == 0 )
        {
            runSingleShotForSubcycle_4_WhenTwoTimesAreDiferrentThanZero( subcycle_1, subcycle_2, subcycle_4 );
        }
        else if( subcycle_1 == 0 && subcycle_2 != 0 && subcycle_3 != 0 )
        {
            runSingleShotForSubcycle_4_WhenTwoTimesAreDiferrentThanZero( subcycle_2, subcycle_3, subcycle_4 );
        }
        else if( subcycle_1 != 0 && subcycle_2 == 0 && subcycle_3 != 0 )
        {
            runSingleShotForSubcycle_4_WhenTwoTimesAreDiferrentThanZero( subcycle_1, subcycle_3, subcycle_4 );
        }
        else if( subcycle_1 != 0 && subcycle_2 == 0 && subcycle_3 == 0 )
        {
            runSingleShotForSubcycle_4_WhenOneTimeIsDiferrentThanZero( subcycle_1, subcycle_4 );
        }
        else if( subcycle_1 == 0 && subcycle_2 != 0 && subcycle_3 == 0 )
        {
            runSingleShotForSubcycle_4_WhenOneTimeIsDiferrentThanZero( subcycle_2, subcycle_4 );
        }
        else if( subcycle_1 == 0 && subcycle_2 == 0 && subcycle_3 != 0 )
        {
            runSingleShotForSubcycle_4_WhenOneTimeIsDiferrentThanZero( subcycle_3, subcycle_4 );
        }
        else if( subcycle_1 == 0 && subcycle_2 == 0 && subcycle_3 == 0 )
        {
            runSingleShotForSubcycle_4_WhenAllTimesAreEqualZero( subcycle_4 );
        }
    }
}

void BladzioJunction::exceptionWhenSubcycleSumEqualZero( uint subcycle_1, uint subcycle_2, uint subcycle_3, uint subcycle_4 )
{
    if( subcycle_1 == 0 && subcycle_2 == 0 && subcycle_3 == 0 && subcycle_4 == 0 )
    {
        m_timeVectorForSubcycles[ 0 ] = 5000;
        m_timeVectorForSubcycles[ 1 ] = 5000;
        m_timeVectorForSubcycles[ 2 ] = 5000;
        m_timeVectorForSubcycles[ 3 ] = 5000;
        runForSubcycles();
    }
}

void BladzioJunction::runSingleShotForSubcycle_1_WhenTimeIsDiferrentThanZero( uint time )
{
    firstSubcycle();
    QTimer::singleShot( time + m_interval, this, SLOT(holdFirstSubcycle()));
}

void BladzioJunction::runSingleShotForSubcycle_2_WhenTimeAreEqualZero( uint time )
{
    secondSubcycle();
    QTimer::singleShot( time + m_interval, this, SLOT(holdSecondSubcycle()));
}

void BladzioJunction::runSingleShotForSubcycle_2_WhenTimeIsDiferrentThanZero( uint time_1, uint time_2 )
{
    QTimer::singleShot( time_1 + ( m_interval * 2 ) + m_pauseBetweenSubcycles, this, SLOT(secondSubcycle()));
    QTimer::singleShot( time_1 + time_2 + ( m_interval * 3 ) + m_pauseBetweenSubcycles,
                        this, SLOT(holdSecondSubcycle()));
}

void BladzioJunction::runSingleShotForSubcycle_3_WhenAllTimesAreEqualZero( uint time )
{
    thirdSubcycle();
    QTimer::singleShot( time + m_interval, this, SLOT(holdThirdSubcycle()));
}

void BladzioJunction::runSingleShotForSubcycle_3_WhenAllTimesAreDiferrentThanZero( uint time_1, uint time_2, uint time_3 )
{
    QTimer::singleShot( time_1 + time_2 + ( m_interval * 4 ) + ( m_pauseBetweenSubcycles * 2 ),
                        this, SLOT(thirdSubcycle()));
    QTimer::singleShot( time_1 + time_2 + time_3 + ( m_interval * 5 ) + ( m_pauseBetweenSubcycles * 2 ),
                        this, SLOT(holdThirdSubcycle()));
}

void BladzioJunction::runSingleShotForSubcycle_3_WhenOneTimeIsDiferrentThanZero( uint time_1, uint time_2 )
{
    QTimer::singleShot( time_1 + ( m_interval * 2 ) + m_pauseBetweenSubcycles, this, SLOT(thirdSubcycle()));
    QTimer::singleShot( time_1 + time_2 + ( m_interval * 3 ) + m_pauseBetweenSubcycles,
                        this, SLOT(holdThirdSubcycle()));
}

void BladzioJunction::runSingleShotForSubcycle_4_WhenOneTimeIsDiferrentThanZero( uint time_1, uint time_2 )
{
    QTimer::singleShot( time_1 + ( m_interval * 2 ) + m_pauseBetweenSubcycles,
                        this, SLOT(fourthSubcycle()));
    QTimer::singleShot( time_1 + time_2 + ( m_interval * 3 ) + m_pauseBetweenSubcycles,
                        this, SLOT(holdFourthSubcycle()));
}

void BladzioJunction::runSingleShotForSubcycle_4_WhenTwoTimesAreDiferrentThanZero( uint time_1, uint time_2, uint time_3 )
{
    QTimer::singleShot( time_1 + time_2 + ( m_interval * 4 ) + ( m_pauseBetweenSubcycles * 2 ),
                        this, SLOT(fourthSubcycle()));
    QTimer::singleShot( time_1 + time_2 + time_3 + ( m_interval * 5 ) + ( m_pauseBetweenSubcycles * 2 ),
                        this, SLOT(holdFourthSubcycle()));
}

void BladzioJunction::runSingleShotForSubcycle_4_WhenAllTimesAreDiferrentThanZero( uint time_1, uint time_2, uint time_3, uint time_4 )
{
    QTimer::singleShot( time_1 + time_2 + time_3 + ( m_interval * 6 ) + ( m_pauseBetweenSubcycles * 3),
                        this, SLOT(fourthSubcycle()));
    QTimer::singleShot( time_1 + time_2 + time_3 + time_4 + ( m_interval * 7 ) + ( m_pauseBetweenSubcycles * 3),
                        this, SLOT(holdFourthSubcycle()));
}

void BladzioJunction::runSingleShotForSubcycle_4_WhenAllTimesAreEqualZero( uint time )
{
    fourthSubcycle();
    QTimer::singleShot( time + m_interval, this, SLOT(holdFourthSubcycle()));
}

void BladzioJunction::firstSubcycle()
{
    m_straightLight2c->letGoVehicles();
    m_rightLight2c->letGoVehicles();
    m_straightLight2a->letGoVehicles();
    m_rightLight2a->letGoVehicles();
}

void BladzioJunction::holdFirstSubcycle()
{
    m_straightLight2a->holdVehicles();
    m_rightLight2a->holdVehicles();
    m_straightLight2c->holdVehicles();
    m_rightLight2c->holdVehicles();

    uint subcycle_2 = m_timeVectorForSubcycles.at( 1 );
    uint subcycle_3 = m_timeVectorForSubcycles.at( 2 );
    uint subcycle_4 = m_timeVectorForSubcycles.at( 3 );

    if( subcycle_2 == 0 && subcycle_3 == 0 && subcycle_4 == 0 )
    {
        startAlgorithm();
        runForSubcycles();
    }
}

void BladzioJunction::secondSubcycle()
{
    m_leftLight2a->letGoVehicles();
    m_leftLight2c->letGoVehicles();
    m_rightLight2b->letGoVehicles();
    m_rightLight2d->letGoVehicles();
}

void BladzioJunction::holdSecondSubcycle()
{
    m_leftLight2a->holdVehicles();
    m_leftLight2c->holdVehicles();

    uint subcycle_3 = m_timeVectorForSubcycles.at( 2 );
    if( subcycle_3 == 0 )
    {
        m_rightLight2b->holdVehicles();
        m_rightLight2d->holdVehicles();
    }

    uint subcycle_4 = m_timeVectorForSubcycles.at( 3 );

    if( subcycle_3 == 0 && subcycle_4 == 0 )
    {
        startAlgorithm();
        runForSubcycles();
    }
}

void BladzioJunction::thirdSubcycle()
{
    m_straightLight2b->letGoVehicles();
    m_straightLight2d->letGoVehicles();

    uint subcycle_2 = m_timeVectorForSubcycles.at( 1 );
    if( subcycle_2 == 0 )
    {
        m_rightLight2b->letGoVehicles();
        m_rightLight2d->letGoVehicles();
    }
}

void BladzioJunction::holdThirdSubcycle()
{
    m_straightLight2b->holdVehicles();
    m_rightLight2b->holdVehicles();
    m_straightLight2d->holdVehicles();
    m_rightLight2d->holdVehicles();

    uint subcycle_4 = m_timeVectorForSubcycles.at( 3 );

    if( subcycle_4 == 0 )
    {
        startAlgorithm();
        runForSubcycles();
    }
}

void BladzioJunction::fourthSubcycle()
{
    m_leftLight2b->letGoVehicles();
    m_leftLight2d->letGoVehicles();
    m_rightLight2a->letGoVehicles();
    m_rightLight2c->letGoVehicles();
}

void BladzioJunction::holdFourthSubcycle()
{
    m_leftLight2b->holdVehicles();
    m_leftLight2d->holdVehicles();
    m_rightLight2a->holdVehicles();
    m_rightLight2c->holdVehicles();

    startAlgorithm();
    runForSubcycles();
}
