#include "vehicle.h"
#include "../Checkpoints_manager/checkpoint.h"
#include "../Checkpoints_manager/path.h"
#include "../../Logger/logger.h"
#include <QAbstractAnimation>
#include <QTimer>

const int Vehicle::WAIT_ON_PERMISSION = 1000;

Vehicle::Vehicle( QDeclarativeItem *parent ):
    QDeclarativeItem( parent ),
    m_currentPath( NULL ),
    m_speed( 1 ),
    m_currentCheckpoint( NULL ),
    m_currentAnimation( NULL ),
    m_first( true )
{
    /// Sets transformation point to center
    setTransformOriginPoint( 9, 9 );
}

Vehicle::~Vehicle()
{
}

QAbstractAnimation* Vehicle::currentAnimation()
{
    return m_currentAnimation;
}

void Vehicle::init( Checkpoint *initCheckpoint )
{
    Q_ASSERT( initCheckpoint != NULL );

    LOG_INFO( "Sets new speed to checkpoint: %i", m_speed );
    LOG_INFO( "Creates new path for checkpoint: (%f, %f) position", initCheckpoint->posX(), initCheckpoint->posY() );

    if( m_first )
    {
        m_currentCheckpoint = initCheckpoint;

        m_currentPath = m_currentCheckpoint->randomPath();

        m_currentAnimation = m_currentPath->animation( this, this, m_speed );

        m_first = false;
    }

    if( m_currentPath != NULL )
    {
        if( initCheckpoint->movePermission() == false )
        {
            QTimer::singleShot( WAIT_ON_PERMISSION, this, SLOT(init()) );

            LOG_INFO( "Permission denied. Wait time: %i", WAIT_ON_PERMISSION );

            return;
        }

        LOG_INFO( "Target of this animation is on pos: (%f, %f) position", m_currentPath->targetCheckpoint()->posX(),
                  m_currentPath->targetCheckpoint()->posY() );

        m_first = true;
    }
    else
    {
        LOG_WARNING( "m_currentPath is NULL: %s", __FUNCTION__ );
    }
}

void Vehicle::init()
{
    init( m_currentCheckpoint );
}

void Vehicle::resumeMove()
{
    if( m_currentAnimation != NULL )
    {
        if( m_currentAnimation->state() == QAbstractAnimation::Paused )
        {
            setBackLights( false );
            m_currentAnimation->resume();
        }
    }
}

void Vehicle::pauseMove()
{
    if( m_currentAnimation != NULL )
    {
        if( m_currentAnimation->state() == QAbstractAnimation::Running )
        {
            setBackLights( true );
            m_currentAnimation->pause();
        }
    }
}

void Vehicle::onAnimationFinish()
{
    LOG_INFO( "Animation is finished. Vehicle is in: (%f, %f) position", m_currentPath->targetCheckpoint()->posX(),
              m_currentPath->targetCheckpoint()->posY() );

    if( m_currentPath->targetCheckpoint() == NULL )
    {
        LOG_WARNING( "Target checkpoint is NULL in: %s", __FUNCTION__ );

        return;
    }

    init( m_currentPath->targetCheckpoint() );
}

void Vehicle::setSpeed( int speed )
{
    m_speed = speed;
}

void Vehicle::setBlinkers( Blinkers blinkers )
{
    Q_UNUSED( blinkers );
}

void Vehicle::setLongLights( bool longLight )
{
    Q_UNUSED( longLight );
}

void Vehicle::setBackLights( bool backLight )
{
    Q_UNUSED( backLight );
}

CollisionPoint Vehicle::collisionPoint() const
{
    return mapToScene( property( "bumperX" ).toInt(), property( "bumperY" ).toInt() );
}

void Vehicle::setParentScene( GraphicsScene *scene )
{
    m_parentScene = scene;
}

GraphicsScene* Vehicle::parentScene() const
{
    return m_parentScene;
}
