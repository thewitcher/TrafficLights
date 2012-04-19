#include "vehicle.h"
#include "../Checkpoints_manager/checkpoint.h"
#include "../Checkpoints_manager/path.h"
#include "../../Logger/logger.h"
#include <QAbstractAnimation>
#include <QTimer>
#include <QTime>

const int Vehicle::WAIT_ON_PERMISSION = 1000;
int Vehicle::S_VEHICLE_ID = 0;

Vehicle::Vehicle( QDeclarativeItem *parent ):
    QDeclarativeItem( parent ),
    m_currentPath( NULL ),
    m_speed( 1 ),
    m_currentCheckpoint( NULL ),
    m_currentAnimation( NULL ),
    m_first( true ),
    m_checkCollisions( true ),
    m_vehicleId( S_VEHICLE_ID++ )
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

    // This function can be call many times, but we want to init new checkpoints and othe parameters only for first time for any new
    // checkpoint.
    if( m_first )
    {
        LOG_INFO( "First time: %s. Inits new checkpint and drawing new path", __FUNCTION__ )

        // False means that recent checkpoint turn off checking collisions, so we turn it on again.
        if( m_checkCollisions == false )
        {
            m_checkCollisions = true;
        }

        // For this particular checkpoint we switch off collision detection. These checkpoints are entrance to BladzioJunction.
        // Collision detection will be switch on if vehicle will arrive to next checkpoint.
        if( ( initCheckpoint->id() == 35 )
            || ( initCheckpoint->id() == 39 )
            || ( initCheckpoint->id() == 22 )
            || ( initCheckpoint->id() == 49 ) )
        {
            m_checkCollisions = false;
        }

        m_currentCheckpoint = initCheckpoint;

        m_currentPath = m_currentCheckpoint->randomPath();

        m_currentAnimation = NULL;

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

        m_currentAnimation = m_currentPath->animation( this, this, m_speed );

        m_currentCheckpoint->reached( this );

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
    LOG_INFO( "Try to resume vehicle move: start %s", __FUNCTION__  );

    if( m_currentAnimation != NULL )
    {
        if( m_currentAnimation->state() == QAbstractAnimation::Paused )
        {
            setBackLights( false );
            m_currentAnimation->resume();
        }
    }
    else
    {
        LOG_WARNING( "Current animation is NULL (%s)", __FUNCTION__ );
    }
}

void Vehicle::pauseMove()
{
    LOG_INFO( "Try to pause vehicle: start %s", __FUNCTION__  );

    if( m_currentAnimation != NULL )
    {
        if( m_currentAnimation->state() == QAbstractAnimation::Running )
        {
            LOG_INFO( "Animation has state: %i", m_currentAnimation->state() );

            setBackLights( true );
            m_currentAnimation->pause();
        }

        LOG_INFO( "Animation didn't pause, becouse it has no RUNNING state. Current state: %i", m_currentAnimation->state() );
    }
    else
    {
        LOG_WARNING( "Current animation is NULL (%s)", __FUNCTION__ );
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

    LOG_INFO( "Inits with new checkpoint in %s", __FUNCTION__ );

    init( m_currentPath->targetCheckpoint() );
}

void Vehicle::setSpeed( int speed )
{
    LOG_INFO( "Set vehicle speed to: %i", speed );

    m_speed = speed;
}

CollisionPoint Vehicle::collisionPoint() const
{
    return mapToScene( property( "bumperX" ).toInt(), property( "bumperY" ).toInt() );
}

void Vehicle::setParentScene( GraphicsScene *scene )
{
    LOG_INFO( "Add scene which contains this vehicle (%s)", __FUNCTION__ );

    m_parentScene = scene;
}

GraphicsScene* Vehicle::parentScene() const
{
    return m_parentScene;
}

QSize Vehicle::size() const
{
    QSize size( 20, 20 );

    if( direction() == Horizontal )
    {
        size.setWidth( property( "realHeight" ).toInt() );
        size.setHeight( property( "realWidth" ).toInt() );
    }
    else if( direction() == Vertical )
    {
        size.setWidth( property( "realWidth" ).toInt() );
        size.setHeight( property( "realHeight" ).toInt() );
    }

    LOG_CRITICAL( "Unknown vehicle direction %s", __FUNCTION__ );

    return size;
}

QPoint Vehicle::topLeftPoint() const
{
    return QPoint( x() - 0.5 * size().width() + 10, y() - 0.5 * size().height() + 10  );
}

QPoint Vehicle::bottomRightPoint() const
{
    return QPoint( x() + 0.5 * size().width() + 10, y() + 0.5 * size().height() + 10  );
}

void Vehicle::setCheckCollisions( bool check )
{
    m_checkCollisions = check;
}

bool Vehicle::checkCollisions() const
{
    return m_checkCollisions;
}

Vehicle::VehicleDirection Vehicle::direction() const
{
    if( ( abs( rotation() ) == 0 ) || ( abs( rotation() ) == 180 ) )
    {
        return Horizontal;
    }
    else if( ( abs( rotation() ) == 90 ) || ( abs( rotation() ) == 270 ) )
    {
        return Vertical;
    }

    return Unknown;
}

void Vehicle::setDarkDesign( bool dark )
{
    Q_UNUSED( dark );
}

void Vehicle::setBlinkers( Blinkers blinkers )
{
    switch( blinkers )
    {
    case LEFT_BLINKERS:
        QMetaObject::invokeMethod( this, "turnOnLeftBlinkers" );
        break;
    case RIGHT_BLINKERS:
        QMetaObject::invokeMethod( this, "turnOnRightBlinkers" );
        break;
    case NO_BLINKERS:
        QMetaObject::invokeMethod( this, "stopBlinkers" );
        break;
    }
}

void Vehicle::setBackLights( bool backLight )
{
    if( backLight )
        QMetaObject::invokeMethod( this, "onBackLights" );
    else
        QMetaObject::invokeMethod( this, "offBackLights" );
}

void Vehicle::setLongLights( bool longLight )
{
    if( longLight )
        QMetaObject::invokeMethod( this, "turnOnLongLights" );
    else
        QMetaObject::invokeMethod( this, "turnOffLongLights" );
}

int Vehicle::waitingTimeInSeconds()
{
    return m_startWaitingTime.secsTo( QTime::currentTime() );
}

void Vehicle::updateWaitingTime()
{
    m_startWaitingTime = QTime::currentTime();
}
