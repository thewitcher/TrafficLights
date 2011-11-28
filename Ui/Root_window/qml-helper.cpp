#include "qml-helper.h"
#include "../Logger/logger.h"
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>
#include <QGraphicsWidget>

QmlHelper::QmlHelper()
{
}

QGraphicsWidget* QmlHelper::createGraphicsWidgetFromQml( const QString &qmlName )
{
    LOG_INFO( "Qml with name %s will be created", qmlName.toLatin1().data() );

    if( qmlName.endsWith( ".qml" ) == true )
    {
        LOG_WARNING( "Your file name contains .qml, please give name without extension (you used: %s)", qmlName.toLatin1().data() );
    }

    QDeclarativeEngine engine;
    QDeclarativeComponent component( &engine, QUrl( "qrc:/qml/Qml/CarDesign.qml" ) );

    QGraphicsWidget* graphicsWidget = qobject_cast<QGraphicsWidget*>( component.create() );
    if( graphicsWidget == NULL )
    {
        LOG_WARNING( "Invalid casting. Qml element shoud be Vehicles element: %s", __FUNCTION__ );
    }
    else
    {
        graphicsWidget->setObjectName( qmlName );
    }

    return graphicsWidget;
}
