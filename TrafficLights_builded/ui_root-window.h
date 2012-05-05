/********************************************************************************
** Form generated from reading UI file 'root-window.ui'
**
** Created: Sat May 5 19:53:38 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROOT_2D_WINDOW_H
#define UI_ROOT_2D_WINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include "../../TrafficLights/Ui/Root_window/graphics-view.h"

QT_BEGIN_NAMESPACE

class Ui_RootWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    GraphicsView *m_graphicsView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RootWindow)
    {
        if (RootWindow->objectName().isEmpty())
            RootWindow->setObjectName(QString::fromUtf8("RootWindow"));
        RootWindow->resize(715, 463);
        centralWidget = new QWidget(RootWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_graphicsView = new GraphicsView(centralWidget);
        m_graphicsView->setObjectName(QString::fromUtf8("m_graphicsView"));

        gridLayout->addWidget(m_graphicsView, 0, 0, 1, 1);

        RootWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(RootWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 715, 25));
        RootWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(RootWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        RootWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(RootWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        RootWindow->setStatusBar(statusBar);

        retranslateUi(RootWindow);

        QMetaObject::connectSlotsByName(RootWindow);
    } // setupUi

    void retranslateUi(QMainWindow *RootWindow)
    {
        RootWindow->setWindowTitle(QApplication::translate("RootWindow", "RootWindow", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RootWindow: public Ui_RootWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROOT_2D_WINDOW_H
