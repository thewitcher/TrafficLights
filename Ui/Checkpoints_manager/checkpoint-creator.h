#ifndef CHECKPOINTCREATOR_H
#define CHECKPOINTCREATOR_H

#include <QString>
#include <QStringList>

class CheckpointManager;

class CheckpointCreator
{
public:
    CheckpointCreator( const QString& fileName, CheckpointManager *manager );

private:
    const QString m_fileName;
    QStringList m_checkpointsList;
    bool m_valid;
    CheckpointManager *m_manager;

    void readAllLines();
    void createCheckpoints();
    void createPaths();

    friend class CheckpointManager;
};

#endif // CHECKPOINTCREATOR_H
