#ifndef VEHICLE_H
#define VEHICLE_H

#include <QGraphicsWidget>

class Vehicle: public QGraphicsWidget
{
public:
    explicit Vehicle( QGraphicsItem *parent = 0 );
};

#endif // VEHICLE_H
