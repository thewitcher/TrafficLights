#include "path.h"
#include "../../Logger/logger.h"
#include "../Cars/vehicle.h"
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

Path::Path( Checkpoint *targetCheckpoint, int duration, const QByteArray property,
            const QVariant &startValue, const QVariant &endValue, const Checkpoint::PathType pathType ):
    m_targetCheckpoint( targetCheckpoint ),
    m_duration( duration ),
    m_property( property ),
    m_startValue( startValue ),
    m_endValue( endValue ),
    m_pathType( pathType )
{
}

Path::~Path()
{
}

void Path::animation( Vehicle *target, QObject *parent ) const
{
    switch( m_pathType )
    {
    case Checkpoint::TURN_LEFT:
        animationWithTurn( target, parent, m_pathType );
        break;
    case Checkpoint::TURN_RIGHT:
        animationWithTurn( target, parent, m_pathType );
        break;
    case Checkpoint::AHEAD:
        animationAhead( target, parent );
        break;
    default:
        LOG_INFO( "Default option was choosen in switch mode (%s)", __FUNCTION__ );
        break;
    }

    LOG_INFO( "End animation function for %s", target->objectName().toLatin1().data() );
}

void Path::animationWithTurn( Vehicle *target, QObject *parent, Checkpoint::PathType pathType ) const
{
    LOG_INFO( "Start %s", __FUNCTION__ );

    Q_UNUSED( parent );

    QSequentialAnimationGroup *sequentialAnimation = new QSequentialAnimationGroup;
    sequentialAnimation->setObjectName( "sequentialAnimation" );

    // Rotating animation
    QPropertyAnimation *propertyAnimationRotate = new QPropertyAnimation( target, "rotation", sequentialAnimation );

    propertyAnimationRotate->setDuration( 1000 );
    propertyAnimationRotate->setStartValue( 0 );

    char angle = 1;

    switch( pathType )
    {
    case Checkpoint::TURN_RIGHT:
        angle = 1;
        break;
    case Checkpoint::TURN_LEFT:
        angle = -1;
        break;
    default:
        break;
    }

    propertyAnimationRotate->setEndValue( angle * 90 );
    propertyAnimationRotate->setObjectName( "propertyAnimation" );

    // Just moving
    QPropertyAnimation *propertyAnimationNormalMove = new QPropertyAnimation( target, m_property, sequentialAnimation );

    propertyAnimationNormalMove->setDuration( m_duration );
    propertyAnimationNormalMove->setStartValue( m_startValue );
    propertyAnimationNormalMove->setEndValue( m_endValue.toInt() );
    propertyAnimationNormalMove->setObjectName( "propertyAnimation" );

    // Adding every animations to sequential group and start the animation
    sequentialAnimation->addAnimation( propertyAnimationRotate );
    sequentialAnimation->addAnimation( propertyAnimationNormalMove );
    sequentialAnimation->start( QAbstractAnimation::DeleteWhenStopped );

    QObject::connect( sequentialAnimation, SIGNAL(finished()), target, SLOT(onAnimationFinish()) );
}

void Path::animationAhead( Vehicle *target, QObject *parent ) const
{
    LOG_INFO( "Start %s", __FUNCTION__ );

    QPropertyAnimation *propertyAnimation = new QPropertyAnimation( target, m_property, parent );

    propertyAnimation->setDuration( m_duration );
    propertyAnimation->setStartValue( m_startValue );
    propertyAnimation->setEndValue( m_endValue );
    propertyAnimation->setObjectName( "propertyAnimation" );
    propertyAnimation->start( QPropertyAnimation::DeleteWhenStopped );

    QObject::connect( propertyAnimation, SIGNAL(finished()), target, SLOT(onAnimationFinish()) );
}

const Checkpoint* Path::targetCheckpoint() const
{
    return m_targetCheckpoint;
}
