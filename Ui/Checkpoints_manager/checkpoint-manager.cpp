#include "checkpoint-manager.h"
#include "cstdlib"
#include "time.h"
#include "../Logger/logger.h"

CheckpointManager::CheckpointManager()
{
    srand( time( NULL ) );
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

void CheckpointManager::addCheckpoint( qreal x, qreal y )
{
    static unsigned id = 0;

    Checkpoint *checkpoint = new Checkpoint( x, y );
    checkpoint->setId( id++ );

    m_checkpointVector << checkpoint;

    LOG_INFO( "Added new checkpoint with %i id", id - 1 );
}

const Checkpoint* CheckpointManager::checkpointById( unsigned int id ) const
{
    Q_ASSERT( id < m_checkpointVector.count() );

    return m_checkpointVector.at( id );
}
