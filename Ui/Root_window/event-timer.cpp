#include "event-timer.h"
#include <QTimer>

EventTimer::EventTimer( QObject *parent ):
    QObject( parent ),
    m_timer( new QTimer ),
    m_currentDayTime( DAY )
{
}

EventTimer::~EventTimer()
{
    delete m_timer;
}

void EventTimer::startDayTimeTimer()
{
    m_timer->singleShot( DAY, this, SLOT(setNight()) );
}

void EventTimer::setNight()
{
    emit night();

    m_currentDayTime = NIGHT;

    m_timer->singleShot( NIGHT, this, SLOT(setDay()) );

}

void EventTimer::setDay()
{
    emit day();

    m_currentDayTime = DAY;

    m_timer->singleShot( DAY, this, SLOT(setNight()) );
}

bool EventTimer::isDark() const
{
    switch( m_currentDayTime )
    {
    case DAY:
        return false;
        break;
    case NIGHT:
        return true;
        break;
    }

    return false;
}
