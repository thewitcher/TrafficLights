#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>

class Database
{
public:
    enum LOAD_TYPE { VEHICLE_COUNT = 0, VEHICLE_WAITING_TIME, VEHICLE_DRIVED_AWAY, LOCAL_VEHICLE_COUNT = 3, LOCAL_VEHICLE_WAITING_TIME };

    Database();

    QStringList loadExperiments();
    const QStringList load( LOAD_TYPE loadType, int junctionId = -1 ) const;
    const QString& databaseName() const;

    void clearDatabase();

    void setExperimentId( int experimentId )
    {
        m_experimentId = experimentId;
    }

private:
    QString m_databaseName;
    bool m_isOpened;
    int m_experimentId;

    QSqlDatabase databaseInstance();
    void errorHandling( QSqlQuery& query );
};

#endif // DATABASE_H
