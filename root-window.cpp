#include "root-window.h"
#include "ui_root-window.h"

RootWindow::RootWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RootWindow)
{
    ui->setupUi(this);
}

RootWindow::~RootWindow()
{
    delete ui;
}
