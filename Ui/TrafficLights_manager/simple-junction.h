#ifndef SIMPLEJUNCTION_H
#define SIMPLEJUNCTION_H

#include "junction.h"

class SimpleJunction: public Junction
{

    Q_OBJECT

public:
    SimpleJunction( const QVector<TrafficLight*>& junction );
    ~SimpleJunction();

protected:
    void run();

private:
    TrafficLight* leftLight;
    TrafficLight* rightLight;
    TrafficLight* leftAndStraightLight;
    TrafficLight* rightAndStraightLight;
    unsigned int m_leftTime, m_leftAndStraightTime;

public slots:
    void firstSeries();
    void secondSeries();
    void thirdSeries();
    void fourthSeries();
    void holdLightsFromFirstSeries();
    void holdLightsFromSecondSeries();
};

#endif // SIMPLEJUNCTION_H
