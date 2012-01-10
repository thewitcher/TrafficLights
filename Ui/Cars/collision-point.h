#ifndef COLLISIONPOINT_H
#define COLLISIONPOINT_H

#include <QPointF>

class Vehicle;

class CollisionPoint: public QPointF
{
public:
    explicit CollisionPoint( qreal x, qreal y );
    CollisionPoint( QPointF point );

    QPointF toPointF();

    bool collideWithItem( const Vehicle* target );
};

#endif // COLLISIONPOINT_H
