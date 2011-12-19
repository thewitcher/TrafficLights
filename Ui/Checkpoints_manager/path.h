#ifndef PATH_H
#define PATH_H

#include "checkpoint.h"
#include <QEasingCurve>

class Vehicle;
class QPropertyAnimation;
class QParallelAnimationGroup;

/*!
 * Path contains target checkpoint and fucntion, which can create property animation. This animation is set to target object and will
 * be deleted by this object (this object is now parent of this animation).
 */
class Path
{
public:
    Path( Checkpoint *targetCheckpoint, int duration, const QByteArray& moveCoordinateProperty, QEasingCurve::Type easingCurve = QEasingCurve::Linear );
    Path( Checkpoint *targetCheckpoint, int duration,
          QEasingCurve::Type easingCurveX = QEasingCurve::Linear,
          QEasingCurve::Type easingCurveY = QEasingCurve::Linear );

    Path( Checkpoint *targetCheckpoint, int turnDuration, int moveDuration, const QByteArray& moveCoordinateProperty, const Checkpoint::TurnType turnType,
          QEasingCurve::Type easingCurve = QEasingCurve::Linear,
          bool sequential = true );
    Path( Checkpoint *targetCheckpoint, int turnDuration, int moveDuration, const Checkpoint::TurnType turnType,
          QEasingCurve::Type easingCurveX,
          QEasingCurve::Type easingCurveY,
          bool sequential );
    ~Path();

    void animation( Vehicle *target, QObject *parent ) const;
    const Checkpoint* targetCheckpoint() const;

private:
    enum PathType{ MOVE, TURN_AND_MOVE, MOVE_XY, TURN_AND_MOVE_XY };

    const Checkpoint *m_targetCheckpoint; // This will be deleted by checkpoint manager
    int m_turnDuration;
    int m_moveDuration;
    const QByteArray m_moveCoordinateProperty;
    const QEasingCurve::Type m_easingCurveX;
    const QEasingCurve::Type m_easingCurveY;
    const QEasingCurve::Type m_easingCurve;
    const PathType m_pathType;
    const Checkpoint::TurnType m_turnType;
    const bool m_sequential;

    QPropertyAnimation* movingToTargetCheckpointAnimation( Vehicle *target, bool start = true, QObject* parent = 0 ) const;
    QParallelAnimationGroup* movingByXYToTargetCheckpointAnimation( Vehicle *target, bool start = true, QObject* parent = 0 ) const;

    void turnAndMovingToTargetCheckpointAnimation( Vehicle *target ) const;
    void turnAndMovingByXYToTargetCheckpointAnimation( Vehicle *target ) const;
};

#endif // PATH_H
