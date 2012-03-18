#include "constraint.h"

bool Constraint::endAlgorithm() const
{
    qDebug() << "Constraint::endAlgorithm";

    static int i = 0;

    if( ++i == 4 )
    {
        return false;
    }

    return true;
}

void Constraint::createCounter( const QString &counterName, int initValue, int maxValue )
{
    Q_ASSERT( m_counters.contains( counterName ) == false );

    m_counters.insert( counterName, Counter( initValue, maxValue ) );
}

bool Constraint::isCounterFinished( const QString &counterName )
{
    return ( m_counters[ counterName ].isFinished() );
}

void Constraint::clearCounters()
{
    m_counters.clear();
}

void Constraint::restartCounter( const QString &counterName )
{
    m_counters[ counterName ].restart();
}

///////////////// Counter /////////////////
Counter::Counter( int initValue, int maxValue ):
    m_currentValue( initValue ),
    m_maxValue( maxValue ),
    m_initValue( initValue )
{}

Counter::Counter():
    m_currentValue( 0 ),
    m_maxValue( 0 )
{}

bool Counter::isFinished()
{
    if( m_currentValue++ >= m_maxValue )
    {
        return true;
    }

    return false;
}

void Counter::restart()
{
    m_currentValue = m_initValue;
}
