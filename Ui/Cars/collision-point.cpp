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
    if( ( target->x() <= x() ) &&  ( x() <= target->x() + target->width() ) )
    {
        if( ( target->y() <= y() ) &&  ( y() <= target->y() + target->height() ) )
        {
            return true;
        }
    }

    return false;
}

QPointF CollisionPoint::toPointF()
{
    return QPointF( x(), y() );
}
