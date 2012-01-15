#ifndef COLLISIONPOINT_H
#define COLLISIONPOINT_H

#include <QPointF>

class Vehicle;

/*!
 * @file collision-point.h
 *
 * @brief QPointF subclass which adding check collision feature.
 *
 * @author Marcin Haber
 *
 * This class allows to check collisions between point and target. If the point is located on the target area (it checks x,y,width and heigh of target)
 * then collideWithItem return true. Otherwise return false. This is simple subclass of QPointF wit converting constructor. The main fetures is that
 * You can check collision wtih vehicle. Object of this type is used by us like a car bumper. We can test if two car are in collision, becouse we can test
 * collision between one's vehicle bumper and shape other vehicle.
 */
class CollisionPoint: public QPointF
{
public:
    /*!
     * Standard constructor. Create simple CollisionPoint with x and y coordinates.
     *
     * @param x X coordinate
     * @param y Y coordinate
     *
     */
    explicit CollisionPoint( qreal x, qreal y );
    /*!
     * Convert constructor. Converting QPointF to Collision point.
     *
     * @param point Point to convert into CollisionPoint.
     */
    CollisionPoint( QPointF point );

    /*!
     * Converts CollisionPoint to normal QPointF.
     */
    QPointF toPointF();

    /*!
     * Returns true if collision point is locatet on target area. Otherwise returns false.
     *
     * @param target Vehicle we check collision with.
     * @return bool Is collision point located in target area or not.
     */
    bool collideWithItem( const Vehicle* target );
};

#endif // COLLISIONPOINT_H
