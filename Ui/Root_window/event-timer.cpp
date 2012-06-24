#include "event-timer.h"
#include "../DatabaseManager/database.h"
#include <QTimer>
#include <QTimerEvent>
#include <QVector>
#include <QtGui/QApplication>

EventTimer::EventTimer( QObject *parent ):
    QObject( parent ),
    m_currentDayTime( DAY ),
    m_database( NULL )
{
}

EventTimer::~EventTimer()
{
    if( m_database != NULL )
    {
        delete m_database;
    }
}

void EventTimer::startDayPartTimer()
{
    m_dayPartTimerId = startTimer( DAY_PART_INTERVAL );
}

void EventTimer::startStatisticTimer( const QVector<Junction*> &junctions )
{
    m_database = new Database( junctions );
    m_database->init();

    m_statisticTimerId = startTimer( STATISTIC_INTERVAL_LOW );
}

void EventTimer::startTimeoutTimer( int timeout )
{
    m_timeoutTimerId = startTimer( timeout * 60 * 1000 );
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

void EventTimer::writeStatisticsToDatabase()
{
    m_database->start();
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
        writeStatisticsToDatabase();
    }
    else if( event->timerId() == m_timeoutTimerId )
    {
        qApp->quit();
    }
}
