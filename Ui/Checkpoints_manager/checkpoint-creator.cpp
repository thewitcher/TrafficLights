#include "checkpoint-creator.h"
#include "checkpoint-manager.h"
#include "../Logger/logger.h"
#include <QFile>
#include <QTextStream>
#include <QDir>

/*!
 * ##############################################################################
 * ## WARNING!!!! Every checkpoints have to be in correct order: from 0 to n.  ##
 * ##############################################################################
 *
 * File .pos should be in this format:
 * <checkpoint id>;<x coordinate>,<y coordinate>;<targets checkpoint list>;<move type>;
 *
 * Move types:
 * ya - ahead with y
 * xa - ahead with x
 * xl - left with x
 * yl - left with y
 * xr - right with x
 * yr - right with y
 * wxy - west with x and y
 * exy - east with x and y
 * sxy - south with x and y
 * nxy - north with x and y
 *
 * EXAMPLE:
 *
 * 18;203,67;27,33,59,69,81;ax;19;ry;
 *
 * It means that from checkpoint with id 18 You can go to checkpoints 27, 33, 59, 81 changing only x coordinate and movig ahead. But You can also travelling
 * to checkpoint with 19 id if You go to right by y coordinate. Checkpoint with id 18 is positioning on (203,67) in the scene.
 */
CheckpointCreator::CheckpointCreator( const QString &fileName, CheckpointManager *manager ):
    m_fileName( fileName ),
    m_valid( false ),
    m_manager( manager )
{
    readAllLines();

    createCheckpoints();
    createPaths();
}

void CheckpointCreator::readAllLines()
{
    QFile file( QDir::currentPath() + "/Data/" + m_fileName );

    if( file.open( QIODevice::ReadOnly ) )
    {
        LOG_INFO( "%s was opened", m_fileName.toLatin1().data() );
        m_valid = true;

        QTextStream reader( &file );

        m_checkpointsList.clear();

        QString line;

        while( QString( line = reader.readLine() ).isEmpty() == false )
        {
            m_checkpointsList << line;

            LOG_INFO( "Added new line with checkpoint parameters: %s", line.toLatin1().data() );
        }
    }
    else
    {
        LOG_INFO( "%s was not opened", m_fileName.toLatin1().data() );
        m_valid = false;
    }
}

void CheckpointCreator::createCheckpoints()
{
    if( m_valid )
    {
        QStringList splitedLine;
        QStringList coordinates;

        for( int i = 0 ; i < m_checkpointsList.count() ; i++)
        {
            splitedLine = m_checkpointsList.at( i ).split( ";" );
            coordinates = splitedLine.at( 2 ).split( "," );

            m_manager->addCheckpoint( coordinates.at( 0 ).toDouble(), coordinates.at( 1 ).toDouble(),
                                      splitedLine.at( 1 ).toUInt(), splitedLine.at( 0 ).toUInt() );
        }
    }
    else
    {
        LOG_WARNING( "Checkpoints are not created (%s)", __FUNCTION__ );
    }
}

void CheckpointCreator::createPaths()
{
    if( m_valid )
    {
        QStringList splitedLine;
        Checkpoint *checkpoint;
        QStringList firstTargets;
        QVector< Checkpoint* > firstTargetsVector;
        QStringList secondTargets;
        QVector< Checkpoint* > secondTargetsVector;

        for( uint i = 0 ; i < m_manager->checkpointsCount() ; i++ )
        {
            // Clear
            firstTargets.clear();
            firstTargetsVector.clear();
            secondTargets.clear();
            secondTargetsVector.clear();

            checkpoint = m_manager->checkpointById( i );
            splitedLine = m_checkpointsList.at( i ).split( ";" );

            // Checks ids
            Q_ASSERT( i == splitedLine.at( 1 ).toUInt() );

            // Creates targets checkpoints list
            if( splitedLine.count() == 5 )
            {
                firstTargets = splitedLine.at( 3 ).split( "," );

                for( unsigned char k = 0 ; k < firstTargets.count() ; k++ )
                {
                    firstTargetsVector << m_manager->checkpointById( firstTargets.at( k ).toUInt() );
                }

                checkpoint->addMove( firstTargetsVector, splitedLine.at( 4 ) );
            }
            else if( splitedLine.count() == 7 )
            {
                firstTargets = splitedLine.at( 3 ).split( "," );
                secondTargets = splitedLine.at( 5 ).split( "," );

                for( unsigned char k = 0 ; k < firstTargets.count() ; k++ )
                {
                    firstTargetsVector << m_manager->checkpointById( firstTargets.at( k ).toUInt() );
                }
                for( unsigned char k = 0 ; k < secondTargets.count() ; k++ )
                {
                    secondTargetsVector << m_manager->checkpointById( secondTargets.at( k ).toUInt() );
                }

                checkpoint->addMove( firstTargetsVector, splitedLine.at( 4 ) );
                checkpoint->addMove( secondTargetsVector, splitedLine.at( 6 ) );
            }
            else
            {
                LOG_WARNING( "Invalid data in: %s for %i", __FUNCTION__, i );
            }
        }
    }
    else
    {
        LOG_WARNING( "Checkpoints are not created (%s)", __FUNCTION__ );
    }
}
