#include "checkpoint-manager.h"
#include "cstdlib"
#include "time.h"
#include "../Logger/logger.h"

CheckpointManager::CheckpointManager()
{
    srand( time( NULL ) );

    createCheckpoints();
}

CheckpointManager::~CheckpointManager()
{
    qDeleteAll( m_checkpointVector );
}

CheckpointManager& CheckpointManager::checkpointManagerInstance()
{
    static CheckpointManager m_checkpointManager;

    return m_checkpointManager;
}

Checkpoint* CheckpointManager::addCheckpoint( qreal x, qreal y )
{
    static unsigned id = 0;

    Checkpoint *checkpoint = new Checkpoint( x, y );
    checkpoint->setId( id++ );

    m_checkpointVector << checkpoint;

    LOG_INFO( "Added new checkpoint with %i id", id - 1 );

    return checkpoint;
}

const Checkpoint* CheckpointManager::checkpointById( unsigned int id ) const
{
    Q_ASSERT( int( id ) < m_checkpointVector.count() );

    return m_checkpointVector.at( id );
}

/*!
 For current vehicles with size You shoudl subtract 9 from x and 9 from y (it depends on vehicles size)
 */
void CheckpointManager::createCheckpoints()
{
    Checkpoint* checkpoint = addCheckpoint( 400, 506 );
    checkpoint->addPath( NULL, 10000, "y", 400, 900, Checkpoint::AHEAD );

    Checkpoint* checkpoint1 = addCheckpoint( 26, 506 );
    checkpoint1->addPath( checkpoint, 10000, "x", 26, 400, Checkpoint::TURN_LEFT );
    checkpoint1->addPath( checkpoint, 10000, "y", 506, 1029, Checkpoint::AHEAD );

    Checkpoint* checkpoint2 = addCheckpoint( 26, 26 );
    checkpoint2->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );
}
