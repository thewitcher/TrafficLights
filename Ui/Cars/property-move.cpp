#include "property-move.h"
#include "vehicle.h"

PropertyMove::PropertyMove( Vehicle *target, const QByteArray &propertyName, QObject *parent ):
    QPropertyAnimation( target, propertyName, parent ),
    SimpleMove( target )
{
}

void PropertyMove::updateCurrentTime( int currentTime )
{
    collisionDetection();

    QPropertyAnimation::updateCurrentTime( currentTime );
}
