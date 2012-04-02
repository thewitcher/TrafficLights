#ifndef QMLHELPER_H
#define QMLHELPER_H

#include <QString>

/*!
 * This is helper class for creating various type object from qml. Just use apprioriate function to create what you want.
 * Remember that you have to free space if you dont't need created object. It creates object but doesn't take ownership.
 */
class Vehicle;
class TrafficLight;
class QDeclarativeEngine;

class QmlHelper
{
public:
    static Vehicle* createVehicleFromQml( const QString& qmlName );
    static TrafficLight* createLightsFromQml( const QString& qmlName );

private:
    QmlHelper();
    ~QmlHelper() {}

    static QDeclarativeEngine* initDeclarativeEngine();
};

#endif // QMLHELPER_H
