#include "path.h"
#include "../../Logger/logger.h"
#include "../Cars/vehicle.h"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>

Path::Path( Checkpoint *targetCheckpoint, int duration, const QByteArray &moveCoordinateProperty,
            QEasingCurve::Type easingCurve ):
    m_targetCheckpoint( targetCheckpoint ),
    m_turnDuration( -1 ),
    m_moveDuration( duration ),
    m_moveCoordinateProperty( moveCoordinateProperty ),
    m_easingCurveX( QEasingCurve::Linear ),
    m_easingCurveY( QEasingCurve::Linear ),
    m_easingCurve( easingCurve ),
    m_pathType( MOVE ),
    m_turnType( Checkpoint::NOT_DEFINED ),
    m_sequential( true )
{
}

Path::Path( Checkpoint *targetCheckpoint, int duration,
            QEasingCurve::Type easingCurveX,
            QEasingCurve::Type easingCurveY ):
    m_targetCheckpoint( targetCheckpoint ),
    m_turnDuration( -1 ),
    m_moveDuration( duration ),
    m_moveCoordinateProperty( QByteArray() ),
    m_easingCurveX( easingCurveX ),
    m_easingCurveY( easingCurveY ),
    m_easingCurve( QEasingCurve::Linear ),
    m_pathType( MOVE_XY ),
    m_turnType( Checkpoint::NOT_DEFINED ),
    m_sequential( true )
{

}

Path::Path( Checkpoint *targetCheckpoint, int turnDuration, int moveDuration,
            const Checkpoint::TurnType turnType,
            QEasingCurve::Type easingCurveX,
            QEasingCurve::Type easingCurveY,
            bool sequential):
    m_targetCheckpoint( targetCheckpoint ),
    m_turnDuration( turnDuration ),
    m_moveDuration( moveDuration ),
    m_moveCoordinateProperty( QByteArray() ),
    m_easingCurveX( easingCurveX ),
    m_easingCurveY( easingCurveY ),
    m_easingCurve( QEasingCurve::Linear ),
    m_pathType( TURN_AND_MOVE_XY ),
    m_turnType( turnType ),
    m_sequential( sequential )
{

}

Path::Path( Checkpoint *targetCheckpoint, int turnDuration, int moveDuration,
            const QByteArray &moveCoordinateProperty,
            const Checkpoint::TurnType turnType,
            QEasingCurve::Type easingCurve,
            bool sequential ):
    m_targetCheckpoint( targetCheckpoint ),
    m_turnDuration( turnDuration ),
    m_moveDuration( moveDuration ),
    m_moveCoordinateProperty( moveCoordinateProperty ),
    m_easingCurveX( QEasingCurve::Linear ),
    m_easingCurveY( QEasingCurve::Linear ),
    m_easingCurve( easingCurve ),
    m_pathType( TURN_AND_MOVE ),
    m_turnType( turnType ),
    m_sequential( sequential )
{

}

Path::~Path()
{
}

const Checkpoint* Path::targetCheckpoint() const
{
    return m_targetCheckpoint;
}

void Path::animation( Vehicle *target, QObject *parent ) const
{
    Q_UNUSED( parent );

    LOG_INFO( "Start switching by path type in: %s", __FUNCTION__ );

    switch( m_pathType )
    {
    case MOVE:
        movingToTargetCheckpointAnimation( target, true );
        break;
    case MOVE_XY:
        movingByXYToTargetCheckpointAnimation( target, true );
        break;
    case TURN_AND_MOVE:
        turnAndMovingToTargetCheckpointAnimation( target );
        break;
    case TURN_AND_MOVE_XY:
        turnAndMovingByXYToTargetCheckpointAnimation( target );
        break;
    }
}

QPropertyAnimation* Path::movingToTargetCheckpointAnimation( Vehicle *target, bool start, QObject* parent ) const
{
    Q_UNUSED( parent );

    LOG_INFO( "Moving animation by one coordinate (%s)", __FUNCTION__ );

    QPropertyAnimation *propertyAnimation = new QPropertyAnimation( target, m_moveCoordinateProperty, target );

    propertyAnimation->setDuration( m_moveDuration );

    if( m_moveCoordinateProperty == "x" )
    {
        propertyAnimation->setStartValue( target->x() );
        propertyAnimation->setEndValue( m_targetCheckpoint->posX() );
    }
    else if( m_moveCoordinateProperty == "y" )
    {
        propertyAnimation->setStartValue( target->y() );
        propertyAnimation->setEndValue( m_targetCheckpoint->posY() );
    }
    else
    {
        LOG_WARNING( "Animation didn't start. Property is invalid: %s", __FUNCTION__ );

        return NULL;
    }

    propertyAnimation->setEasingCurve( m_easingCurve );

    propertyAnimation->setObjectName( "propertyAnimation" );


    if( start )
    {
        QObject::connect( propertyAnimation, SIGNAL(finished()), target, SLOT(onAnimationFinish()) );
        propertyAnimation->start( QPropertyAnimation::DeleteWhenStopped );
    }

    return propertyAnimation;
}

