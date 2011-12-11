#include "vehicle.h"
#include "../Checkpoints_manager/checkpoint.h"
#include "../Checkpoints_manager/path.h"
#include "../../Logger/logger.h"

Vehicle::Vehicle( QGraphicsItem *parent ):
    QGraphicsWidget( parent ),
    m_currentPath( NULL )
{
    // Sets transformation point to center
    setTransformOriginPoint( 9, 9 );
}

void Vehicle::init( const Checkpoint *initCheckpoint )
{
    LOG_INFO( "Creating new path for checkpint: (%f, %f) position", initCheckpoint->posX(), initCheckpoint->posY() );

    m_currentPath = initCheckpoint->randomPath();

    if( m_currentPath != NULL )
    {
        m_currentPath->animation( this, this );

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
    }

    init( m_currentPath->targetCheckpoint() );
}
