#ifndef CHECKPOINTMANAGER_H
#define CHECKPOINTMANAGER_H

#include "checkpoint.h"
#include <QVector>

/*!
 * It's a kind of layout. Creates and manages all checkpoint. You can create new checkpoint by invoke addCheckpoint()
 * with coordinates. CheckpointManager also add uniq id to each checkpoint. Delete checkpoint is not supported. If You want
 * to implement deleting checkpoint You need to reimplement virtual checkpointById(). All checkpoint are keeped in vector
 * and can be retreive by calling checkpointById. You can create new checkpoints in function createCheckpoints(). After destroy
 * checkpoint manager object every checkpoits will be deleted.
 */
class CheckpointManager
{
public:
    Checkpoint* addCheckpoint( qreal x, qreal y, unsigned int id );
    virtual const Checkpoint* checkpointByIdConst( unsigned int id ) const;
    virtual Checkpoint* checkpointById( unsigned int id ) const;
    unsigned int checkpointsCount() const;

protected:
    CheckpointManager();
    ~CheckpointManager();

    QVector<Checkpoint*> m_checkpointVector;

    friend class GraphicsView;
};

#endif // CHECKPOINTMANAGER_H
