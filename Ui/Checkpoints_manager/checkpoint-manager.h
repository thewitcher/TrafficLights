#ifndef CHECKPOINTMANAGER_H
#define CHECKPOINTMANAGER_H

#include "checkpoint.h"
#include <QVector>
#include <QObject>

/*!
 * It's a kind of layout. Creates and manages all checkpoint. You can create new checkpoint by invoke addCheckpoint()
 * with coordinates. CheckpointManager also add uniq id to each checkpoint. Delete checkpoint is not supported. If You want
 * to implement deleting checkpoint You need to reimplement virtual checkpointById(). All checkpoint are keeped in vector
 * and can be retreive by calling checkpointById. You can create new checkpoints in function createCheckpoints(). After destroy
 * checkpoint manager object every checkpoits will be deleted.
 */
class CheckpointManager: public QObject
{

    Q_OBJECT

public:
    /*!
     * @param x X checkpoint coordinate
     * @param y Y checkpoint coordinate
     * @param id Unique checkpoint number
     * @param flags Sets flags to checkpoint
     *
     * Adds new created checkpoints to m_checkpointVector and return new reated checkpoint.
     */
    Checkpoint* addCheckpoint( qreal x, qreal y, uint id , uint flags );
    /*!
     * @param id Unique checkpoint number
     *
     * Returns pointer to checkpoint with appropriate id.
     */
    virtual const Checkpoint* checkpointByIdConst( uint id ) const;
    virtual Checkpoint* checkpointById( uint id ) const;
    /*!
     * Returns checkpoints count.
     */
    uint checkpointsCount() const;

protected:
    CheckpointManager();
    ~CheckpointManager();

    QVector<Checkpoint*> m_checkpointVector;

    friend class GraphicsView;

signals:
    void checkpointReached( uint flags );
};

#endif // CHECKPOINTMANAGER_H
