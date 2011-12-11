#include "checkpoint.h"
#include "../../Logger/logger.h"
#include "path.h"
#include <cstdlib>

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

void Checkpoint::addPath( Checkpoint *targetCheckpoint, int duration, const QByteArray property,
                          const QVariant &startValue, const QVariant &endValue, const PathType pathType )
{
    if( targetCheckpoint != NULL )
    {
        m_paths << new Path( targetCheckpoint, duration, property, startValue, endValue, pathType );
    }
    else
    {
        LOG_WARNING( "Target checkpoint is NULL: %s", __FUNCTION__ );
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
