#ifndef COLLISIONPOINT_H
#define COLLISIONPOINT_H

#include <QPointF>

class Vehicle;

/*!
 * This class allows to check point collisions with target. It is very fast way to find out if there is collision or not.
 */
class CollisionPoint: public QPointF
{
public:
    explicit CollisionPoint( qreal x, qreal y );
    /*!
     * Convert constructor.
     */
    CollisionPoint( QPointF point );

    QPointF toPointF();

    bool collideWithItem( const Vehicle* target );
};

#endif // COLLISIONPOINT_H
