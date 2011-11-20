#include "style-loader.h"
#include "../../Logger/logger.h"
#include <QDir>
#include <QFile>

StyleLoader::StyleLoader()
{
}

StyleLoader& StyleLoader::styleLoaderInstance()
{
    static StyleLoader styleLoader;

    return styleLoader;
}

/*!
 * Adds new style to widget. Remember that there should exists file with widget name in appriopriate directory. It changes
 * style only for widget with widget->objectName() name.
 */
void StyleLoader::updateStyleSheetForName( QWidget *widget )
{
    //Try to find file in Build/Data/Qss directory
    LOG_INFO( "updateStyleSheet for widget with name: %s", widget->objectName().toLatin1().data() );
    QString dir = QDir::currentPath() + "/Data/Qss/" + widget->objectName() + ".qss";
    LOG_INFO( "Directory: %s", dir.toLatin1().data() );

    QFile qssFile( dir );
    LOG_INFO( "Is qss file opened: %i", qssFile.open( QIODevice::ReadOnly ) );

    widget->setStyleSheet( QString ( qssFile.readAll() ) );

    LOG_INFO( "Widget %s was styled", widget->objectName().toLatin1().data() );
}

/*!
 * Adds style to widget and his children with type type. Type can be like this:
 * QLabel
 * QPushButton
 * or something else which is known by application.
 */
void StyleLoader::updateStyleSheetForType( QWidget *widget, const QString &type )
{
    //Try to find file in Build/Data/Qss directory
    LOG_INFO( "updateStyleSheet for type: %s in %s or it's children", type.toLatin1().data(), widget->objectName().toLatin1().data() );
    QString dir = QDir::currentPath() + "/Data/Qss/" + type + ".qss";
    LOG_INFO( "Directory: %s", dir.toLatin1().data() );

    QFile qssFile( dir );
    LOG_INFO( "Is qss file opened: %i", qssFile.open( QIODevice::ReadOnly ) );

    widget->setStyleSheet( QString ( qssFile.readAll() ) );

    LOG_INFO( "Type %s was styled in %s or it's children", type.toLatin1().data(), widget->objectName().toLatin1().data() );
}
