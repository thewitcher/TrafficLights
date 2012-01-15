#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <QVariant>
#include <QEasingCurve>

class Path;
class Vehicle;

/*!
 * This is point where vehicles get new animations. It gives permission to cars to go from this point. Checkpoints are deploy on the scene
 * and have responibility for no collision cars movement. Each checkpoint has uniq id, which is provided to it by checkpoint manager.
 * By this point You can create path for vehicles. They can drive between this point. If vehicles will reach new point it get path to
 * another point. Remember to create path to every checkpoint.
 */
class Checkpoint
{
public:
    enum TurnType { TURN_90_LEFT = -90, TURN_90_RIGHT = 90, NOT_DEFINED = 0 };

    Checkpoint( qreal x, qreal y );
    ~Checkpoint();
    const Path* randomPath() const;
    qreal posX() const;
    qreal posY() const;
    bool movePermission() const;
    void setMovePermission( bool permission );

private:
    qreal m_x;
    qreal m_y;
    unsigned char m_id;
    bool m_movePermission; // It allows vehicle to move or not.

    QList<Path*> m_paths;

    unsigned char randomNumber( unsigned char max ) const;
    void setId( unsigned char id );
    int estimatedMovingTimeToTargetCheckpoint( const Checkpoint* targetCheckpoint ) const;

    void addMovingByXToTargetCheckpointPath( Checkpoint *targetCheckpoint, int duration, QEasingCurve::Type easingCurve = QEasingCurve::Linear );
    void addMovingByYToTargetCheckpointPath( Checkpoint *targetCheckpoint, int duration, QEasingCurve::Type easingCurve = QEasingCurve::Linear );
    void addMovingByXYToTargetCheckpointPath( Checkpoint *targetCheckpoint, int duration,
                                              QEasingCurve::Type easingCurveX = QEasingCurve::Linear,
                                              QEasingCurve::Type easingCurveY = QEasingCurve::Linear );

    void addTurnAndMovingByXToTargetCheckpointPath( Checkpoint *targetCheckpoint, int turnDuration, int moveDuration, const TurnType turnType,
                                                    QEasingCurve::Type easingCurveX = QEasingCurve::Linear,
                                                    bool sequenatial = true );
    void addTurnAndMovingByYToTargetCheckpointPath( Checkpoint *targetCheckpoint, int turnDuration, int moveDuration, const TurnType turnType,
                                                    QEasingCurve::Type easingCurveY = QEasingCurve::Linear,
                                                    bool sequenatial = true );
    void addTurnAndMovingByXYToTargetCheckpointPath( Checkpoint *targetCheckpoint, int turnDuration, int moveDuration, const TurnType turnType,
                                                     QEasingCurve::Type easingCurveX = QEasingCurve::Linear,
                                                     QEasingCurve::Type easingCurveY = QEasingCurve::Linear,
                                                     bool sequenatial = true );

    void addMove( QVector< Checkpoint* > checkpointsVector, const QString& parameters );

    friend class CheckpointManager;
    friend class CheckpointCreator;
};

#endif // CHECKPOINT_H
