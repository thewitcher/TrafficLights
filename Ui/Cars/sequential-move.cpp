#include "sequential-move.h"

SequentialMove::SequentialMove( QObject *parent ):
    QSequentialAnimationGroup( parent )
{
}

void SequentialMove::updateCurrentTime( int currentTime )
{
    doItWhileMoving();

    QSequentialAnimationGroup::updateCurrentTime( currentTime );
}
