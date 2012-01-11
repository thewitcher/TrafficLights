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
    if( ( target->x() <= x() )
            &&  ( x() <= target->x() + 20 )
            &&  ( target->y() <= y() )
            &&  ( y() <= target->y() + 20) )
    {
        return true;
    }

    return false;
}

QPointF CollisionPoint::toPointF()
{
    return QPointF( x(), y() );
}
