#include "settings.h"
#include "../Logger/logger.h"
#include <QDir>

QString Settings::m_settingsPath = QDir::currentPath() + "/Data/settings.ini";

Settings::Settings():
    QSettings( m_settingsPath, QSettings::IniFormat )
{
    QDir dir = QDir::currentPath();

    if( dir.cd("/Data") == false)
    {
        bool ok = dir.mkdir("Data");
        LOG_INFO("Data catalog was created: %i", ok);
    }
}

Settings& Settings::settingsInstance()
{
    static Settings settings;

    return settings;
}

void Settings::loadAllSettings()
{
    // It loads every settings needed on start up application. It will be implemented later.
}
