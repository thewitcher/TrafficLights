#include "bladzio-junction.h"
#include "../Lights/trafficlight.h"
#include <QTimer>

BladzioJunction::BladzioJunction( const QVector<TrafficLight *> &junction ):
    Junction( junction ),
    leftLight2a( junction.at( 0 ) ),
    straightLight2a( junction.at( 1 ) ),
    rightLight2a( junction.at( 2 ) ),
    leftLight2b( junction.at( 3 ) ),
    straightLight2b( junction.at( 4 ) ),
    rightLight2b( junction.at( 5 ) ),
    leftLight2c( junction.at( 6 ) ),
    straightLight2c( junction.at( 7 ) ),
    rightLight2c( junction.at( 8 ) ),
    leftLight2d( junction.at( 9 ) ),
    straightLight2d( junction.at( 10 ) ),
    rightLight2d( junction.at( 11 ) )
{
}

BladzioJunction::~BladzioJunction()
{
}

void BladzioJunction::run()
{
    t1v = m_timeVector.at( 0 );
    t2v = m_timeVector.at( 1 );
    t3v = m_timeVector.at( 2 );
    t1h = m_timeVector.at( 3 );
    t2h = m_timeVector.at( 4 );
    t3h = m_timeVector.at( 5 );


    if( t3h > t1v )
    {
        t3h -= t1v;
    }
    if( t1v > 0 )
    {
        firstVertivalSeries();                          /* Series 1 */
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if( t2v > t3v )
    {
        t3v = t2v;
    }
    else
    {
        t2v = t3v;
    }
    if( t2v > 0 )
    {
        QTimer::singleShot( (t1v + m_interval) , this, SLOT(secondVerticalSeries()));   /* Series 2 */
        QTimer::singleShot( ( t2v + t1v + m_interval), this, SLOT(turnOffSecondVerticalSeries()));
    }
    else
    {
        QTimer::singleShot( t1v + m_interval, this, SLOT(turnOffFirstVerticalSeries()));
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if( t3v > t1h)
    {
        t3v -= t1h;
    }
    if( t1h > 0 )
    {
        QTimer::singleShot( ( t2v + t1v + (m_interval*2) ), this, SLOT(firstHorizontalSeries()));        /* Series 3 */
        QTimer::singleShot( (t2v + t1v + t1h + (m_interval*2) ), this, SLOT(turnOffFirstHorizontalSeries()));
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if( t2h > t3h )
    {
        t3h = t2h;
    }
    else
    {
        t2h = t3h;
    }
    if( t2h > 0 )
    {
        QTimer::singleShot( ( t2v + t1v + t1h + (m_interval*3) ), this, SLOT(secondHorizontalSeries()) );
        QTimer::singleShot( ( t2v + t1v + t1h + t2h + (m_interval*3) ), this, SLOT(turnOffSecondHorizontalSeties()) );
    }
}

void BladzioJunction::firstVertivalSeries()
{
    leftLight2a->letGoVehicles();
    leftLight2c->letGoVehicles();
    rightLight2b->letGoVehicles();
    rightLight2d->letGoVehicles();
}

void BladzioJunction::secondVerticalSeries()
{
    turnOffFirstVerticalSeries();
    straightLight2a->letGoVehicles();
    rightLight2a->letGoVehicles();
    straightLight2c->letGoVehicles();
    rightLight2c->letGoVehicles();
}

void BladzioJunction::turnOffFirstVerticalSeries()
{
    leftLight2a->holdVehicles();
    leftLight2c->holdVehicles();
    if( t1h > 0 )
    {
        rightLight2b->holdVehicles();
        rightLight2d->holdVehicles();
    }
}

void BladzioJunction::turnOffSecondVerticalSeries()
{
    straightLight2a->holdVehicles();
    straightLight2c->holdVehicles();
    if( t1h == 0 )
    {
        rightLight2a->holdVehicles();
        rightLight2c->holdVehicles();
    }
}

void BladzioJunction::firstHorizontalSeries()
{
    leftLight2b->letGoVehicles();
    leftLight2d->letGoVehicles();
    if( t1h == 0 )
    {
        rightLight2a->holdVehicles();
        rightLight2c->holdVehicles();
    }
}

void BladzioJunction::secondHorizontalSeries()
{
    straightLight2b->letGoVehicles();
    straightLight2d->letGoVehicles();
    rightLight2b->letGoVehicles();
    rightLight2d->letGoVehicles();
}

void BladzioJunction::turnOffFirstHorizontalSeries()
{
    leftLight2b->holdVehicles();
    leftLight2d->holdVehicles();
    rightLight2a->holdVehicles();
    rightLight2c->holdVehicles();

}

void BladzioJunction::turnOffSecondHorizontalSeties()
{
    straightLight2b->holdVehicles();
    straightLight2d->holdVehicles();
    rightLight2b->holdVehicles();
    rightLight2d->holdVehicles();
//    run();
}
