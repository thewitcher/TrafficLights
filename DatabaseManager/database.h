#ifndef DATABASE_H
#define DATABASE_H

#include "../Ui/TrafficLights_manager/junction.h"
#include <QString>
#include <QSqlQuery>
#include <QDateTime>
#include <QThread>

class QSqlDatabase;

class Database: public QThread
{
public:
    Database( const QVector<Junction*>& junctions );
    ~Database() {}

    void init();
    void close();
    void writeStatisticToDatabase( const Junction* junction );
    void run();

private:
    QString m_databaseName;
    QDateTime m_currentDate;
    int m_currentExperimentId;
    bool m_isOpened;
    QVector<Junction*> m_junctions;
    int m_statisticTime;

    QSqlDatabase databaseInstance();
    void addNewExperiment();
    void errorHandling( QSqlQuery& query );
};

#endif // DATABASE_H
