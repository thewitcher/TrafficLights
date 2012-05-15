#include "main-window.h"
#include "ui_main-window.h"
#include "database.h"
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_database( new Database )
{
    ui->setupUi(this);

    init();
    createConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_database;
}

void MainWindow::init()
{
    ui->m_experimentsComboBox->addItems( m_database->loadExperiments() );
}

void MainWindow::createConnections()
{
    connect( ui->m_reportButton, SIGNAL(clicked()), this, SLOT(createReport()) );
}

int MainWindow::experimentId()
{
    QString text = ui->m_experimentsComboBox->currentText();

    int i = 0;
    QString id = "";

    while( text.at( i ).isDigit() )
    {
        id += text.at( i );
        i++;
    }

    return id.toInt();
}

void MainWindow::createReport()
{
    m_database->setExperimentId( experimentId() );

    /// VEHICLE COUNT
    QFile file( ui->m_experimentsComboBox->currentText() + " vehicleCount.csv" );

    if( file.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
    {
        return;
    }

    QTextStream writer( &file );

    QStringList statisticList = m_database->loadVehicleCountOnJunctions();

    for( int i = 0 ; i < statisticList.count() ; i++ )
    {
        writer << statisticList.at( i ) << "\n";
    }

    file.close();

    /// VEHICLE WAITING TIME
    file.setFileName( ui->m_experimentsComboBox->currentText() + " vehicleWaitingTime.csv" );

    if( file.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
    {
        return;
    }

    statisticList.clear();
    statisticList = m_database->loadVehicleWaitingTimeOnJunctions();

    for( int i = 0 ; i < statisticList.count() ; i++ )
    {
        writer << statisticList.at( i ) << "\n";
    }


    /// VEHICLE COUNT ON SUBCYCLES
    for( int i = 0 ; i <= 6 ; i++ )
    {
        file.close();

        file.setFileName( ui->m_experimentsComboBox->currentText() + " vehicleCount" + QString::number( i ) + ".csv" );

        if( file.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
        {
            return;
        }

        statisticList.clear();
        statisticList = m_database->loadVehicleCountOnSubcyclesOnAppropriateJunction( i );

        for( int i = 0 ; i < statisticList.count() ; i++ )
        {
            writer << statisticList.at( i ) << "\n";
        }
    }

    /// VEHICLE WAITING TIME ON SUBCYCLES
    for( int i = 0 ; i <= 6 ; i++ )
    {
        file.close();

        file.setFileName( ui->m_experimentsComboBox->currentText() + " vehicleWaitingTime" + QString::number( i ) + ".csv" );

        if( file.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
        {
            return;
        }

        statisticList.clear();
        statisticList = m_database->loadWaitingTimeOnSubcyclesOnAppropriateJunction( i );

        for( int i = 0 ; i < statisticList.count() ; i++ )
        {
            writer << statisticList.at( i ) << "\n";
        }
    }
}
