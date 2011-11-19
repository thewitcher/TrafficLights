#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QFile>

/*!
 * @author Marcin Haber
 * This class allows you to create logs in text file. Use macrodefinitions to write your logs. There is short manual which can help
 * in using Logger class.
 *
 * Manual:
 * First of all you need to define LOGGER macro in your project in order to have posibility to use Logger. It should be done in
 * pro file to avoid adding it in every file. Just add:
 * #DEFINES += LOGGER into pro file. After this you can use LOG_INFO(), LOG_WARNING() and LOG_CRITICAL() to save your logs.
 *
 * Logger has to be initialised. You can invoke Login::init() static method to do it.
 *
 * All of macros are enabled when LOGGER macro is defined. You can use it in this way:
 * -> give string with text you want to write to file. This string can contain optional embedded format tags which can be substituted
 * by the values in subsequent arguments. This works like sprintf function in C++ standard, so I send you to:
 * http://www.cplusplus.com/reference/clibrary/cstdio/sprintf/
 * for more informations.
 *
 * I show you how to creates basic logs. I suppose that this informations will be suffice for you.
 *
 * Example:
 * -> you can write LOG_INFO("There is %i elements in the list", 3); into function functionName, in 3 line and in loggerName file.
 * You will see in log file this:
 * [Info] There is 3 elements in the list
 *
 * The number of arguments following the format parameters should at least be as much as the number of format tags.
 *
 * Some of format paramaters you can use (for more read sprintf documentation):
 * - %i - integer
 * - %c - char
 * - %s - string
 * - %p - pointer address
 *
 * You can use also other option in info string like precision, width, flags, length. These options are descrbed in sprintf documentation.
 *
 * To get information about function name, line and file name use: __FILE__, __LINE__ and __FUNCTION__ macros as arguments. Remember
 * about appropriate type of this macros.
 */

class Logger
{
public:
    static void init();
    static void writeInfo( const QString& info );
    static void writeCritical( const QString& info );
    static void writeWarning( const QString& info );

private:
    static QString m_loggerPath;
    static QFile m_logger;

    Logger();
    ~Logger();
};

#define LOG_INFO(info,...); \
    { \
        QString formatString; \
        Logger::writeInfo(formatString.sprintf(info,__VA_ARGS__)); \
    }
#define LOG_CRITICAL(info,...); \
    { \
        QString formatString; \
        Logger::writeCritical(formatString.sprintf(info,__VA_ARGS__)); \
    }
#define LOG_WARNING(info,...); \
    { \
        QString formatString; \
        Logger::writeWarning(formatString.sprintf(info,__VA_ARGS__)); \
    }

#endif // LOGGER_H
