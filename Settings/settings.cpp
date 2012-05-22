#include "settings.h"
#include "../Logger/logger.h"
#include <QDir>
#include <QSettings>

QString Settings::S_SETTINGS_PATH = QDir::currentPath() + "/Data/settings.ini";


QVariant Settings::takeValue( const QString &key, const QString &groupName, const QVariant &defaultValue )
{
    QSettings settings( S_SETTINGS_PATH, QSettings::IniFormat );
    settings.beginGroup( groupName );
    QVariant value = settings.value( key, defaultValue );
    settings.endGroup();

    return value;
}

void Settings::setValues( const QString &key, const QString &groupName, const QString& value )
{
    QSettings settings( S_SETTINGS_PATH, QSettings::IniFormat );
    settings.beginGroup( groupName );
    settings.setValue( key, value );
    settings.endGroup();
}
