#ifndef BLADZIOJUNCTION_H
#define BLADZIOJUNCTION_H

#include "junction.h"

class BladzioJunction: public Junction
{

    Q_OBJECT

public:
    BladzioJunction( const QVector<TrafficLight*>& junction, QLCDNumber* vehicleCounter );
    ~BladzioJunction();

protected:
    void run();

private:
    TrafficLight* leftLight2a;
    TrafficLight* straightLight2a;
    TrafficLight* rightLight2a;
    TrafficLight* leftLight2b;
    TrafficLight* straightLight2b;
    TrafficLight* rightLight2b;
    TrafficLight* leftLight2c;
    TrafficLight* straightLight2c;
    TrafficLight* rightLight2c;
    TrafficLight* leftLight2d;
    TrafficLight* straightLight2d;
    TrafficLight* rightLight2d;
    uint t1v,t2v,t3v,t1h,t2h,t3h;

private slots:
    void firstVertivalSeries();
    void secondVerticalSeries();

    void holdFirstVerticalSeries();
    void holdPartialSecondVerticalSeries();
    void holdAllSecondVerticalSeries();

    void firstHorizontalSeries();
    void secondHorizontalSeries();

    void holdFirstHorizontalSeries();
    void holdSecondHorizontalSeries();

};

#endif // BLADZIOJUNCTION_H
