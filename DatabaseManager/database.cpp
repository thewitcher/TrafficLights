#include "database.h"
#include "../Logger/logger.h"
#include "../Ui/TrafficLights_manager/vehicle-count-manager.h"
#include <QSqlDatabase>
#include <QDir>
#include <QVariant>
#include <QSqlError>

Database::Database( const QVector<Junction *> &junctions ):
    QThread( NULL ),
    m_databaseName( QDir::currentPath() + "/Data/statistic.db3" ),
    m_currentDate( QDateTime::currentDateTime() ),
    m_currentExperimentId( 0 ),
    m_isOpened( false ),
    m_junctions( junctions ),
    m_statisticTime( 0 )
{
    QSqlDatabase database = QSqlDatabase::addDatabase( "QSQLITE" );
    database.setDatabaseName( m_databaseName );
    m_isOpened = database.open();

    if( m_isOpened == true )
    {
        LOG_INFO( "Database was opened (%s)", __FUNCTION__ );
    }
    else
    {
        LOG_INFO( "Database not available. Check whether database file exists (%s)", __FUNCTION__ );
    }

    addNewExperiment();
}

QSqlDatabase Database::databaseInstance()
{
    Q_ASSERT( m_isOpened == true );

    LOG_INFO( "Database is not open (%s)", __FUNCTION__ )
    return QSqlDatabase::database();
}

void Database::close()
{
    databaseInstance().removeDatabase( databaseInstance().databaseName() );
    databaseInstance().close();

    LOG_INFO( "Close database connection (%s)", __FUNCTION__ )
}

void Database::addNewExperiment()
{
    QSqlQuery query;
    query.prepare( "INSERT INTO Experiment( experimentDate ) VALUES( :experimentDate )" );
    query.bindValue( ":experimentDate", m_currentDate.toString( "MM-dd-yyyy ( hh:mm:ss )" ) );

    errorHandling( query, "Insert into Experiment table can not be performed" );

    query.clear();

    query.exec( "SELECT MAX( experimentId ) FROM Experiment" );
    query.next();
    m_currentExperimentId = query.value( 0 ).toInt();

    errorHandling( query, "Read MAX from statistic table can not be performed" );

    LOG_INFO( "Add new experiment into database with date: %s", m_currentDate.toString( "MM-dd-yyyy ( hh:mm:ss )" ).toAscii().data() )
}

void Database::errorHandling( QSqlQuery &query, const char *additionalComment )
{
    if( !query.exec() )
    {
        LOG_WARNING( "Error: %s", query.lastError().text().toAscii().data() );
        LOG_WARNING( "Additional comment for error: %s", additionalComment );
    }
}

void Database::init()
{
    databaseInstance();
}

void Database::writeStatisticToDatabase( const Junction *junction )
{
    QSqlQuery query;
    query.exec( "SELECT MAX( statisticId ) FROM Statistic" );
    query.next();
    int statisticId = query.value( 0 ).toInt() + 1;

    errorHandling( query, "Read MAX from statistic table can not be performed" );

    query.clear();

    query.prepare( "INSERT INTO Statistic( junctionId, experimentId, statisticTime, vehicleCount, vehicleWaitingTime, vehicleDriveAwayCount )"
                   "VALUES( :junctionId, :experimentId, :statisticTime, :vehicleCount, :vehicleWaitingTime, :vehicleDriveAwayCount )" );
    query.bindValue( ":junctionId", junction->id() );
    query.bindValue( ":experimentId", m_currentExperimentId );
    query.bindValue( ":statisticTime", m_statisticTime );
    query.bindValue( ":vehicleCount", VehicleCountManager::sumVehiclesAtJunction( junction ) );
    query.bindValue( ":vehicleWaitingTime", VehicleCountManager::sumVehiclesWaitingTimeAtJunction( junction ) );
    query.bindValue( ":vehicleDriveAwayCount", junction->getAndClearVehicleDriveAwayCount() );

    errorHandling( query, "Insert into statistic table can not be performed" );

    query.clear();

    QList<VehicleCountManager::SubCycle> list;

    if( junction->junctionType() == Junction::BLADZIO )
    {
        list << VehicleCountManager::SUBCYCLE_0
             << VehicleCountManager::SUBCYCLE_1
             << VehicleCountManager::SUBCYCLE_2
             << VehicleCountManager::SUBCYCLE_3;
    }
    else
    {
        list << VehicleCountManager::SUBCYCLE_0
             << VehicleCountManager::SUBCYCLE_1
             << VehicleCountManager::SUBCYCLE_2;
    }


    for( int i = 0 ; i < list.count() ; i++ )
    {
        query.prepare( "INSERT INTO Subcycle( statisticId, subcycleType, vehicleCount, vehicleWaitingTime )"
                       "VALUES( :statisticId, :subcycleType, :vehicleCount, :vehicleWaitingTime )" );
        query.bindValue( ":statisticId", statisticId );
        query.bindValue( ":subcycleType", i );
        query.bindValue( ":vehicleCount", VehicleCountManager::vehicleCountOnSubcycle( junction, list.at( i ) ) );
        query.bindValue( ":vehicleWaitingTime", VehicleCountManager::wholeVehicleWaitingTimeForSubcycle( junction, list.at( i ) ) );

        errorHandling( query, "Insert into Subcycle table can not be performed" );
    }
}

void Database::run()
{
    m_statisticTime = m_currentDate.secsTo( QDateTime::currentDateTime() );

    for( int i = 0 ; i < m_junctions.count() ; i++ )
    {
        writeStatisticToDatabase( m_junctions.at( i ) );
    }
}
