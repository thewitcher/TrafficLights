#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <QVariant>

class Path;

/*!
 * This is point where vehicles get new animations. It gives permission to cars to go from this point. Checkpoints are deploy on the scene
 * and have responibility for no collision cars movement. Each checkpoint has uniq id, which is provided to it by checkpoint manager.
 */
class Checkpoint
{
public:
    Checkpoint( qreal x, qreal y );
    ~Checkpoint();
    const Path* randomPath() const;

private:
    qreal m_x;
    qreal m_y;
    unsigned char m_id;

    QList<Path*> m_paths;

    unsigned char randomNumber( unsigned char max ) const;
    void setId( unsigned char id );
    void addPath( Checkpoint *targetCheckpoint, int duration, const QByteArray property,
                  const QVariant& startValue, const QVariant& endValue );

    friend class CheckpointManager;
};

#endif // CHECKPOINT_H
