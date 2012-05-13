#include "event-timer.h"
#include "../DatabaseManager/database.h"
#include <QTimer>
#include <QTimerEvent>
#include <QVector>


EventTimer::EventTimer( QObject *parent ):
    QObject( parent ),
    m_currentDayTime( DAY )
{
}

EventTimer::~EventTimer()
{}

void EventTimer::startDayPartTimer()
{
    m_dayPartTimerId = startTimer( DAY_PART_INTERVAL );
}

void EventTimer::startStatisticTimer( const QVector<Junction*> &junctions )
{
    Database::init();
    m_junctions = junctions;

    m_statisticTimerId = startTimer( STATISTIC_INTERVAL_LOW );
}

void EventTimer::setNight()
{
    emit night();

    m_currentDayTime = NIGHT;
}

void EventTimer::setDay()
{
    emit day();

    m_currentDayTime = DAY;
}

bool EventTimer::isDark() const
{
    return m_currentDayTime;
}

void EventTimer::writeStatisticsToDatabase( const Junction *junction )
{
    Database::writeStatisticToDatabase( junction );
}

void EventTimer::timerEvent( QTimerEvent *event )
{
    if( event->timerId() == m_dayPartTimerId )
    {
        if( m_currentDayTime == DAY )
        {
            setNight();
        }
        else
        {
            setDay();
        }
    }
    else if( event->timerId() == m_statisticTimerId )
    {
        for( int i = 0 ; i < m_junctions.count() ; i++ )
        {
            writeStatisticsToDatabase( m_junctions.at( i ) );
        }
    }
}
