#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <QDeclarativeItem>

class TrafficLight : public QDeclarativeItem
{
    Q_OBJECT

public:
    explicit TrafficLight( QDeclarativeItem *parent = 0 );
    enum Direction { STRAIGHT, LEFT, RIGHT, STRAIGHT_AND_LEFT, STRAIGHT_AND_RIGHT };

    void setDirection( TrafficLight* light, const Direction& direct );
    void changeState();

private slots:
    void letGoVehicles();
    void holdVehicles();

};

#endif // TRAFFICLIGHT_H