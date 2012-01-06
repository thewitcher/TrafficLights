#include "parallel-move.h"

ParallelMove::ParallelMove( Vehicle *target, QObject *parent ):
    QParallelAnimationGroup( parent ),
    SimpleMove( target )
{
}

void ParallelMove::updateCurrentTime( int currentTime )
{
    collisionDetection();

    QParallelAnimationGroup::updateCurrentTime( currentTime );
}
