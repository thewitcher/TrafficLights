#include "parallel-move.h"

ParallelMove::ParallelMove( QObject *parent ):
    QParallelAnimationGroup( parent )
{
}

void ParallelMove::updateCurrentTime( int currentTime )
{
    doItWhileMoving();

    QParallelAnimationGroup::updateCurrentTime( currentTime );
}
