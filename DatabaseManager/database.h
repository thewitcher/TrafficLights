#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlQuery>
#include <QDateTime>

class QSqlDatabase;
class Junction;

class Database
{
public:
    static void init();
    static void close();
    static void writeStatisticToDatabase( const Junction* junction );

private:
    static QString S_DATABASE_NAME;
    static QDateTime S_CURRENT_DATE;
    static int S_CURRENT_EXPERIMENT_ID;

    static QSqlDatabase databaseInstance();
    static void addNewExperiment();
    static void errorHandling( QSqlQuery& query );

    Database() {}
    ~Database() {}
};

#endif // DATABASE_H
