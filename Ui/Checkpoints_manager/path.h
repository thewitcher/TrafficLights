#ifndef PATH_H
#define PATH_H

#include "checkpoint.h"
#include <QEasingCurve>

class Vehicle;
class QAbstractAnimation;

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

    /*!
     * Parameter increaseSpeed is added to duration. After finish this method, duration variable goes back to default value.
     */
    QAbstractAnimation* animation( Vehicle *target, QObject *parent, double speedMultiplier ) const;
    Checkpoint* targetCheckpoint() const;
    bool doTurn() const; // Returns true if movement will start with turn.

private:
    enum PathType{ MOVE, TURN_AND_MOVE, MOVE_XY, TURN_AND_MOVE_XY };

    Checkpoint *m_targetCheckpoint; // This will be deleted by checkpoint manager
    mutable int m_turnDuration;
    mutable int m_moveDuration;
    const QByteArray m_moveCoordinateProperty;
    const QEasingCurve::Type m_easingCurveX;
    const QEasingCurve::Type m_easingCurveY;
    const QEasingCurve::Type m_easingCurve;
    const PathType m_pathType;
    const Checkpoint::TurnType m_turnType;
    const bool m_sequential;

    QAbstractAnimation* movingToTargetCheckpointAnimation( Vehicle *target, bool start, int speedMiltiplier, QObject* parent = 0 ) const;
    QAbstractAnimation* movingByXYToTargetCheckpointAnimation( Vehicle *target, bool start, int speedMiltiplier, QObject* parent = 0 ) const;

    QAbstractAnimation* turnAndMovingToTargetCheckpointAnimation( Vehicle *target, int speedMiltiplier ) const;
    QAbstractAnimation* turnAndMovingByXYToTargetCheckpointAnimation( Vehicle *target, int speedMiltiplier ) const;
};

#endif // PATH_H
