#include "path.h"
#include "../../Logger/logger.h"
#include "../Cars/vehicle.h"
#include "../Cars/property-move.h"
#include "../Cars/parallel-move.h"
#include "../Cars/sequential-move.h"

Path::Path( Checkpoint *targetCheckpoint, int duration, const QByteArray &moveCoordinateProperty,
            QEasingCurve::Type easingCurve ):
    m_targetCheckpoint( targetCheckpoint ),
    m_turnDuration( -1 ),
    m_moveDuration( duration ),
    m_originalTurnDuration( -1 ),
    m_originalMoveDuration( duration ),
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
    m_originalTurnDuration( -1 ),
    m_originalMoveDuration( duration ),
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
    m_originalTurnDuration( turnDuration ),
    m_originalMoveDuration( moveDuration ),
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
    m_originalTurnDuration( turnDuration ),
    m_originalMoveDuration( moveDuration ),
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

QAbstractAnimation* Path::animation( Vehicle *target, QObject *parent, double speedMultiplier ) const
{
    Q_UNUSED( parent );

    LOG_INFO( "Times duration by %f", speedMultiplier );

    m_moveDuration = m_originalMoveDuration * speedMultiplier;
    m_turnDuration = m_originalTurnDuration * speedMultiplier;

    LOG_INFO( "Starts switching by path type in: %s", __FUNCTION__ );

    switch( m_pathType )
    {
    case MOVE:
        return movingToTargetCheckpointAnimation( target, true );
    case MOVE_XY:
        return movingByXYToTargetCheckpointAnimation( target, true );
    case TURN_AND_MOVE:
        return turnAndMovingToTargetCheckpointAnimation( target );
    case TURN_AND_MOVE_XY:
        return turnAndMovingByXYToTargetCheckpointAnimation( target );
    }

    return NULL;
}

QAbstractAnimation* Path::movingToTargetCheckpointAnimation( Vehicle *target, bool start, QObject* parent ) const
{
    Q_UNUSED( parent );

    LOG_INFO( "Moving animation by one coordinate (%s)", __FUNCTION__ );

    PropertyMove *propertyMove = new PropertyMove( target, m_moveCoordinateProperty, target );

    propertyMove->setDuration( m_moveDuration );

    if( m_moveCoordinateProperty == "x" )
    {
        propertyMove->setStartValue( target->x() );
        propertyMove->setEndValue( m_targetCheckpoint->posX() );
    }
    else if( m_moveCoordinateProperty == "y" )
    {
        propertyMove->setStartValue( target->y() );
        propertyMove->setEndValue( m_targetCheckpoint->posY() );
    }
    else
    {
        LOG_WARNING( "Animation didn't start. Property is invalid: %s", __FUNCTION__ );

        return NULL;
    }

    propertyMove->setEasingCurve( m_easingCurve );

    propertyMove->setObjectName( "propertyAnimation" );


    if( start )
    {
        QObject::connect( propertyMove, SIGNAL(finished()), target, SLOT(onAnimationFinish()) );
        propertyMove->start( QPropertyAnimation::DeleteWhenStopped );
    }

    return propertyMove;
}

QAbstractAnimation* Path::movingByXYToTargetCheckpointAnimation( Vehicle *target, bool start, QObject *parent ) const
{
    LOG_INFO( "Moving animation by x and y coordinate (%s)", __FUNCTION__ );

    ParallelMove *parallelMove = new ParallelMove( target, parent );

    parallelMove->setObjectName( "parallelAniamtion" );

    QPropertyAnimation *propertyAnimationX = new QPropertyAnimation( target, "x", parallelMove );
    propertyAnimationX->setDuration( m_moveDuration );
    propertyAnimationX->setStartValue( target->x() );
    propertyAnimationX->setEndValue( m_targetCheckpoint->posX() );
    propertyAnimationX->setEasingCurve( m_easingCurveX );
    propertyAnimationX->setObjectName( "propertyMoveAnimation" );

    QPropertyAnimation *propertyAnimationY = new QPropertyAnimation( target, "y", parallelMove );
    propertyAnimationY->setDuration( m_moveDuration );
    propertyAnimationY->setStartValue( target->y() );
    propertyAnimationY->setEndValue( m_targetCheckpoint->posY() );
    propertyAnimationX->setEasingCurve( m_easingCurveY );
    propertyAnimationY->setObjectName( "propertyMoveAnimation" );

    parallelMove->addAnimation(propertyAnimationX);
    parallelMove->addAnimation(propertyAnimationY);


    if( start )
    {
        QObject::connect( parallelMove, SIGNAL(finished()), target, SLOT(onAnimationFinish()) );
        parallelMove->start( QPropertyAnimation::DeleteWhenStopped );
    }

    return parallelMove;
}

