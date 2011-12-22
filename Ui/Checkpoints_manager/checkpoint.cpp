#include "checkpoint.h"
#include "../../Logger/logger.h"
#include "path.h"
#include <cstdlib>
#include <QVector>

Checkpoint::Checkpoint(qreal x, qreal y):
    m_x( x ),
    m_y( y ),
    m_id( 0 )
{
}

Checkpoint::~Checkpoint()
{
    qDeleteAll( m_paths );
}

unsigned char Checkpoint::randomNumber( unsigned char max ) const
{
    unsigned char random = ( rand() % ( max + 1 ) );

    LOG_INFO( "Random number: %i(%i) ,from: %s", random, max, __FUNCTION__ );

    return random;
}

const Path* Checkpoint::randomPath() const
{
    LOG_INFO( "Random path was returned for checkpoint with %i id", m_id );

    if( m_paths.isEmpty() == true )
    {
        LOG_WARNING( "m_path is empty: %s", __FUNCTION__ );

        return NULL;
    }

    return m_paths.at( randomNumber( m_paths.count() - 1 ) );
}

void Checkpoint::setId( unsigned char id )
{
    m_id = id;
}

void Checkpoint::addMovingByXToTargetCheckpointPath( Checkpoint *targetCheckpoint, int duration, QEasingCurve::Type easingCurve )
{
    if( targetCheckpoint != NULL )
    {
        m_paths << new Path( targetCheckpoint, duration, "x", easingCurve );
    }
    else
    {
        LOG_WARNING( "Target checkpoint is NULL: %s", __FUNCTION__ );
    }
}

void Checkpoint::addMovingByYToTargetCheckpointPath( Checkpoint *targetCheckpoint, int duration, QEasingCurve::Type easingCurve )
{
    if( targetCheckpoint != NULL )
    {
        m_paths << new Path( targetCheckpoint, duration, "y", easingCurve );
    }
    else
    {
        LOG_WARNING( "Target checkpoint is NULL: %s", __FUNCTION__ );
    }
}

void Checkpoint::addMovingByXYToTargetCheckpointPath( Checkpoint *targetCheckpoint, int duration,
                                                      QEasingCurve::Type easingCurveX, QEasingCurve::Type easingCurveY )
{
    if( targetCheckpoint != NULL )
    {
        m_paths << new Path( targetCheckpoint, duration, easingCurveX, easingCurveY );
    }
    else
    {
        LOG_WARNING( "Target checkpoint is NULL: %s", __FUNCTION__ );
    }
}

void Checkpoint::addTurnAndMovingByXToTargetCheckpointPath( Checkpoint *targetCheckpoint, int turnDuration, int moveDuration, const TurnType turnType,
                                                            QEasingCurve::Type easingCurveX, bool sequential )
{
    if( targetCheckpoint != NULL )
    {
        m_paths << new Path( targetCheckpoint, turnDuration, moveDuration, "x", turnType, easingCurveX, sequential );
    }
    else
    {
        LOG_WARNING( "Target checkpoint is NULL: %s", __FUNCTION__ );
    }
}

void Checkpoint::addTurnAndMovingByXYToTargetCheckpointPath( Checkpoint *targetCheckpoint, int turnDuration, int moveDuration, const TurnType turnType,
                                                             QEasingCurve::Type easingCurveX, QEasingCurve::Type easingCurveY, bool sequential )
{
    if( targetCheckpoint != NULL )
    {
        m_paths << new Path( targetCheckpoint, turnDuration, moveDuration, turnType, easingCurveX, easingCurveY, sequential );
    }
    else
    {
        LOG_WARNING( "Target checkpoint is NULL: %s", __FUNCTION__ );
    }
}

void Checkpoint::addTurnAndMovingByYToTargetCheckpointPath( Checkpoint *targetCheckpoint, int turnDuration, int moveDuration,
                                                            const TurnType turnType, QEasingCurve::Type easingCurveY, bool sequential )
{
    if( targetCheckpoint != NULL )
    {
        m_paths << new Path( targetCheckpoint, turnDuration, moveDuration, "y", turnType, easingCurveY, sequential );
    }
    else
    {
        LOG_WARNING( "Target checkpoint is NULL: %s", __FUNCTION__ );
    }
}

void Checkpoint::addMove( QVector<Checkpoint *> checkpointsVector, const QString &parameters )
{
    LOG_INFO( "Try to add move path with parameters: %s to checkpoint with id: %i", parameters.toLatin1().data(), m_id );

    if( parameters == "ay" ) // Ahead with y
    {
        for( int i = 0 ; i < checkpointsVector.count() ; i++ )
        {
            addMovingByYToTargetCheckpointPath( checkpointsVector.at( i ), 10000 );
        }
    }
    else if( parameters == "ax" ) // Ahead with x
    {
        for( int i = 0 ; i < checkpointsVector.count() ; i++ )
        {
            addMovingByXToTargetCheckpointPath( checkpointsVector.at( i ), 10000 );
        }
    }
    else if( parameters == "lx" ) // Left with x
    {
        for( int i = 0 ; i < checkpointsVector.count() ; i++ )
        {
            addTurnAndMovingByXToTargetCheckpointPath( checkpointsVector.at( i ), 1000, 10000, TURN_90_LEFT );
        }
    }
    else if( parameters == "ly" ) // Left with y
    {
        for( int i = 0 ; i < checkpointsVector.count() ; i++ )
        {
            addTurnAndMovingByYToTargetCheckpointPath( checkpointsVector.at( i ), 1000, 10000, TURN_90_LEFT );
        }
    }
    else if( parameters == "rx" ) // Right with x
    {
        for( int i = 0 ; i < checkpointsVector.count() ; i++ )
        {
            addTurnAndMovingByXToTargetCheckpointPath( checkpointsVector.at( i ), 1000, 10000, TURN_90_RIGHT );
        }
    }
    else if( parameters == "ry" ) // Right with y
    {
        for( int i = 0 ; i < checkpointsVector.count() ; i++ )
        {
            addTurnAndMovingByYToTargetCheckpointPath( checkpointsVector.at( i ), 1000, 10000, TURN_90_RIGHT );
        }
    }
    else if( parameters == "vxy" ) // Right with x and y
    {
        for( int i = 0 ; i < checkpointsVector.count() ; i++ )
        {
            addTurnAndMovingByXYToTargetCheckpointPath( checkpointsVector.at( i ), 10000, 10000, TURN_90_RIGHT, QEasingCurve::Linear, QEasingCurve::OutQuad, false );
        }
    }
    else if( parameters == "hxy" ) // Left with x and y
    {
        for( int i = 0 ; i < checkpointsVector.count() ; i++ )
        {
            addTurnAndMovingByXYToTargetCheckpointPath( checkpointsVector.at( i ), 10000, 10000, TURN_90_LEFT, QEasingCurve::OutQuad, QEasingCurve::Linear, false );
        }
    }
    else
    {
        LOG_WARNING( "Parameter is unknown: %s", __FUNCTION__ );
    }
}

qreal Checkpoint::posX() const
{
    return m_x;
}

qreal Checkpoint::posY() const
{
    return m_y;
}
