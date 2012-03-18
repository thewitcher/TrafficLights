#include "qml-helper.h"
#include "../Logger/logger.h"
#include "../Cars/vehicle.h"
#include "../Lights/trafficlight.h"
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>

QDeclarativeEngine* QmlHelper::s_engine = new QDeclarativeEngine();

QmlHelper::QmlHelper()
{
}

Vehicle* QmlHelper::createVehicleFromQml( const QString &qmlName )
{
    LOG_INFO( "Qml with name %s will be created", qmlName.toLatin1().data() );

    if( qmlName.endsWith( ".qml" ) == true )
    {
        LOG_WARNING( "Your file name contains .qml, please give name without extension (you used: %s)", qmlName.toLatin1().data() );
    }

    QDeclarativeComponent component( s_engine, QUrl( "qrc:/qml/Qml/Car/" + qmlName + ".qml" ) );

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

TrafficLight* QmlHelper::createLightsFromQml( const QString &qmlName )
{
    LOG_INFO( "Qml with name %s will be created", qmlName.toLatin1().data() );

    if( qmlName.endsWith( ".qml" ) == true )
    {
        LOG_WARNING( "Your file name contains .qml, please give name without extension (you used: %s)",qmlName.toLatin1().data() );
    }

    QDeclarativeComponent component( s_engine, QUrl( "qrc:/qml/Qml/Lights/" + qmlName + ".qml") );

    TrafficLight * light = qobject_cast<TrafficLight*>( component.create() );
    if( light == NULL )
    {
        LOG_WARNING( "Invalid casting. Qml element shoud be TrafficLight element: %s", __FUNCTION__ );
    }
    else
    {
        light->setObjectName( qmlName );
    }

    return light;
}
