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
    m_subcycle_1 = m_timeVectorForSubcycles.at( 0 );
    m_subcycle_2 = m_timeVectorForSubcycles.at( 1 );
    m_subcycle_3 = m_timeVectorForSubcycles.at( 2 );

    /* Subcycle 1 */
    runFirstSubcycle( m_subcycle_1, this );

    /* Subcycle 2 */
    runSecondSubcycle( m_subcycle_1, m_subcycle_2, this );

    /* Subcycle 3 */
    runThirdSubcycle( m_subcycle_1, m_subcycle_2, m_subcycle_3, this );
}

void SimpleJunction::firstSubcycle()
{
    m_leftLight->letGoVehicles();
    m_rightLight->letGoVehicles();
}

void SimpleJunction::holdFirstSubcycle()
{
    if( m_subcycle_2 == 0 ){
        m_rightLight->holdVehicles();
    }
    m_leftLight->holdVehicles();

    if( m_subcycle_2 == 0 && m_subcycle_3 == 0 )
    {
        startAlgorithm();
        runForSubcycles();
    }
}

void SimpleJunction::secondSubcycle()
{
    m_leftAndStraightLight->letGoVehicles();

    if( m_subcycle_1 == 0 ){
        m_rightLight->letGoVehicles();
    }
}

void SimpleJunction::holdSecondSubcycle()
{
    m_leftAndStraightLight->holdVehicles();
    m_rightLight->holdVehicles();

    if( m_subcycle_3 == 0 )
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
