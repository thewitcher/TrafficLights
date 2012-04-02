#include <QtGui/QApplication>
#include <QtDeclarative>
#include "../Ui/Root_window/root-window.h"
#include "../Logger/logger.h"
#include "../Settings/settings.h"
#include "../Ui/Cars/motor-car.h"
#include "../Ui/Lights/trafficlight.h"
#include "../Ui/Cars/bus-car.h"
#include "../Logic/Genetic_algorithm/GA/genetic-algorithm-manager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //It is neccessary to open file to writes logs
    Logger::init();

    //Register type
//    qmlRegisterType<MotorCar> ( "Cars", 1, 0, "MotorCar" );
//    qmlRegisterType<BusCar> ( "Cars", 1, 0, "BusCar" );
//    qmlRegisterType<TrafficLight> ( "LightsPacket", 1, 0, "Light" );

//    RootWindow w;
//    w.show();

    GeneticAlgorithmManager geneticAlgorithmManager;

    Q_UNUSED( geneticAlgorithmManager );

    return a.exec();
}
