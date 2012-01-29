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

    int time = 0;

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
        if( t1v > 0 ){
            time = t1v + m_interval;
            QTimer::singleShot( time, this, SLOT( holdFirstVerticalSeries() ) )
                    ;
            time = time + m_interval;
            QTimer::singleShot( time , this, SLOT( secondVerticalSeries() ) );
        }
        else{
        QTimer::singleShot( time , this, SLOT( secondVerticalSeries() ) );   /* Series 2 */
        }
    }
    else
    {
        if ( t1v > 0 ){
            time = t1v + m_interval;
            QTimer::singleShot( time, this, SLOT( holdFirstVerticalSeries() ) );
        }
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if( t1h > 0 )
    {
        time = time + t2v;
        if( t2v > 0 ){
            QTimer::singleShot(time,this,SLOT( holdPartialSecondVerticalSeries()));
        }
            time = time + m_interval;
            QTimer::singleShot( time, this, SLOT(firstHorizontalSeries()));        /* Series 3 */
            time = time + t1h;
            QTimer::singleShot( time , this, SLOT(holdFirstHorizontalSeries()));

    }
    else
    {
        time = time + t2v;
        if ( t2v > 0 )
            QTimer::singleShot(time,this,SLOT( holdAllSecondVerticalSeries()));
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
        time = time + m_interval;
        QTimer::singleShot( time, this, SLOT( secondHorizontalSeries() ) );
        time = time + t2h;
        QTimer::singleShot( time, this, SLOT( holdSecondHorizontalSeries() ) );
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
    straightLight2a->letGoVehicles();
    rightLight2a->letGoVehicles();
    straightLight2c->letGoVehicles();
    rightLight2c->letGoVehicles();
}

void BladzioJunction::holdFirstVerticalSeries()
{
    leftLight2a->holdVehicles();
    leftLight2c->holdVehicles();
    rightLight2b->holdVehicles();
    rightLight2d->holdVehicles();
}

void BladzioJunction::holdPartialSecondVerticalSeries()
{
    straightLight2a->holdVehicles();
    straightLight2c->holdVehicles();
}

void BladzioJunction::holdAllSecondVerticalSeries()
{
    straightLight2a->holdVehicles();
    straightLight2c->holdVehicles();
    rightLight2a->holdVehicles();
    rightLight2c->holdVehicles();
}

void BladzioJunction::firstHorizontalSeries()
{
    leftLight2b->letGoVehicles();
    leftLight2d->letGoVehicles();
    if( t2v == 0 )
    {
        rightLight2a->letGoVehicles();
        rightLight2c->letGoVehicles();
    }
}

void BladzioJunction::secondHorizontalSeries()
{
    straightLight2b->letGoVehicles();
    straightLight2d->letGoVehicles();
    rightLight2b->letGoVehicles();
    rightLight2d->letGoVehicles();
}

void BladzioJunction::holdFirstHorizontalSeries()
{
    leftLight2b->holdVehicles();
    leftLight2d->holdVehicles();
    rightLight2a->holdVehicles();
    rightLight2c->holdVehicles();
}

void BladzioJunction::holdSecondHorizontalSeries()
{
    straightLight2b->holdVehicles();
    straightLight2d->holdVehicles();
    rightLight2b->holdVehicles();
    rightLight2d->holdVehicles();
    run();
}
