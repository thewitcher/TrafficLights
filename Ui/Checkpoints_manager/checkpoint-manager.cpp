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
    Checkpoint* checkpoint0 = addCheckpoint( 26, 26 );
    Checkpoint* checkpoint1 = addCheckpoint( 26, 506 );
    Checkpoint* checkpoint2 = addCheckpoint( 26, 454 );
    Checkpoint* checkpoint3 = addCheckpoint( 26, 538 );
    Checkpoint* checkpoint4 = addCheckpoint( 26, 570 );
    Checkpoint* checkpoint5 = addCheckpoint( 26, 1024 );

    Checkpoint* checkpoint6 = addCheckpoint( 58, 58 );
    Checkpoint* checkpoint7 = addCheckpoint( 58, 422 );
    Checkpoint* checkpoint8 = addCheckpoint( 58, 506 );
    Checkpoint* checkpoint9 = addCheckpoint( 58, 538 );
    Checkpoint* checkpoint10 = addCheckpoint( 58, 570 );
    Checkpoint* checkpoint11 = addCheckpoint( 58, 992 );

    Checkpoint* checkpoint12 = addCheckpoint( 90, 422 );
    Checkpoint* checkpoint13 = addCheckpoint( 90, 454 );

    Checkpoint* checkpoint14 = addCheckpoint( 162, 506 );
    Checkpoint* checkpoint15 = addCheckpoint( 162, 538 );
    Checkpoint* checkpoint16 = addCheckpoint( 162, 570 );

    // Adds paths to checkpoint0
    checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );
    checkpoint0->addPath( checkpoint3, 10000, "y", 26, 538, Checkpoint::AHEAD );
    checkpoint0->addPath( checkpoint4, 10000, "y", 26, 570, Checkpoint::AHEAD );
    checkpoint0->addPath( checkpoint5, 10000, "y", 26, 1024, Checkpoint::AHEAD );

    // Adds paths to checkpoint1
    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

    // Adds paths to checkpoint2
    checkpoint2->addPath( checkpoint14, 10000, "x", 26, 162, Checkpoint::TURN_LEFT );

    // Adds paths to checkpoint3
    checkpoint3->addPath( checkpoint15, 10000, "x", 26, 162, Checkpoint::TURN_LEFT );

    // Adds paths to checkpoint4
    checkpoint4->addPath( checkpoint16, 10000, "x", 26, 162, Checkpoint::TURN_LEFT );

    // Adds paths to checkpoint5
    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );
}
