#include "root-window.h"
#include "ui_root-window.h"
#include "../Logger/logger.h"
#include "../QSSEngine/style-loader.h"

#include <QGLWidget>

RootWindow::RootWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RootWindow)
{
    ui->setupUi(this);

    initGraphicsView();
}

RootWindow::~RootWindow()
{
    delete ui;
}

void RootWindow::initGraphicsView()
{
    LOG_INFO( "Start: %s", __FUNCTION__ );

    QGLWidget *viewportWidget = new QGLWidget( ui->m_graphicsView );
    ui->m_graphicsView->setViewport( viewportWidget );
    ui->m_graphicsView->show();

    LOG_INFO( "End: %s", __FUNCTION__ );
}
