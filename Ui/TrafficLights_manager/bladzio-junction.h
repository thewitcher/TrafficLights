#ifndef BLADZIOJUNCTION_H
#define BLADZIOJUNCTION_H

#include "junction.h"

class BladzioJunction: public Junction
{
    Q_OBJECT

public:
    BladzioJunction( const QVector<TrafficLight*>& junction, QLCDNumber* vehicleCounter, int junctionId );
    ~BladzioJunction();

protected:
    void runForSubcycles();

private:
    TrafficLight* m_leftLight2a;
    TrafficLight* m_straightLight2a;
    TrafficLight* m_rightLight2a;
    TrafficLight* m_leftLight2b;
    TrafficLight* m_straightLight2b;
    TrafficLight* m_rightLight2b;
    TrafficLight* m_leftLight2c;
    TrafficLight* m_straightLight2c;
    TrafficLight* m_rightLight2c;
    TrafficLight* m_leftLight2d;
    TrafficLight* m_straightLight2d;
    TrafficLight* m_rightLight2d;

    uint m_subcycle_1;
    uint m_subcycle_2;
    uint m_subcycle_3;
    uint m_subcycle_4;

    void exceptionWhenSubcycleSumEqualZero();

public slots:
    void firstSubcycle();
    void secondSubcycle();
    void thirdSubcycle();
    void fourthSubcycle();

    void holdFirstSubcycle();
    void holdSecondSubcycle();
    void holdThirdSubcycle();
    void holdFourthSubcycle();
};

#endif // BLADZIOJUNCTION_H
