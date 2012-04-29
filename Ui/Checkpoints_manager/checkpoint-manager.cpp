#include "checkpoint-manager.h"
#include "cstdlib"
#include "time.h"
#include "../Logger/logger.h"
#include "checkpoint-creator.h"

CheckpointManager::CheckpointManager():
    QObject( NULL )
{
    srand( time( NULL ) );

    CheckpointCreator checkpointCreator( "Checkpoints_positions.pos", this ); // It creates checkpoints from file and save all in vector.

    Q_UNUSED( checkpointCreator );
}

CheckpointManager::~CheckpointManager()
{
    qDeleteAll( m_checkpointVector );
}

Checkpoint* CheckpointManager::addCheckpoint( qreal x, qreal y, uint id, uint flags )
{
    Checkpoint *checkpoint = new Checkpoint( x, y );
    checkpoint->setId( id );
    checkpoint->setFlags( flags );

    m_checkpointVector << checkpoint;

    LOG_INFO( "Added new checkpoint with %i id", id );

    connect( checkpoint, SIGNAL(checkpointReached(uint,int,Vehicle*)), this, SIGNAL(checkpointReached(uint,int,Vehicle*)) );

    return checkpoint;
}

const Checkpoint* CheckpointManager::checkpointByIdConst( uint id ) const
{
    Q_ASSERT( int( id ) < m_checkpointVector.count() );

    return m_checkpointVector.at( id );
}

Checkpoint* CheckpointManager::checkpointById( uint id ) const
{
    Q_ASSERT( int( id ) < m_checkpointVector.count() );

    return m_checkpointVector.at( id );
}


uint CheckpointManager::checkpointsCount() const
{
    return m_checkpointVector.count();
}