QAbstractAnimation* Path::turnAndMovingByXYToTargetCheckpointAnimation( Vehicle *target ) const
{
    LOG_INFO( "Turn and move animation by x and y coordinate (%s) (is sequential: %i)", __FUNCTION__, m_sequential );

    LOG_INFO( "Switching on blinkers in: %s", target->objectName().toLatin1().data() );
    target->switchOnOffBlinkers();

    QAnimationGroup *animationGroup = NULL;

    if( m_sequential )
    {
        animationGroup = new SequentialMove( target );
        animationGroup->setObjectName( "sequentialAnimation" );
    }
    else
    {
        animationGroup = new ParallelMove( target );
        animationGroup->setObjectName( "parallelAnimation" );
    }

    // Rotating animation
    QPropertyAnimation *propertyAnimationRotate = new QPropertyAnimation( target, "rotation", animationGroup );

    int startRotationValue = target->property( "rotation" ).toInt();

    propertyAnimationRotate->setDuration( m_turnDuration );
    propertyAnimationRotate->setStartValue( startRotationValue );
    propertyAnimationRotate->setEndValue( startRotationValue + m_turnType );

    propertyAnimationRotate->setObjectName( "propertyRotateAnimation" );

    // Adding every animations to sequential group and start the animation
    animationGroup->addAnimation( propertyAnimationRotate );
    animationGroup->addAnimation( movingByXYToTargetCheckpointAnimation( target, false, animationGroup ) );

    QObject::connect( propertyAnimationRotate, SIGNAL(finished()), target, SLOT(switchOnOffBlinkers()) );
    QObject::connect( animationGroup, SIGNAL(finished()), target, SLOT(onAnimationFinish()) );

    animationGroup->start( QAbstractAnimation::DeleteWhenStopped );

    return animationGroup;
}

QAbstractAnimation* Path::turnAndMovingToTargetCheckpointAnimation( Vehicle *target ) const
{
    LOG_INFO( "Turn and move animation by one coordinate (%s)", __FUNCTION__ );

    LOG_INFO( "Switching on blinkers in: %s", target->objectName().toLatin1().data() );
    target->switchOnOffBlinkers();

    QAnimationGroup *animationGroup = NULL;

    if( m_sequential )
    {
        animationGroup = new SequentialMove( target );
        animationGroup->setObjectName( "sequentialAnimation" );
    }
    else
    {
        animationGroup = new ParallelMove( target );
        animationGroup->setObjectName( "parallelAnimation" );
    }

    // Rotating animation
    QPropertyAnimation *propertyAnimationRotate = new QPropertyAnimation( target, "rotation", animationGroup );

    int startRotationValue = target->property( "rotation" ).toInt();

    propertyAnimationRotate->setDuration( m_turnDuration );
    propertyAnimationRotate->setStartValue( startRotationValue );
    propertyAnimationRotate->setEndValue( startRotationValue + m_turnType );

    propertyAnimationRotate->setObjectName( "propertyRotateAnimation" );

    // Adding every animations to sequential group and start the animation
    animationGroup->addAnimation( propertyAnimationRotate );
    animationGroup->addAnimation( movingToTargetCheckpointAnimation( target, false, animationGroup ) );

    QObject::connect( propertyAnimationRotate, SIGNAL(finished()), target, SLOT(switchOnOffBlinkers()) );
    QObject::connect( animationGroup, SIGNAL(finished()), target, SLOT(onAnimationFinish()) );

    animationGroup->start( QAbstractAnimation::DeleteWhenStopped );

    return animationGroup;
}

bool Path::doTurn() const
{
    switch( m_pathType )
    {
        case TURN_AND_MOVE:
        case TURN_AND_MOVE_XY:
        return true;
    default:
        return false;
    }

    return false;
}
