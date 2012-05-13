#include "database.h"
#include "../Logger/logger.h"
#include "../Ui/TrafficLights_manager/junction.h"
#include "../Ui/TrafficLights_manager/vehicle-count-manager.h"
#include <QSqlDatabase>
#include <QDir>
#include <QVariant>
#include <QSqlError>

QString Database::S_DATABASE_NAME = QDir::currentPath() + "/Data/statistic.db3";
QDateTime Database::S_CURRENT_DATE = QDateTime::currentDateTime();
int Database::S_CURRENT_EXPERIMENT_ID = 0;


QSqlDatabase Database::databaseInstance()
{
    static bool open = false;

    if( open == false )
    {
        QSqlDatabase database = QSqlDatabase::addDatabase( "QSQLITE" );
        database.setDatabaseName( S_DATABASE_NAME );
        open = database.open();

        Q_ASSERT( open == true );

        addNewExperiment();
    }

    return QSqlDatabase::database();
}

void Database::close()
{
    databaseInstance().removeDatabase( databaseInstance().databaseName() );
    databaseInstance().close();
}

void Database::addNewExperiment()
{
    QSqlQuery query;
    query.prepare( "INSERT INTO Experiment( experimentDate ) VALUES( :experimentDate )" );
    query.bindValue( ":experimentDate", S_CURRENT_DATE.toString( "MM-dd-yyyy ( hh:mm:ss )" ) );

    errorHandling( query );

    query.clear();

    query.exec( "SELECT MAX( experimentId ) FROM Experiment" );
    query.next();
    S_CURRENT_EXPERIMENT_ID = query.value( 0 ).toInt();

    errorHandling( query );
}

void Database::errorHandling( QSqlQuery &query )
{
    if( !query.exec() )
    {
        LOG_WARNING( "Error: %s", query.lastError().text().toAscii().data() );
    }
}

void Database::init()
{
    databaseInstance();
}

void Database::writeStatisticToDatabase( const Junction *junction )
{
    QSqlQuery query;
    query.exec( "SELECT MAX( experimentId ) FROM Experiment" );
    query.next();
    int statisticId = query.value( 0 ).toInt() + 1;

    errorHandling( query );

    query.clear();

    query.prepare( "INSERT INTO Statistic( junctionId, experimentId, statisticTime, vehicleCount, vehicleWaitingTime )"
                   "VALUES( :junctionId, :experimentId, :statisticTime, :vehicleCount, :vehicleWaitingTime )" );
    query.bindValue( ":junctionId", junction->id() );
    query.bindValue( ":experimentId", S_CURRENT_EXPERIMENT_ID );
    query.bindValue( ":statisticTime", S_CURRENT_DATE.secsTo( QDateTime::currentDateTime() ) );
    query.bindValue( ":vehicleCount", VehicleCountManager::sumVehiclesAtJunction( junction ) );
    query.bindValue( ":vehicleWaitingTime", VehicleCountManager::sumVehiclesWaitingTimeAtJunction( junction ) );

    errorHandling( query );

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
        query.bindValue( ":subcycleType", list.at( i ) );
        query.bindValue( ":vehicleCount", VehicleCountManager::vehicleCountOnSubcycle( junction, list.at( i ) ) );
        query.bindValue( ":vehicleWaitingTime", VehicleCountManager::wholeVehicleWaitingTimeForSubcycle( junction, list.at( i ) ) );

        errorHandling( query );
    }
}
