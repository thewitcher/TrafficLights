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

    void runSubcycle_1();
    void runSubcycle_2();
    void runSubcycle_3();
    void exceptionWhenSubcycleSumEqualZero();

    void runSingleShotForSubcycle_1_WhenTimeIsDiferrentThanZero( uint time );

    void runSingleShotForSubcycle_2_WhenTimeIsDiferrentThanZero( uint time_1, uint time_2 );
    void runSingleShotForSubcycle_2_WhenTimeAreEqualZero( uint time );

    void runSingleShotForSubcycle_3_WhenOneTimeIsDiferrentThanZero( uint time_1, uint time_2 );
    void runSingleShotForSubcycle_3_WhenAllTimesAreDiferrentThanZero(uint time_1, uint time_2, uint time_3 );
    void runSingleShotForSubcycle_3_WhenAllTimesAreEqualZero( uint time );

private slots:
    void firstSubcycle();
    void secondSubcycle();
    void thirdSubcycle();
    void holdFirstSubcycle();
    void holdSecondSubcycle();
    void holdThirdSubcycle();
};

#endif // SIMPLEJUNCTION_H
