#ifndef SIMPLEJUNCTION_H
#define SIMPLEJUNCTION_H

#include "junction.h"

class SimpleJunction: public Junction
{
    Q_OBJECT

public:
    SimpleJunction( const QVector<TrafficLight*>& junction, QLCDNumber* vehicleCounter, int junctionId );
    ~SimpleJunction();

protected:
    void runForSubcycles();

private:
    TrafficLight* m_leftLight;
    TrafficLight* m_rightLight;
    TrafficLight* m_leftAndStraightLight;
    TrafficLight* m_rightAndStraightLight;

    uint m_subcycle_1;
    uint m_subcycle_2;
    uint m_subcycle_3;

public slots:
    void firstSubcycle();
    void secondSubcycle();
    void thirdSubcycle();
    void holdFirstSubcycle();
    void holdSecondSubcycle();
    void holdThirdSubcycle();
};

#endif // SIMPLEJUNCTION_H
