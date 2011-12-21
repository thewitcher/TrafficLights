#include "logger.h"
#include <QDir>
#include <QTextStream>
#include <QTime>

QString Logger::m_loggerPath = QDir::currentPath() + "/Data/user_logger.txt";
QFile Logger::m_logger( Logger::m_loggerPath );

Logger::Logger()
{
    // There is no need to implement any constructor. Everything has done in macro.
}

void Logger::init()
{
    QDir dir = QDir::currentPath();

    if( dir.cd("/Data") == false)
    {
        dir.mkdir("Data");
    }

    m_logger.open( QIODevice::ReadWrite | QIODevice::Append );
}

Logger::~Logger()
{
    // File will be closed by his destructor.
}

void Logger::writeInfo( const QString &info )
{
#ifdef LOGGER
    QTextStream writer( &m_logger );
    writer << "[INFO: time( " + QTime::currentTime().toString( "hh:mm" ) + " )] " << info << "\n";
#else
    Q_UNUSED(info);
#endif
}

void Logger::writeCritical( const QString &info )
{
#ifdef LOGGER
    QTextStream writer( &m_logger );
    writer << "[CRITICAL: time( " + QTime::currentTime().toString( "hh:mm" ) + " )] " << info << "\n";
#else
    Q_UNUSED(info);
#endif
}

void Logger::writeWarning( const QString &info )
{
#ifdef LOGGER
    QTextStream writer( &m_logger );
    writer << "[WARNING: time( " + QTime::currentTime().toString( "hh:mm" ) + " )] " << info << "\n";
#else
    Q_UNUSED(info);
#endif
}
