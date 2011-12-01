#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <QVariant>

class Path;

/*!
 * This is point where vehicles get new animations. It gives permission to cars to go from this point. Checkpoints are deploy on the scene
 * and have responibility for no collision cars movement. Each checkpoint has uniq id, which is provided to it by checkpoint manager.
 * By this point You can create path for vehicles. They can drive between this point. If vehicles will reach new point it get path to
 * another point. Remember to create path to every checkpoint.
 */
class Checkpoint
{
public:
    Checkpoint( qreal x, qreal y );
    ~Checkpoint();
    const Path* randomPath() const;
    qreal posX() const;
    qreal posY() const;

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
