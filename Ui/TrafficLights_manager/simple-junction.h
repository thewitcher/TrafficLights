#ifndef SIMPLEJUNCTION_H
#define SIMPLEJUNCTION_H

#include "junction.h"

class SimpleJunction: public Junction
{

    Q_OBJECT

public:
    SimpleJunction( const QVector<TrafficLight*>& junction, QLCDNumber* vehicleCounter );
    ~SimpleJunction();

protected:
    void run();

private:
    TrafficLight* m_leftLight;
    TrafficLight* m_rightLight;
    TrafficLight* m_leftAndStraightLight;
    TrafficLight* m_rightAndStraightLight;
    uint m_leftTime;
    uint m_leftAndStraightTime;

public slots:
    void firstSeries();
    void secondSeries();
    void thirdSeries();
    void holdFirst();
    void holdFirstTwoCondition();
    void holdSecond();
    void holdThird();
};

#endif // SIMPLEJUNCTION_H
