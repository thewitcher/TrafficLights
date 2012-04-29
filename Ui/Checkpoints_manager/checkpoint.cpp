#include "checkpoint.h"
#include "../../Logger/logger.h"
#include "path.h"
#include <cstdlib>
#include <math.h>
#include <QVector>

Checkpoint::Checkpoint(qreal x, qreal y):
    QObject( NULL ),
    m_x( x ),
    m_y( y ),
    m_id( 0 ),
    m_movePermission( true ),
    m_flags( 0 )
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

int Checkpoint::id() const
{
    return m_id;
}

QList<Path*> Checkpoint::allPaths() const
{
    return m_paths;
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

void Checkpoint::setMovePermission( bool permission )
{
    m_movePermission = permission;
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

    int duration = 10000;

    if( parameters == "ya" ) // Ahead with y
    {  
        for( int i = 0 ; i < checkpointsVector.count() ; i++ )
        {
            duration = estimatedMovingTimeToTargetCheckpoint( checkpointsVector.at( i ) );

            addMovingByYToTargetCheckpointPath( checkpointsVector.at( i ), duration );
        }
    }
    else if( parameters == "xa" ) // Ahead with x
    {
        for( int i = 0 ; i < checkpointsVector.count() ; i++ )
        {
            duration = estimatedMovingTimeToTargetCheckpoint( checkpointsVector.at( i ) );

            addMovingByXToTargetCheckpointPath( checkpointsVector.at( i ), duration );
        }
    }
    else if( parameters == "xl" ) // Left with x
    {
        for( int i = 0 ; i < checkpointsVector.count() ; i++ )
        {
            duration = estimatedMovingTimeToTargetCheckpoint( checkpointsVector.at( i ) );

            addTurnAndMovingByXToTargetCheckpointPath( checkpointsVector.at( i ), 300, duration, TURN_90_LEFT );
        }
    }
    else if( parameters == "yl" ) // Left with y
    {
        for( int i = 0 ; i < checkpointsVector.count() ; i++ )
        {
            duration = estimatedMovingTimeToTargetCheckpoint( checkpointsVector.at( i ) );

            addTurnAndMovingByYToTargetCheckpointPath( checkpointsVector.at( i ), 300, duration, TURN_90_LEFT );
        }
    }
    else if( parameters == "xr" ) // Right with x
    {
        for( int i = 0 ; i < checkpointsVector.count() ; i++ )
        {
            duration = estimatedMovingTimeToTargetCheckpoint( checkpointsVector.at( i ) );

            addTurnAndMovingByXToTargetCheckpointPath( checkpointsVector.at( i ), 300, duration, TURN_90_RIGHT );
        }
    }
    else if( parameters == "yr" ) // Right with y
    {
        for( int i = 0 ; i < checkpointsVector.count() ; i++ )
        {
            duration = estimatedMovingTimeToTargetCheckpoint( checkpointsVector.at( i ) );

            addTurnAndMovingByYToTargetCheckpointPath( checkpointsVector.at( i ), 300, duration, TURN_90_RIGHT );
        }
    }
    else if( parameters == "wxy" ) // West with x and y
    {
        for( int i = 0 ; i < checkpointsVector.count() ; i++ )
        {
            duration = estimatedMovingTimeToTargetCheckpoint( checkpointsVector.at( i ) );

            addTurnAndMovingByXYToTargetCheckpointPath( checkpointsVector.at( i ), duration, duration, TURN_90_LEFT,
                                                        QEasingCurve::OutCirc, QEasingCurve::OutCirc,
                                                        false );
        }
    }
    else if( parameters == "exy" ) // East with x and y
    {     
        for( int i = 0 ; i < checkpointsVector.count() ; i++ )
        {
            duration = estimatedMovingTimeToTargetCheckpoint( checkpointsVector.at( i ) );

            addTurnAndMovingByXYToTargetCheckpointPath( checkpointsVector.at( i ), duration, duration, TURN_90_LEFT,
                                                        QEasingCurve::OutCirc, QEasingCurve::OutCirc,
                                                        false );
        }
    }
    else if( parameters == "nxy" ) // North with x and y
    {
        for( int i = 0 ; i < checkpointsVector.count() ; i++ )
        {
            duration = estimatedMovingTimeToTargetCheckpoint( checkpointsVector.at( i ) );

            addTurnAndMovingByXYToTargetCheckpointPath( checkpointsVector.at( i ), duration, duration, TURN_90_LEFT,
                                                        QEasingCurve::InCirc, QEasingCurve::InCirc,
                                                        false );
        }
    }
    else if( parameters == "sxy" ) // South with x and y
    {
        for( int i = 0 ; i < checkpointsVector.count() ; i++ )
        {
            duration = estimatedMovingTimeToTargetCheckpoint( checkpointsVector.at( i ) );

            addTurnAndMovingByXYToTargetCheckpointPath( checkpointsVector.at( i ), duration, duration, TURN_90_LEFT,
                                                        QEasingCurve::InCirc, QEasingCurve::InCirc,
                                                        false );
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

int Checkpoint::estimatedMovingTimeToTargetCheckpoint( const Checkpoint *targetCheckpoint ) const
{
    LOG_INFO( "Start %s", __FUNCTION__ );

    int distance = sqrt( pow( posX() - targetCheckpoint->posX(), 2) + pow( posY() - targetCheckpoint->posY(), 2) );
    int time = 10 * distance;

    LOG_INFO( "Distance between: (%f,%f) and (%f,%f) = %i", posX(), posY(), targetCheckpoint->posX(), targetCheckpoint->posY(), distance );
    LOG_INFO( "Estimated moving time: %i", time );

    return time;
}

bool Checkpoint::movePermission() const
{
    return m_movePermission;
}

void Checkpoint::reached( Vehicle* vehicle )
{
    LOG_INFO( "Checkpoint with id: %i was reached", m_id );

    if( m_flags & 1 )
    {
        emit checkpointReached( m_flags, m_id, vehicle );
    }
}

void Checkpoint::setFlags( uint flags )
{
    m_flags = flags;
}
