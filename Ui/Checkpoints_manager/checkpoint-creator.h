#ifndef CHECKPOINTCREATOR_H
#define CHECKPOINTCREATOR_H

#include <QString>
#include <QStringList>

class CheckpointManager;

/*!
 * @file vehicle.h
 *
 * @brief Creates checkpoint from file.
 *
 * @author Marcin Haber
 *
 * CheckpointCreator allows to create checkpoint from file. It is easy way to manage checkpoint from the text file. This is simple parser of .pos file.
 * It saves all created checkpoints to the manager.
 */
class CheckpointCreator
{
private:
    /*!
     * Creates all checkpoint and their paths and save the result into manager.
     *
     * @param fileName File with defined checkpoints. It should be in .pos format.
     * @param manager It is used to remeber created checkpoints.
     */
    CheckpointCreator( const QString& fileName, CheckpointManager *manager );

    /// File name with checkpoints description.
    const QString m_fileName;
    /// List of checkpoints (one row from file) - used to create single checkpoint.
    QStringList m_checkpointsList;
    /// If it is true then reading from file was succesfull. Otherwise something went wrong (for example there is no such file - see loger messages).
    bool m_valid;
    /// Manager to saves created checkpoint.
    CheckpointManager *m_manager;

    /*!
     * Reads all rows from file and saves it to m_checkpointsList.
     */
    void readAllLines();
    /*!
     * Uses m_checkpointsList to create all checkpoint and add them to manager.
     */
    void createCheckpoints();
    /*!
     * Creates paths for all checkpoints.
     */
    void createPaths();

    friend class CheckpointManager;
};

#endif // CHECKPOINTCREATOR_H
