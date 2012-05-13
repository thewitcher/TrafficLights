#ifndef EVENTTIMER_H
#define EVENTTIMER_H

#include <QObject>
#include "../Ui/TrafficLights_manager/junction.h"


class EventTimer: public QObject
{

    Q_OBJECT

public:
    enum DayPart { DAY = 0, NIGHT = 1 };
    enum Intervals { DAY_PART_INTERVAL = 60000, STATISTIC_INTERVAL_LOW = 10000 };

    EventTimer( QObject* parent = NULL );
    ~EventTimer();

    void startDayPartTimer();
    void startStatisticTimer( const QVector<Junction*>& junctions );
    bool isDark() const;
    void writeStatisticsToDatabase( const Junction *junction );

private:
    int m_dayPartTimerId;
    int m_statisticTimerId;
    DayPart m_currentDayTime;
    QVector<Junction*> m_junctions;

    void timerEvent( QTimerEvent * event );

signals:
    void day();
    void night();

private slots:
    void setDay();
    void setNight();
};
#endif // EVENTTIMER_H
