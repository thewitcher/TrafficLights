#ifndef DATABASE_H
#define DATABASE_H

#include "../Ui/TrafficLights_manager/junction.h"
#include <QString>
#include <QSqlQuery>
#include <QDateTime>
#include <QThread>

class QSqlDatabase;

/*!
 * This class is responsible for access to database and operations on it. Becouse of some effort in writing and reading from
 * database it works in thread. You should be carefull in using this class. There are many function, that can be unsave in
 * some cases. If something doesn't work correctly then see logs to find the problem.
 */
class Database: public QThread
{
public:
    /*!
     * Constructor opens database and adds new experiment to it. New experiment is called with present date.
     */
    Database( const QVector<Junction*>& junctions );
    ~Database() {}

    /*!
     * For this time it just call databaseInstance() method;
     */
    void init();
    /*!
     * Removes database connection from list and closes the connection.
     */
    void close();
    /*!
     * Writes statistic about single junction into database.
     */
    void writeStatisticToDatabase( const Junction* junction );
    /*!
     * Calls writeStatisticToDatabase() method on all junctions. It starts new thred.
     */
    void run();

private:
    /*!
     * Full database name (with absolute path).
     */
    QString m_databaseName;
    /*!
     * Present date.
     */
    QDateTime m_currentDate;
    /*!
     * For each instance of application there is uniq experiment id. This variable keeps uniq value for this instance.
     * It is used to differentiate statistics data from one instance and other.
     */
    int m_currentExperimentId;
    /*!
     * Check m_isOpened value before you start use database. If it true, then database is available and ready to read/write. Otherwise
     * something went wrong. Logger can tell more about problem.
     */
    bool m_isOpened;
    /*!
     * Pointers to all junctions. They are used to save statistics from all junction in database.
     */
    QVector<Junction*> m_junctions;
    /*!
     * Each statistic have own time in order to see changes in time. It keeps current statistic time.
     */
    int m_statisticTime;

    /*!
     * Checks whether database is open or not. Checking is performed only when debug version is now running. It also returns
     * instance of database.
     */
    QSqlDatabase databaseInstance();
    /*!
     * Add new experiment into database.
     */
    void addNewExperiment();
    /*!
     * Check query for errors.
     */
    void errorHandling( QSqlQuery& query, const char * additionalComment );
};

#endif // DATABASE_H
