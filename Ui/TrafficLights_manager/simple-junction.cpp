#include "simple-junction.h"
#include "../Lights/trafficlight.h"
#include <QTimer>

SimpleJunction::SimpleJunction( const QVector<TrafficLight *> &junction ):
    Junction( junction ),
    leftLight( m_trafficLightVector.at( 0 ) ),
    rightLight( m_trafficLightVector.at( 1 ) ),
    leftAndStraightLight( m_trafficLightVector.at( 2 ) ),
    rightAndStraightLight( m_trafficLightVector.at( 3 ) )
{
    run();
}

SimpleJunction::~SimpleJunction()
{
}

void SimpleJunction::run()
{
    if( m_timeVector.count() != 0 ){

    unsigned int rightTime = m_timeVector.at( 1 );
    unsigned int rightAndStraightTime = m_timeVector.at( 3 );
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
            int timeThirdSeries = m_leftTime + (m_interval*2) + m_leftAndStraightTime;
            QTimer::singleShot(timeThirdSeries, this, SLOT(holdSecond()));
        }
    }
    }
}

void SimpleJunction::firstSeries()
{
    leftLight->letGoVehicles();
    rightLight->letGoVehicles();
}

void SimpleJunction::secondSeries()
{
    if( m_leftTime == 0)
        rightLight->letGoVehicles();

    leftAndStraightLight->letGoVehicles();
}

void SimpleJunction::thirdSeries()
{
    if( m_leftAndStraightTime > 0)
    {
        rightLight->holdVehicles();
        leftAndStraightLight->holdVehicles();
    }
    rightAndStraightLight->letGoVehicles();
}

void SimpleJunction::holdFirst()
{
     leftLight->holdVehicles();
}

void SimpleJunction::holdFirstTwoCondition()
{
    leftLight->holdVehicles();
    rightLight->holdVehicles();
}

void SimpleJunction::holdSecond()
{
    rightLight->holdVehicles();
    leftAndStraightLight->holdVehicles();
    run();
}

void SimpleJunction::holdThird()
{
    rightAndStraightLight->holdVehicles();
    run();
}

