#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>

class Database
{
public:
    Database();

    QStringList loadExperiments();
    const QStringList loadVehicleCountOnJunctions() const;
    const QStringList loadVehicleWaitingTimeOnJunctions() const;
    const QStringList loadWaitingTimeOnSubcyclesOnAppropriateJunction( int junctionId ) const;
    const QStringList loadVehicleCountOnSubcyclesOnAppropriateJunction( int junctionId ) const;
    const QString& databaseName() const;

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
