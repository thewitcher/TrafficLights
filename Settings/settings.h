#ifndef SETTINGS_H
#define SETTINGS_H

/*!
 * @author Marcin Haber
 * This class is created for easy load and save application settings. It saves setings in Data directory.
 *
 * Consider implementing loadAllSettings() function to easy load some setting from any moment in application.
 */

#include <QVariant>

class Settings
{
public:
    static QVariant takeValue( const QString& key, const QString& groupName, const QVariant& defaultValue = QVariant() );
    static void setValues( const QString& key, const QString& groupName, const QString& value );
private:
    explicit Settings() {}
    ~Settings() {}

    static QString S_SETTINGS_PATH;
};

#endif // SETTINGS_H
