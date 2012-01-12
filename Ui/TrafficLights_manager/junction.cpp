#include "junction.h"
#include "../Lights/trafficlight.h"
#include <QTimer>
#include <QDebug>

Junction::Junction( const QVector<TrafficLight *>& junction, const QVector<unsigned char>& cycles, QObject* parent ):
    QObject( parent ),
    m_junction( junction ),
    m_currentCycle( 0 )
{
    setGreenLightTime( QVector<unsigned char>() << 8 << 8 );
    createCycles( cycles );

    run();
}

void Junction::setGreenLightTime( QVector<unsigned char>& time )
{
    m_timesForGreenLight = time;
}

void Junction::createCycles( const QVector<unsigned char>& cycles )
{
    Q_ASSERT( m_junction.count() == cycles.count() );

    for( int i = 0 ; i < m_junction.count() ; i++ )
    {
        m_junction.at( i )->setCycleNumber( cycles.at( i ) );
    }
}

void Junction::run()
{
    setAllToRedLight();

    if( m_currentCycle < m_timesForGreenLight.count() )
    {
        setCycleToGreenLight( m_currentCycle );

        QTimer::singleShot( m_timesForGreenLight.at( m_currentCycle++ ) * 1000, this, SLOT(run()) );
    }
    else
    {
        m_currentCycle = 0;
        run();
    }
}

void Junction::setAllToRedLight()
{
    for( int i = 0 ; i < m_junction.count() ; i++ )
    {
        m_junction.at( i )->holdVehicles();
    }
}

void Junction::setCycleToGreenLight( unsigned char cycleNumber )
{
    for( int i = 0 ; i < m_junction.count() ; i++ )
    {
        if( m_junction.at( i )->cycleNumber() == 0 )
        {
            m_junction.at( i )->letGoVehicles();
        }
    }
}

void Junction::setCycleToRedLight( unsigned char cycleNumber )
{
    for( int i = 0 ; i < m_junction.count() ; i++ )
    {
        if( m_junction.at( i )->cycleNumber() == 0 )
        {
            m_junction.at( i )->holdVehicles();
        }
    }
}
