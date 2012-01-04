#include "checkpoint-manager.h"
#include "cstdlib"
#include "time.h"
#include "../Logger/logger.h"
#include "checkpoint-creator.h"

CheckpointManager::CheckpointManager()
{
    srand( time( NULL ) );

    CheckpointCreator checkpointCreator( "Checkpoints_positions.pos", this ); // It creates checkpoints from file and save all in vector.

    Q_UNUSED( checkpointCreator );
}

CheckpointManager::~CheckpointManager()
{
    qDeleteAll( m_checkpointVector );
}

Checkpoint* CheckpointManager::addCheckpoint( qreal x, qreal y, unsigned int id )
{
    Checkpoint *checkpoint = new Checkpoint( x, y );
    checkpoint->setId( id );

    m_checkpointVector << checkpoint;

    LOG_INFO( "Added new checkpoint with %i id", id );

    return checkpoint;
}

const Checkpoint* CheckpointManager::checkpointByIdConst( unsigned int id ) const
{
    Q_ASSERT( int( id ) < m_checkpointVector.count() );

    return m_checkpointVector.at( id );
}

Checkpoint* CheckpointManager::checkpointById( unsigned int id ) const
{
    Q_ASSERT( int( id ) < m_checkpointVector.count() );

    return m_checkpointVector.at( id );
}


unsigned int CheckpointManager::checkpointsCount() const
{
    return m_checkpointVector.count();
}
