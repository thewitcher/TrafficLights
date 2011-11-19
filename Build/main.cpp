#include <QtGui/QApplication>
#include "../Ui/Root_window/root-window.h"
#include "../Logger/logger.h"
#include "../Settings/settings.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //It is neccessary to open file to writes logs
    Logger::init();

    RootWindow w;
    w.show();

    return a.exec();
}
