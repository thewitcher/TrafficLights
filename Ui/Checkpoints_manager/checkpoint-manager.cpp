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

void CheckpointManager::createCheckpoints()
{
    Checkpoint* checkpoint = addCheckpoint( 400, 513 );
    checkpoint->addPath( NULL, 10000, "y", 400, 900 );

    Checkpoint* checkpoint1 = addCheckpoint( 35, 513 );
    checkpoint1->addPath( checkpoint, 10000, "x", 35, 400 );

    Checkpoint* checkpoint2 = addCheckpoint( 35, 35 );
    checkpoint2->addPath( checkpoint1, 10000, "y", 35, 513 );
}
