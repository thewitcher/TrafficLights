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
    Checkpoint* checkpoint17 = addCheckpoint( 194, 26 );
    Checkpoint* checkpoint18 = addCheckpoint( 194, 58 );
    Checkpoint* checkpoint19 = addCheckpoint( 194, 390 );
    Checkpoint* checkpoint20 = addCheckpoint( 194, 422 );
    Checkpoint* checkpoint21 = addCheckpoint( 194, 454 );
    Checkpoint* checkpoint22 = addCheckpoint( 194, 506 );
    Checkpoint* checkpoint23 = addCheckpoint( 194, 570 );
    Checkpoint* checkpoint24 = addCheckpoint( 194, 960 );
    Checkpoint* checkpoint25 = addCheckpoint( 194, 992 );
    Checkpoint* checkpoint26 = addCheckpoint( 226, 26 );
    Checkpoint* checkpoint27 = addCheckpoint( 226, 58 );
    Checkpoint* checkpoint28 = addCheckpoint( 226, 390 );
    Checkpoint* checkpoint29 = addCheckpoint( 226, 570 );
    Checkpoint* checkpoint30 = addCheckpoint( 226, 960 );
    Checkpoint* checkpoint31 = addCheckpoint( 226, 1024 );
    Checkpoint* checkpoint32 = addCheckpoint( 258, 26 );
    Checkpoint* checkpoint33 = addCheckpoint( 258, 58 );
    Checkpoint* checkpoint34 = addCheckpoint( 258, 390 );
    Checkpoint* checkpoint35 = addCheckpoint( 258, 422 );
    Checkpoint* checkpoint36 = addCheckpoint( 310, 26 );
    Checkpoint* checkpoint37 = addCheckpoint( 310, 90 );
    Checkpoint* checkpoint38 = addCheckpoint( 310, 422 );
    Checkpoint* checkpoint39 = addCheckpoint( 278, 570 );
    Checkpoint* checkpoint40 = addCheckpoint( 278, 602 );
    Checkpoint* checkpoint41 = addCheckpoint( 310, 602 );
    Checkpoint* checkpoint42 = addCheckpoint( 278, 992 );
    Checkpoint* checkpoint43 = addCheckpoint( 278, 1024 );
    Checkpoint* checkpoint44 = addCheckpoint( 310, 1024 );
    Checkpoint* checkpoint45 = addCheckpoint( 310, 992 );
    Checkpoint* checkpoint46 = addCheckpoint( 342, 58 );
    Checkpoint* checkpoint47 = addCheckpoint( 342, 90 );
    Checkpoint* checkpoint48 = addCheckpoint( 342, 422 );
    Checkpoint* checkpoint49 = addCheckpoint( 342, 486 );
    Checkpoint* checkpoint50 = addCheckpoint( 342, 538 );
    Checkpoint* checkpoint51 = addCheckpoint( 342, 570 );
    Checkpoint* checkpoint52 = addCheckpoint( 342, 602 );
    Checkpoint* checkpoint53 = addCheckpoint( 342, 992 );
    Checkpoint* checkpoint54 = addCheckpoint( 342, 1024 );
    Checkpoint* checkpoint55 = addCheckpoint( 720, 1024 );
    Checkpoint* checkpoint56 = addCheckpoint( 688, 992 );
    Checkpoint* checkpoint57 = addCheckpoint( 688, 960 );
    Checkpoint* checkpoint58 = addCheckpoint( 720, 960 );
    Checkpoint* checkpoint59 = addCheckpoint( 688, 58 );
    Checkpoint* checkpoint60 = addCheckpoint( 720, 58 );
    Checkpoint* checkpoint61 = addCheckpoint( 688, 26 );
    Checkpoint* checkpoint62 = addCheckpoint( 720, 26 );
    Checkpoint* checkpoint63 = addCheckpoint( 804, 26 );
    Checkpoint* checkpoint64 = addCheckpoint( 836, 58 );
    Checkpoint* checkpoint65 = addCheckpoint( 804, 90 );
    Checkpoint* checkpoint66 = addCheckpoint( 836, 90 );
    Checkpoint* checkpoint67 = addCheckpoint( 804, 992 );
    Checkpoint* checkpoint68 = addCheckpoint( 804, 1024 );
    Checkpoint* checkpoint69 = addCheckpoint( 836, 1024 );
    Checkpoint* checkpoint70 = addCheckpoint( 836, 992 );
    Checkpoint* checkpoint71 = addCheckpoint( 1280, 1024 );
    Checkpoint* checkpoint72 = addCheckpoint( 1248, 992 );
    Checkpoint* checkpoint73 = addCheckpoint( 1280, 538 );
    Checkpoint* checkpoint74 = addCheckpoint( 1248, 570 );
    Checkpoint* checkpoint75 = addCheckpoint( 1216, 538 );
    Checkpoint* checkpoint76 = addCheckpoint( 1216, 570 );
    Checkpoint* checkpoint77 = addCheckpoint( 1280, 454 );
    Checkpoint* checkpoint78 = addCheckpoint( 1248, 454 );
    Checkpoint* checkpoint79 = addCheckpoint( 1248, 422 );
    Checkpoint* checkpoint80 = addCheckpoint( 1280, 422 );
    Checkpoint* checkpoint81 = addCheckpoint( 1248, 58 );
    Checkpoint* checkpoint82 = addCheckpoint( 1280, 26 );
    Checkpoint* checkpoint83 = addCheckpoint( 374, 422 );
    Checkpoint* checkpoint84 = addCheckpoint( 374, 454 );
    Checkpoint* checkpoint85 = addCheckpoint( 374, 486 );

//    // Adds paths to checkpoint0
    checkpoint0->addTurnAndMovingByXYToTargetCheckpointPath( checkpoint8, 5000, 10000, Checkpoint::TURN_LEFT );

//    // Adds paths to checkpoint1
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint2
//    checkpoint2->addPath( checkpoint14, 10000, Checkpoint::TURN_LEFT, "x", 26, 162 );

//    // Adds paths to checkpoint3
//    checkpoint3->addPath( checkpoint15, 10000, Checkpoint::TURN_LEFT, "x", 26, 162 );

//    // Adds paths to checkpoint4
//    checkpoint4->addPath( checkpoint16, 10000, Checkpoint::TURN_LEFT, "x", 26, 162 );

//    // Adds paths to checkpoint5
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint6
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint7
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint8
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint9
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint10
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint11
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint12
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint13
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint14
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint15
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint16
//    checkpoint16->addPath( checkpoint22, 10000, Checkpoint::AHEAD, "x", 162, 194 );

//    // Adds paths to checkpoint17
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint18
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint19
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint20
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint21
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint22
//    //checkpoint22->addPath( checkpoint38, 10000, "y", 26, 506, Checkpoint::AHEAD );
//    //checkpoint22->addPath( checkpoint48, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint23
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint24
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint25
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint26
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint27
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint28
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint29
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint30
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint31
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint32
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint33
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint34
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint35
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint36
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint37
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint38
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint39
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint40
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint41
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint42
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint43
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint44
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint45
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint46
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint47
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint48
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint49
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint50
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint51
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint52
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint53
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint54
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint55
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );

//    // Adds paths to checkpoint56
//    //checkpoint0->addPath( checkpoint1, 10000, "y", 26, 506, Checkpoint::AHEAD );
}
