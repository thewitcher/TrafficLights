#include "sequential-move.h"

SequentialMove::SequentialMove( Vehicle *target, QObject *parent ):
    QSequentialAnimationGroup( parent ),
    SimpleMove( target )
{
}

void SequentialMove::updateCurrentTime( int currentTime )
{
    collisionDetection();

    QSequentialAnimationGroup::updateCurrentTime( currentTime );
}
