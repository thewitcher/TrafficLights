#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui { class MainWindow; }

class Database;

class MainWindow: public QMainWindow
{

    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Database* m_database;

    void init();
    void createConnections();
    int experimentId();

public slots:
    void createReport();
};

#endif // MAINWINDOW_H
