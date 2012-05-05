#include "bladzio-junction.h"
#include "../Lights/trafficlight.h"
#include "../../Logger/logger.h"
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
    m_subcycle_1 = m_timeVectorForSubcycles.at( 0 );
    m_subcycle_2 = m_timeVectorForSubcycles.at( 1 );
    m_subcycle_3 = m_timeVectorForSubcycles.at( 2 );
    m_subcycle_4 = m_timeVectorForSubcycles.at( 3 );

    /* Series 1 */
    runFirstSubcycle( m_subcycle_1, this );

    /* Series 2 */
    runSecondSubcycle( m_subcycle_1, m_subcycle_2, this );

    /* Series 3 */
    runThirdSubcycle( m_subcycle_1, m_subcycle_2, m_subcycle_3, this );

    /* Series 4 */
    runFourthSubcycle( m_subcycle_1, m_subcycle_2, m_subcycle_3, m_subcycle_4, this );

    // Exception
    exceptionWhenSubcycleSumEqualZero();
}

void BladzioJunction::exceptionWhenSubcycleSumEqualZero()
{
    if( m_subcycle_1 == 0 && m_subcycle_2 == 0 && m_subcycle_3 == 0 && m_subcycle_4 == 0 )
    {
        for( int i = 0; i < m_timeVectorForSubcycles.size(); i++ )
        {
            m_timeVectorForSubcycles[ i ] = 5000;
        }
        runForSubcycles();
    }
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

    if( m_subcycle_2 == 0 && m_subcycle_3 == 0 && m_subcycle_4 == 0 )
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

    if( m_subcycle_3 == 0 )
    {
        m_rightLight2b->holdVehicles();
        m_rightLight2d->holdVehicles();
    }

    if( m_subcycle_3 == 0 && m_subcycle_4 == 0 )
    {
        startAlgorithm();
        runForSubcycles();
    }
}

void BladzioJunction::thirdSubcycle()
{
    m_straightLight2b->letGoVehicles();
    m_straightLight2d->letGoVehicles();

    if( m_subcycle_2 == 0 )
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

    if( m_subcycle_4 == 0 )
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
