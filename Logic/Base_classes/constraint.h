#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <QHash>
#include <QDebug>

class Counter
{
public:
    Counter( int initValue, int maxValue );
    Counter();

    // Adds one to counter and if current value equals m_maxValue then returns true. Otherwise returns false.
    bool isFinished();
    void restart();

private:
    int m_currentValue;
    int m_maxValue;
    int m_initValue;
};

struct Constraint
{
    virtual void createCounter( const QString& counterName, int initValue = 0, int maxValue = 10 );
    virtual bool isCounterFinished( const QString& counterName );
    virtual bool endAlgorithm() const;
    virtual void restartCounter( const QString& counterName );

    void clearCounters();

    QHash< QString, Counter > m_counters;
};

#endif // CONSTRAINT_H
