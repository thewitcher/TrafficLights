#include "parallel-move.h"

ParallelMove::ParallelMove( Vehicle *vehicle, QObject *parent ):
    QParallelAnimationGroup( parent ),
    SimpleMove( vehicle )
{
}

void ParallelMove::updateCurrentTime( int currentTime )
{
    collisionDetection();

    QParallelAnimationGroup::updateCurrentTime( currentTime );
}
