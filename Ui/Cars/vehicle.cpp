#include "vehicle.h"
#include "../Checkpoints_manager/checkpoint.h"
#include "../Checkpoints_manager/path.h"
#include "../../Logger/logger.h"
#include <QAbstractAnimation>

Vehicle::Vehicle( QDeclarativeItem *parent ):
    QDeclarativeItem( parent ),
    m_currentPath( NULL ),
    m_speed( 1 ),
    m_blinkers( false ),
    m_currentAnimation( NULL )
{
    // Sets transformation point to center
    setTransformOriginPoint( 9, 9 );
}

void Vehicle::init( const Checkpoint *initCheckpoint )
{
    LOG_INFO( "Sets new speed to checkpoint: %f", m_speed );
    LOG_INFO( "Creates new path for checkpoint: (%f, %f) position", initCheckpoint->posX(), initCheckpoint->posY() );

    m_currentPath = initCheckpoint->randomPath();

    if( m_currentPath != NULL )
    {
        m_currentAnimation = m_currentPath->animation( this, this, m_speed );

        LOG_INFO( "Target of this animation is on pos: (%f, %f) position", m_currentPath->targetCheckpoint()->posX(),
                  m_currentPath->targetCheckpoint()->posY() );
    }
    else
    {
        LOG_WARNING( "m_currentPath is NULL: %s", __FUNCTION__ );
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

void Vehicle::setSpeed( double speed )
{
    m_speed = speed;
}

void Vehicle::switchOnOffBlinkers( bool blinkers )
{
    Q_UNUSED( blinkers )

    m_blinkers = !m_blinkers;

    emit blinkersChanged();
}

bool Vehicle::blinkers()
{
    return m_blinkers;
}