QParallelAnimationGroup* Path::movingByXYToTargetCheckpointAnimation( Vehicle *target, bool start, QObject *parent ) const
{
    LOG_INFO( "Moving animation by x and y coordinate (%s)", __FUNCTION__ );

    QParallelAnimationGroup *parallelAnimationGroup = new QParallelAnimationGroup( parent );

    parallelAnimationGroup->setObjectName( "parallelAniamtion" );

    QPropertyAnimation *propertyAnimationX = new QPropertyAnimation( target, "x", parallelAnimationGroup );
    propertyAnimationX->setDuration( m_moveDuration );
    propertyAnimationX->setStartValue( target->x() );
    propertyAnimationX->setEndValue( m_targetCheckpoint->posX() );
    propertyAnimationX->setEasingCurve( m_easingCurveX );
    propertyAnimationX->setObjectName( "propertyMoveAnimation" );

    QPropertyAnimation *propertyAnimationY = new QPropertyAnimation( target, "y", parallelAnimationGroup );
    propertyAnimationY->setDuration( m_moveDuration );
    propertyAnimationY->setStartValue( target->y() );
    propertyAnimationY->setEndValue( m_targetCheckpoint->posY() );
    propertyAnimationX->setEasingCurve( m_easingCurveY );
    propertyAnimationY->setObjectName( "propertyMoveAnimation" );

    parallelAnimationGroup->addAnimation(propertyAnimationX);
    parallelAnimationGroup->addAnimation(propertyAnimationY);


    if( start )
    {
        QObject::connect( parallelAnimationGroup, SIGNAL(finished()), target, SLOT(onAnimationFinish()) );
        parallelAnimationGroup->start( QPropertyAnimation::DeleteWhenStopped );
    }

    return parallelAnimationGroup;
}

void Path::turnAndMovingByXYToTargetCheckpointAnimation( Vehicle *target ) const
{
    LOG_INFO( "Turn and move animation by x and y coordinate (%s)", __FUNCTION__ );

    QAnimationGroup *animationGroup = NULL;

    if( m_sequential )
    {
        animationGroup = new QSequentialAnimationGroup;
        animationGroup->setObjectName( "sequentialAnimation" );
    }
    else
    {
        animationGroup = new QParallelAnimationGroup;
        animationGroup->setObjectName( "parallelAnimation" );
    }

    // Rotating animation
    QPropertyAnimation *propertyAnimationRotate = new QPropertyAnimation( target, "rotation", animationGroup );

    propertyAnimationRotate->setDuration( m_turnDuration );
    propertyAnimationRotate->setStartValue( 0 );
    propertyAnimationRotate->setEndValue( m_turnType );

    propertyAnimationRotate->setObjectName( "propertyRotateAnimation" );

    // Adding every animations to sequential group and start the animation
    animationGroup->addAnimation( propertyAnimationRotate );
    animationGroup->addAnimation( movingByXYToTargetCheckpointAnimation( target, false, animationGroup ) );

    QObject::connect( animationGroup, SIGNAL(finished()), target, SLOT(onAnimationFinish()) );

    animationGroup->start( QAbstractAnimation::DeleteWhenStopped );
}

void Path::turnAndMovingToTargetCheckpointAnimation( Vehicle *target ) const
{
    LOG_INFO( "Turn and move animation by one coordinate (%s)", __FUNCTION__ );

    QAnimationGroup *animationGroup = NULL;

    if( m_sequential )
    {
        animationGroup = new QSequentialAnimationGroup;
        animationGroup->setObjectName( "sequentialAnimation" );
    }
    else
    {
        animationGroup = new QParallelAnimationGroup;
        animationGroup->setObjectName( "parallelAnimation" );
    }


    // Rotating animation
    QPropertyAnimation *propertyAnimationRotate = new QPropertyAnimation( target, "rotation", animationGroup );

    propertyAnimationRotate->setDuration( m_turnDuration );
    propertyAnimationRotate->setStartValue( 0 );
    propertyAnimationRotate->setEndValue( m_turnType );

    propertyAnimationRotate->setObjectName( "propertyRotateAnimation" );

    // Adding every animations to sequential group and start the animation
    animationGroup->addAnimation( propertyAnimationRotate );
    animationGroup->addAnimation( movingToTargetCheckpointAnimation( target, false, animationGroup ) );

    QObject::connect( animationGroup, SIGNAL(finished()), target, SLOT(onAnimationFinish()) );

    animationGroup->start( QAbstractAnimation::DeleteWhenStopped );
}
