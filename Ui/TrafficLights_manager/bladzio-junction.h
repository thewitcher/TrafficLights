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

    void setTimeVectorByGeneticAlgorithm();
    void runFirstSubcycle( uint subcycle_1 );
    void runSecondSubcycle( uint subcycle_1, uint subcycle_2 );
    void runThirdSubcycle( uint subcycle_1, uint subcycle_2, uint subcycle_3 );
    void runFourthSubcycle( uint subcycle_1, uint subcycle_2, uint subcycle_3, uint subcycle_4 );
    void exceptionWhenSubcycleSumEqualZero( uint subcycle_1, uint subcycle_2, uint subcycle_3, uint subcycle_4 );

    void runSingleShotForSubcycle_1_WhenTimeIsDiferrentThanZero( uint time );

    void runSingleShotForSubcycle_2_WhenTimeIsDiferrentThanZero( uint time_1, uint time_2 );
    void runSingleShotForSubcycle_2_WhenTimeAreEqualZero( uint time );

    void runSingleShotForSubcycle_3_WhenOneTimeIsDiferrentThanZero( uint time_1, uint time_2 );
    void runSingleShotForSubcycle_3_WhenAllTimesAreDiferrentThanZero( uint time_1, uint time_2, uint time_3 );
    void runSingleShotForSubcycle_3_WhenAllTimesAreEqualZero( uint time_3 );

    void runSingleShotForSubcycle_4_WhenOneTimeIsDiferrentThanZero( uint time_1, uint time_2 );
    void runSingleShotForSubcycle_4_WhenTwoTimesAreDiferrentThanZero( uint time_1, uint time_2, uint time_3 );
    void runSingleShotForSubcycle_4_WhenAllTimesAreDiferrentThanZero( uint time_1, uint time_2, uint time_3, uint time_4 );
    void runSingleShotForSubcycle_4_WhenAllTimesAreEqualZero( uint time );

private slots:

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
