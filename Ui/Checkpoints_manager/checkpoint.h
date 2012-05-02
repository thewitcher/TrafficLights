#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <QVariant>
#include <QEasingCurve>
#include <QObject>

class Path;
class Vehicle;

/*!
 * This is point where vehicles get new animations. It gives permission to cars to go from this point. Checkpoints are deploy on the scene
 * and have responibility for no collision cars movement. Each checkpoint has uniq id, which is provided to it by checkpoint manager.
 * By this point You can create path for vehicles. They can drive between this point. If vehicles will reach new point it get path to
 * another point. Remember to create path to every checkpoint.
 */
class Checkpoint: public QObject
{

    Q_OBJECT

public:
    /*!
     * It defines turning direction for vehicle in this checkpoint.
     */
    enum TurnType { TURN_90_LEFT = -90, TURN_90_RIGHT = 90, NOT_DEFINED = 0 };

    Checkpoint( qreal x, qreal y );
    ~Checkpoint();
    /*!
     * Every checkpoints contains some paths which can be given to vehicle. Path describe new way for vehicle. This method
     * return random path from path storer. Random behaviour for this function is implemented in order to get more
     * realistic car move.
     */
    const Path* randomPath() const;
    /*!
     * Checkpoint x coordinate.
     */
    qreal posX() const;
    /*!
     * Checkpoint y coordinate.
     */
    qreal posY() const;
    /*!
     * Every vehicle which arrive to this checkpoit should ask for permission to move first. If this function return true
     * than vehicle can continue moving, otherwise it should wait for a while.
     */
    bool movePermission() const;
    /*!
     * @param permission Persmission to move.
     *
     * You can set permission to move on this checkpoint. If You set permission to false then every car will wait in this checkpoit
     * till You set move permmision to true again.
     */
    void setMovePermission( bool permission );
    /*!
     * Emits signal checkpointReached() with flags. Flags describe some behaviour of checkpoint. Some flags are now in use.
     * But You can add new flags to checkpoint and write Your own support for it.
     */
    void reached( Vehicle* vehicle );
    /*!
     * @param flags Flags describe some behaviour of checkpoint. For more details see m_flags description.
     *
     * Sets new flags.
     */
    void setFlags( uint flags = 0 );
    /*!
     * Returns checkpoint id.
     */
    int id() const;
    /*!
     * Returns all paths associated with this checkpoint.
     */
    QList<Path*> allPaths() const;

private:
    /// x coordinate
    qreal m_x;
    /// y coordinate
    qreal m_y;
    /// Checkpoint id
    int m_id;
    /// It allows vehicle to move or not
    bool m_movePermission;

    /*!
     * m_flags contains parameters for checkpoints:
     * <...,9,8,7,6,5,4,3,2,1>
     * 1 - informs junction about vehicles
     * 2,3,4,5,6,7,8 - tells what junction shoud be inform
     * 9 - adds or subtracts to or from vehicles counter in junction
     *
     * First junction (id 0):
     * add =      100000011 = 259
     * subtract = 000000011 = 3
     *
     * Second junction (id 1):
     * add =      100000101 = 261
     * subtract = 000000101 = 5
     *
     * Third junction (id 2):
     * add =      100001001 = 265
     * subtract = 000001001 = 9
     *
     * Fourth junction (id 3):
     * add =      100010001 = 273
     * subtract = 000010001 = 17
     *
     * Fifth junction (id 4):
     * add =      100100001 = 289
     * subtract = 000100001 = 33
     *
     * Sixth junction (id 5):
     * add =      101000001 = 321
     * subtract = 001000001 = 65
     *
     * Seventh junction (id 6):
     * add =      110000001 = 385
     * subtract = 010000001 = 129
     */
    uint m_flags;

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

signals:
    void checkpointReached( uint flags, int checkpointId, Vehicle* vehicle );

    friend class CheckpointManager;
    friend class CheckpointCreator;
};

#endif // CHECKPOINT_H
