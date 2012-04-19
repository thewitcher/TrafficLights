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

    void setTimeVectorByGeneticAlgorithm();
    void runSubcycle_1( uint subcycle_1 );
    void runSubcycle_2( uint subcycle_1, uint subcycle_2 );
    void runSubcycle_3( uint subcycle_1, uint subcycle_2, uint subcycle_3 );
    void exceptionWhenSubcycleSumEqualZero( uint subcycle_1, uint subcycle_2, uint subcycle_3 );

private slots:
    void firstSubcycle();
    void secondSubcycle();
    void thirdSubcycle();
    void holdFirstSubcycle();
    void holdSecondSubcycle();
    void holdThirdSubcycle();
};

#endif // SIMPLEJUNCTION_H
