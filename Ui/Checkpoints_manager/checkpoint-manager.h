#ifndef CHECKPOINTMANAGER_H
#define CHECKPOINTMANAGER_H

#include "checkpoint.h"
#include <QVector>

class CheckpointManager
{
public:
    static CheckpointManager& checkpointManagerInstance();

    void addCheckpoint( qreal x, qreal y );
    const Checkpoint* checkpointById( unsigned int id ) const;

private:
    CheckpointManager();
    ~CheckpointManager();

    QVector<Checkpoint*> m_checkpointVector;
};

#endif // CHECKPOINTMANAGER_H
