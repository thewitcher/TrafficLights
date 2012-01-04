#include "property-move.h"

PropertyMove::PropertyMove( QObject *target, const QByteArray &propertyName, QObject *parent ):
    QPropertyAnimation( target, propertyName, parent ),
    SimpleMove( NULL )
{
}

void PropertyMove::updateCurrentTime( int currentTime )
{
    doItWhileMoving();

    QPropertyAnimation::updateCurrentTime( currentTime );
}
