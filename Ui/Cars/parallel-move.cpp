#include "parallel-move.h"

ParallelMove::ParallelMove( Vehicle *target, QObject *parent ):
    QParallelAnimationGroup( parent ),
    SimpleMove( target )
{
}

void ParallelMove::updateCurrentTime( int currentTime )
{
#ifdef COLLISIONS
    collisionDetection();
#endif

    QParallelAnimationGroup::updateCurrentTime( currentTime );
}
