#ifndef ROOTWINDOW_H
#define ROOTWINDOW_H

#include <QMainWindow>

namespace Ui {
    class RootWindow;
}

class RootWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RootWindow(QWidget *parent = 0);
    ~RootWindow();

private:
    Ui::RootWindow *ui;
};

#endif // ROOTWINDOW_H
