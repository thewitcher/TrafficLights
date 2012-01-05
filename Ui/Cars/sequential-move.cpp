#include "sequential-move.h"

SequentialMove::SequentialMove( Vehicle *vehicle, QObject *parent ):
    QSequentialAnimationGroup( parent ),
    SimpleMove( vehicle )
{
}

void SequentialMove::updateCurrentTime( int currentTime )
{
    collisionDetection();

    QSequentialAnimationGroup::updateCurrentTime( currentTime );
}
