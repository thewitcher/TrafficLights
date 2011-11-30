#include "vehicle.h"
#include "../Checkpoints_manager/checkpoint.h"
#include "../Checkpoints_manager/path.h"

Vehicle::Vehicle( QGraphicsItem *parent ):
    QGraphicsWidget( parent )
{
}

void Vehicle::init( const Checkpoint *initCheckpoint )
{
    const Path *path = initCheckpoint->randomPath();
    path->animation( this, this );
}
