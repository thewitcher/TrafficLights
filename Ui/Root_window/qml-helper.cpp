#include "qml-helper.h"
#include "../Logger/logger.h"
#include "../Cars/vehicle.h"
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>

QmlHelper::QmlHelper()
{
}

Vehicle* QmlHelper::createVehicleFromQml( const QString &qmlName )
{
    static QDeclarativeEngine *engine = new QDeclarativeEngine();

    LOG_INFO( "Qml with name %s will be created", qmlName.toLatin1().data() );

    if( qmlName.endsWith( ".qml" ) == true )
    {
        LOG_WARNING( "Your file name contains .qml, please give name without extension (you used: %s)", qmlName.toLatin1().data() );
    }

    QDeclarativeComponent component( engine, QUrl( "qrc:/qml/Qml/" + qmlName + ".qml" ) );

    Vehicle *vehicle = qobject_cast<Vehicle*>( component.create() );
    if( vehicle == NULL )
    {
        LOG_WARNING( "Invalid casting. Qml element shoud be Vehicles element: %s", __FUNCTION__ );
    }
    else
    {
        vehicle->setObjectName( qmlName );
    }

    return vehicle;
}
