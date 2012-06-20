#include "database.h"
#include <QSqlDatabase>
#include <QDir>
#include <QVariant>
#include <QSqlError>
#include <QSqlQuery>


Database::Database():
    m_databaseName( QDir::currentPath() + "/statistic.db3" ),
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

const QStringList Database::loadVehicleCountOnJunctions() const
{
    QSqlQuery query;
    query.prepare( "SELECT statisticTime, vehicleCount, junctionId FROM Statistic WHERE experimentId = :experimentId ORDER BY statisticTime" );
    query.bindValue( ":experimentId", m_experimentId );
    query.exec();

    QStringList resultList;
    QString line;
    int currentJunctionId = 0;

    line = " 0 1 2 3 4 5 6";
    resultList << line;
    line.clear();

    while( query.next() )
    {
        currentJunctionId = query.value( 2 ).toInt();
        line += ( " " + query.value( 1 ).toString() );

        if( currentJunctionId == 6 )
        {
            resultList << ( query.value( 0 ).toString() + line );
            line.clear();
        }
    }

    return resultList;
}

const QStringList Database::loadVehicleWaitingTimeOnJunctions() const
{
    QSqlQuery query;
    query.prepare( "SELECT statisticTime, vehicleWaitingTime, junctionId FROM Statistic WHERE experimentId = :experimentId ORDER BY statisticTime" );
    query.bindValue( ":experimentId", m_experimentId );
    query.exec();

    QStringList resultList;
    QString line;
    int currentJunctionId = 0;

    line = " 0 1 2 3 4 5 6";
    resultList << line;
    line.clear();

    while( query.next() )
    {
        currentJunctionId = query.value( 2 ).toInt();
        line += ( " " + query.value( 1 ).toString() );

        if( currentJunctionId == 6 )
        {
            resultList << ( query.value( 0 ).toString() + line );
            line.clear();
        }
    }

    return resultList;
}

const QStringList Database::loadWaitingTimeOnSubcyclesOnAppropriateJunction( int junctionId ) const
{
    QSqlQuery query;
    query.prepare( "SELECT statisticTime, Subcycle.vehicleWaitingTime, subcycleType FROM Subcycle, Statistic "
                   "WHERE  Statistic.experimentId = :experimentId AND "
                   "Statistic.statisticId = Subcycle.statisticId AND Statistic.junctionId = :junctionId "
                   "ORDER BY statisticTime" );
    query.bindValue( ":experimentId", m_experimentId );
    query.bindValue( ":junctionId", junctionId );
    query.exec();

    QStringList resultList;
    QString line;
    int currentSubcycle = 0;

    line = " 0 1 2 3";
    resultList << line;
    line.clear();

    int guard = 2;

    if( junctionId == 2 )
    {
        guard = 3;
    }

    while( query.next() )
    {
        currentSubcycle = query.value( 2 ).toInt();
        line += ( " " + query.value( 1 ).toString() );

        if( currentSubcycle == guard )
        {
            resultList << ( query.value( 0 ).toString() + line );
            line.clear();
        }
    }

    return resultList;
}

const QStringList Database::loadVehicleCountOnSubcyclesOnAppropriateJunction( int junctionId ) const
{
    QSqlQuery query;
    query.prepare( "SELECT statisticTime, Subcycle.vehicleCount, subcycleType FROM Subcycle, Statistic "
                   "WHERE  Statistic.experimentId = :experimentId AND "
                   "Statistic.statisticId = Subcycle.statisticId AND Statistic.junctionId = :junctionId "
                   "ORDER BY statisticTime" );
    query.bindValue( ":experimentId", m_experimentId );
    query.bindValue( ":junctionId", junctionId );
    query.exec();

    QStringList resultList;
    QString line;
    int currentSubcycle = 0;

    line = " 0 1 2 3";
    resultList << line;
    line.clear();

    int guard = 2;

    if( junctionId == 2 )
    {
        guard = 3;
    }

    while( query.next() )
    {
        currentSubcycle = query.value( 2 ).toInt();
        line += ( " " + query.value( 1 ).toString() );

        if( currentSubcycle == guard )
        {
            resultList << ( query.value( 0 ).toString() + line );
            line.clear();
        }
    }

    return resultList;
}

const QStringList Database::loadVehicleDrivedAwayCountOnJunctions() const
{
    QSqlQuery query;
    query.prepare( "SELECT statisticTime, vehicleDriveAwayCount, junctionId FROM Statistic WHERE experimentId = :experimentId ORDER BY statisticTime" );
    query.bindValue( ":experimentId", m_experimentId );
    query.exec();

    QStringList resultList;
    QString line;
    int currentJunctionId = 0;

    line = " 0 1 2 3 4 5 6";
    resultList << line;
    line.clear();

    while( query.next() )
    {
        currentJunctionId = query.value( 2 ).toInt();
        line += ( " " + query.value( 1 ).toString() );

        if( currentJunctionId == 6 )
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
