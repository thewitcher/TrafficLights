#include "vehicle.h"
#include "../Checkpoints_manager/checkpoint.h"
#include "../Checkpoints_manager/path.h"
#include "../../Logger/logger.h"
#include <QAbstractAnimation>
#include "QTimer"

const int Vehicle::WAIT_ON_PERMISSION = 1000;

Vehicle::Vehicle( QDeclarativeItem *parent ):
    QDeclarativeItem( parent ),
    m_currentPath( NULL ),
    m_speed( 1 ),
    m_blinkers( false ),
    m_currentAnimation( NULL )
    m_currentCheckpoint( NULL )
{
    // Sets transformation point to center
    setTransformOriginPoint( 9, 9 );
}

Vehicle::~Vehicle()
{
}

void Vehicle::init( const Checkpoint *initCheckpoint )
{
    LOG_INFO( "Sets new speed to checkpoint: %f", m_speed );
    LOG_INFO( "Creates new path for checkpoint: (%f, %f) position", initCheckpoint->posX(), initCheckpoint->posY() );

    static bool first = true;

    if( first )
    {
        m_currentPath = initCheckpoint->randomPath();

        first = false;
    }

    if( m_currentPath != NULL )
    {
        m_currentAnimation = m_currentPath->animation( this, this, m_speed );

        if( ( m_currentPath->doTurn() == true ) && ( initCheckpoint->movePermission() == false ) )
        {
            m_currentCheckpoint = initCheckpoint;

            QTimer::singleShot( WAIT_ON_PERMISSION, this, SLOT(init()) );

            LOG_INFO( "Permission denied. Wait time: %i", WAIT_ON_PERMISSION );

            return;
        }

        LOG_INFO( "Target of this animation is on pos: (%f, %f) position", m_currentPath->targetCheckpoint()->posX(),
                  m_currentPath->targetCheckpoint()->posY() );

        first = true;
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
