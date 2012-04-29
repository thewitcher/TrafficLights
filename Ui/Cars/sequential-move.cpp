#include "sequential-move.h"

SequentialMove::SequentialMove( Vehicle *target, QObject *parent ):
    QSequentialAnimationGroup( parent ),
    SimpleMove( target )
{
}

void SequentialMove::updateCurrentTime( int currentTime )
{
#ifdef COLLISIONS
    collisionDetection();
#endif
    QSequentialAnimationGroup::updateCurrentTime( currentTime );
}
