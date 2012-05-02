#ifndef EVENTTIMER_H
#define EVENTTIMER_H

#include <QObject>

class QTimer;

class EventTimer: public QObject
{

    Q_OBJECT

public:
    enum DayTime { DAY = 60000, NIGHT = 50000 };

    EventTimer( QObject* parent = NULL );
    ~EventTimer();

    void startDayTimeTimer();
    bool isDark() const;

private:
    QTimer* m_timer;
    DayTime m_currentDayTime;

signals:
    void day();
    void night();

private slots:
    void setDay();
    void setNight();
};
#endif // EVENTTIMER_H
