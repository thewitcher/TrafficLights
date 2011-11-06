#include <QtGui/QApplication>
#include "../Ui/Root_window/root-window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RootWindow w;
    w.show();

    return a.exec();
}
