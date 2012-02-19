#include "collision-point.h"
#include "vehicle.h"

CollisionPoint::CollisionPoint( qreal x, qreal y ):
    QPointF( x, y )
{
}

CollisionPoint::CollisionPoint( QPointF point ):
    QPointF( point.x(), point.y() )
{
}

bool CollisionPoint::collideWithItem( const Vehicle *target )
{   
    QPoint topLeft = target->topLeftPoint();
    QPoint bottomRight = target->bottomRightPoint();

    if( ( topLeft.x() <= x() ) &&  ( x() <= bottomRight.x() )
            &&
        ( topLeft.y() <= y() ) &&  ( y() <= bottomRight.y() ) )
    {
        return true;
    }

    return false;
}

QPointF CollisionPoint::toPointF()
{
    return QPointF( x(), y() );
}
