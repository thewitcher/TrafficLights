#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

/*!
 * @author Marcin Haber
 * This class is created for easy load and save application settings. It saves setings in Data directory.
 *
 * Consider implementing loadAllSettings() function to easy load some setting from any moment in application.
 */

class Settings: public QSettings
{
public:
    static Settings& settingsInstance();
    void loadAllSettings();

private:
    explicit Settings();
    ~Settings() {}

    static QString m_settingsPath;
};

#endif // SETTINGS_H
