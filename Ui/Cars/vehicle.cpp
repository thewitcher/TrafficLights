#include "vehicle.h"
#include "../Checkpoints_manager/checkpoint.h"
#include "../Checkpoints_manager/path.h"
#include "../../Logger/logger.h"
#include <QAbstractAnimation>
#include <QTimer>
#include <math.h>

#include <QDebug>
const int Vehicle::WAIT_ON_PERMISSION = 1000;

Vehicle::Vehicle( QDeclarativeItem *parent ):
    QDeclarativeItem( parent ),
    m_currentPath( NULL ),
    m_speed( 1 ),
    m_blinkers( false ),
    m_currentCheckpoint( NULL ),
    m_currentAnimation( NULL ),
    m_consequent( NULL ),
    m_predecessor( NULL )
{
    // Sets transformation point to center
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

    static bool first = true;

    if( first )
    {
        // Part for collision detection
        if( m_currentCheckpoint != NULL )
        {
            if( m_currentCheckpoint->lastArrived() == this )
            {
                qDebug() << "Jestem jedynym pojazdem na trasie i usuwam sie z listy ( " << m_speed << " )";
                m_currentCheckpoint->setLastArrived( NULL );
            }
        }

        m_currentCheckpoint = initCheckpoint;

        Vehicle *lastArrived = m_currentCheckpoint->lastArrived();
        setConsquent( lastArrived );

        if( lastArrived != NULL )
        {
            lastArrived->setPredecessor( this );
        }

        m_currentCheckpoint->setLastArrived( this );
        // ############################

        m_currentPath = m_currentCheckpoint->randomPath();

        m_currentAnimation = m_currentPath->animation( this, this, m_speed );

        first = false;
    }

    if( m_currentPath != NULL )
    {
        checkConsequence();

        if( ( m_currentPath->doTurn() == true ) && ( initCheckpoint->movePermission() == false ) )
        {
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

void Vehicle::checkConsequence()
{
    qDebug() << "Sprawdzanie czy nastepnik jest nullem ( " << m_speed << " )";
    if( consequent() == NULL )
    {
        qDebug() << "Jest ( " << m_speed << " )";
        if( isVehicleInNextCheckpoint() == true )
        {
            int time = timeToCollision();
            if( time > 0 )
            {
                resumeMove();
                QTimer::singleShot( time, this, SLOT(moveAndStop()) );
            }
            if( time == 0 )
            {
                qDebug() << "Stoje bo mam czas równy zero ( " << m_speed << " )";
                pauseMove();
                QTimer::singleShot( 1000, this, SLOT(checkConsequence()) );
            }
        }

        // Else - just go to the next checkpoint and inform previous vehicle about this.
        resumeMove();
    }
    else
    {
        qDebug() << "Nie jest";
        int time = timeToCollision();

        if( time > 0 )
        {
            resumeMove();
            QTimer::singleShot( time, this, SLOT(moveAndStop()) );
        }
        if( time == 0 )
        {
            qDebug() << "Stoje bo mam czas równy zero ( " << m_speed << " )";
            pauseMove();
            QTimer::singleShot( 1000, this, SLOT(checkConsequence()) );
        }
    }
}

void Vehicle::moveAndStop()
{
    qDebug() << "Start: moveAndStop()";
    Q_ASSERT( m_currentAnimation != NULL );

    // If vehicle is paused then we resume animation. In other cases we pause the animation.
    if( m_currentAnimation->state() != QAbstractAnimation::Paused )
    {
        qDebug() << "Zatrzymanie ( " << m_speed << " )";;
        m_currentAnimation->pause();
    }

    qDebug() << "(Koniec: moveAndStop) Stoje bo ruszylem sie tyle ile trzeba ( " << m_speed << " )";
    checkConsequence();
}

void Vehicle::resumeMove()
{
    Q_ASSERT( m_currentAnimation != NULL );

    if( m_currentAnimation->state() != QAbstractAnimation::Running )
    {
        qDebug() << "Resume moving";
        m_currentAnimation->resume();
    }
}

void Vehicle::pauseMove()
{
    Q_ASSERT( m_currentAnimation != NULL );

    if( m_currentAnimation->state() != QAbstractAnimation::Paused )
    {
        qDebug() << "Pause moving";
        m_currentAnimation->pause();
    }
}

bool Vehicle::isVehicleInNextCheckpoint()
{
    return true;
}

int Vehicle::timeToCollision()
{
    if( consequent() == NULL )
    {
        return 0;
    }

    int distance = sqrt( pow( x() - consequent()->x(), 2) + pow( y() - consequent()->y(), 2) );
    qDebug() << "Distance: " << distance;

    if( distance < 30 )
    {
        return 0;
    }

    return ( distance / ( 10 * m_speed ) );
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

    if( m_predecessor != NULL )
    {
        m_predecessor->setConsquent( NULL );
    }

    init( m_currentPath->targetCheckpoint() );
}

void Vehicle::setSpeed( int speed )
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

const Vehicle* Vehicle::consequent() const
{
    return m_consequent;
}

void Vehicle::setConsquent( Vehicle *consequent )
{
    m_consequent = consequent;
}

const Vehicle* Vehicle::predecessor() const
{
    return m_predecessor;
}

void Vehicle::setPredecessor( Vehicle *predecessor )
{
    m_predecessor = predecessor;
}
