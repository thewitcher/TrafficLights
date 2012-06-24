#include "database.h"
#include <QSqlDatabase>
#include <QDir>
#include <QVariant>
#include <QSqlError>
#include <QSqlQuery>


Database::Database():
    m_databaseName( QDir::currentPath() + "/Data/statistic.db3" ),
    m_isOpened( false ),
    m_experimentId( 0 )
{
    QSqlDatabase database = QSqlDatabase::addDatabase( "QSQLITE" );
    database.setDatabaseName( m_databaseName );
    m_isOpened = database.open();
}

QSqlDatabase Database::databaseInstance()
{
    Q_ASSERT( m_isOpened == true );

    return QSqlDatabase::database();
}

void Database::errorHandling( QSqlQuery &query )
{
    Q_ASSERT( query.exec() == true );
}

QStringList Database::loadExperiments()
{
    QStringList experimentsList;

    QSqlQuery query( "SELECT * FROM Experiment" );

    while( query.next() )
    {
        experimentsList << query.value( 0 ).toString() + ", Date " + query.value( 1 ).toString();
    }

    return experimentsList;
}

const QStringList Database::load( LOAD_TYPE loadType, int junctionId ) const
{
    QString queryString;

    QStringList resultList;
    QString line;
    int current = 0;
    int guard = 2;

    switch( loadType )
    {
    case VEHICLE_COUNT:
        queryString = "SELECT statisticTime, vehicleCount, junctionId FROM Statistic WHERE experimentId = :experimentId ORDER BY statisticTime";
        line = " 0 1 2 3 4 5 6";
        guard = 6;
        break;
    case VEHICLE_WAITING_TIME:
        queryString = "SELECT statisticTime, vehicleWaitingTime, junctionId FROM Statistic WHERE experimentId = :experimentId ORDER BY statisticTime";
        line = " 0 1 2 3 4 5 6";
        guard = 6;
        break;
    case VEHICLE_DRIVED_AWAY:
        queryString = "SELECT statisticTime, vehicleDriveAwayCount, junctionId FROM Statistic WHERE experimentId = :experimentId ORDER BY statisticTime";
        line = " 0 1 2 3 4 5 6";
        guard = 6;
        break;
    case LOCAL_VEHICLE_COUNT:
        queryString = "SELECT statisticTime, Subcycle.vehicleCount, subcycleType FROM Subcycle, Statistic "
                "WHERE  Statistic.experimentId = :experimentId AND "
                "Statistic.statisticId = Subcycle.statisticId AND Statistic.junctionId = :junctionId "
                "ORDER BY statisticTime";
        line = " 0 1 2 3";
        break;
    case LOCAL_VEHICLE_WAITING_TIME:
        queryString = "SELECT statisticTime, Subcycle.vehicleWaitingTime, subcycleType FROM Subcycle, Statistic "
                "WHERE  Statistic.experimentId = :experimentId AND "
                "Statistic.statisticId = Subcycle.statisticId AND Statistic.junctionId = :junctionId "
                "ORDER BY statisticTime";
        line = " 0 1 2 3";
        break;
    }

    QSqlQuery query;
    query.prepare( queryString );
    query.bindValue( ":experimentId", m_experimentId );

    resultList << line;
    line.clear();

    if( junctionId  > -1 )
    {
        query.bindValue( ":junctionId", junctionId );

        int guard = 2;

        if( junctionId == 2 )
        {
            guard = 3;
        }
    }

    query.exec();

    while( query.next() )
    {
        current = query.value( 2 ).toInt();
        line += ( " " + query.value( 1 ).toString() );

        if( current == guard )
        {
            resultList << ( query.value( 0 ).toString() + line );
            line.clear();
        }
    }

    return resultList;
}

const QString& Database::databaseName() const
{
    return m_databaseName;
}

void Database::clearDatabase()
{
    QSqlQuery query;
    query.exec( "DROP TABLE IF EXISTS Experiment" );
    query.exec( "DROP TABLE IF EXISTS Junction" );
    query.exec( "DROP TABLE IF EXISTS Subcycle" );
    query.exec( "DROP TABLE IF EXISTS Statistic" );

    query.exec( "CREATE TABLE Junction ( junctionId integer primary key, junctionType text )" );

    query.exec( "CREATE TABLE Statistic ( "
                "statisticId           integer primary key, "
                "junctionId            integer NOT NULL, "
                "experimentId          integer NOT NULL, "
                "statisticTime         integer NOT NULL, "
                "vehicleCount          integer, "
                "vehicleWaitingTime    integer, "
                "vehicleDriveAwayCount integer, "
                "CONSTRAINT ExperimentFK FOREIGN KEY( experimentId ) REFERENCES Experiment( experimentId ), "
                "CONSTRAINT JunctionFK FOREIGN KEY( junctionId ) REFERENCES Junction( junctionId ) )" );

    query.exec( "CREATE TABLE Subcycle ( "
                "subcycleId           integer primary key, "
                "statisticId          integer NOT NULL, "
                "subcycleType         integer NOT NULL, "
                "vehicleCount         integer, "
                "vehicleWaitingTime   integer, "
                "CONSTRAINT StatisticFK FOREIGN KEY( statisticId ) REFERENCES Statistic( statisticId ) )" );

    query.exec( "CREATE TABLE Experiment ( "
                "experimentId         integer primary key, "
                "experimentDate       text )" );


    query.exec( "INSERT INTO Junction( junctionType ) VALUES( 'SimpleJunction' )" );
    query.exec( "INSERT INTO Junction( junctionType ) VALUES( 'SimpleJunction' )" );
    query.exec( "INSERT INTO Junction( junctionType ) VALUES( 'BladzioJunction' )" );
    query.exec( "INSERT INTO Junction( junctionType ) VALUES( 'SimpleJunction' )" );
    query.exec( "INSERT INTO Junction( junctionType ) VALUES( 'SimpleJunction' )" );
    query.exec( "INSERT INTO Junction( junctionType ) VALUES( 'SimpleJunction' )" );
    query.exec( "INSERT INTO Junction( junctionType ) VALUES( 'SimpleJunction' )" );
}
