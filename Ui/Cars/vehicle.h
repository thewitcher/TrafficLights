#ifndef VEHICLE_H
#define VEHICLE_H

#include <QGraphicsWidget>

class Checkpoint;

class Vehicle: public QGraphicsWidget
{

    Q_OBJECT

public:
    explicit Vehicle( QGraphicsItem *parent = 0 );

    void init( const Checkpoint* initCheckpoint );
};

#endif // VEHICLE_H
