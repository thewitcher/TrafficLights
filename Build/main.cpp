#include <QtGui/QApplication>
#include <QtDeclarative>
#include "../Ui/Root_window/root-window.h"
#include "../Logger/logger.h"
#include "../Settings/settings.h"
#include "../Ui/Cars/vehicle.h"
#include "../Ui/Cars/mycars.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //It is neccessary to open file to writes logs
    Logger::init();

    //Register type
    qmlRegisterType<Vehicle>( "Vehicles", 1, 0, "Vehicles" );
    qmlRegisterType<MyCars> ("Cars", 1, 0, "MyCars");

    RootWindow w;
    w.show();

    return a.exec();
}
