#include "main-window.h"
#include "ui_main-window.h"
#include "database.h"
#include <QFile>
#include <QTextStream>
#include <QDir>

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
    connect( ui->m_clearButton, SIGNAL(clicked()), this, SLOT(clearDatabase()));
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

    QString folderName  = ui->m_experimentsComboBox->currentText();

    createFolder( folderName );

    /// VEHICLE COUNT
    QFile file( folderName + "/vehicleCount.csv" );
    if( file.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
    {
        return;
    }

    QTextStream writer( &file );

    QStringList statisticList = m_database->load( Database::VEHICLE_COUNT );

    for( int i = 0 ; i < statisticList.count() ; i++ )
    {
        writer << statisticList.at( i ) << "\n";
    }

    file.close();

    /// VEHICLE WAITING TIME
    file.setFileName( folderName + "/vehicleWaitingTime.csv" );

    if( file.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
    {
        return;
    }

    statisticList.clear();
    statisticList = m_database->load( Database::VEHICLE_WAITING_TIME );

    for( int i = 0 ; i < statisticList.count() ; i++ )
    {
        writer << statisticList.at( i ) << "\n";
    }

    file.close();

    /// VEHICLE DRIVED AWAY COUNT
    file.setFileName( folderName + "/vehicleDriveAwayCount.csv" );

    if( file.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
    {
        return;
    }

    statisticList.clear();
    statisticList = m_database->load( Database::VEHICLE_DRIVED_AWAY );

    for( int i = 0 ; i < statisticList.count() ; i++ )
    {
        writer << statisticList.at( i ) << "\n";
    }

    /// VEHICLE COUNT ON SUBCYCLES
    for( int i = 0 ; i <= 6 ; i++ )
    {
        file.close();

        file.setFileName( folderName + "/vehicleCount" + QString::number( i ) + ".csv" );

        if( file.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
        {
            return;
        }

        statisticList.clear();
        statisticList = m_database->load( Database::LOCAL_VEHICLE_COUNT, i );

        for( int i = 0 ; i < statisticList.count() ; i++ )
        {
            writer << statisticList.at( i ) << "\n";
        }
    }

    /// VEHICLE WAITING TIME ON SUBCYCLES
    for( int i = 0 ; i <= 6 ; i++ )
    {
        file.close();

        file.setFileName( folderName + "/vehicleWaitingTime" + QString::number( i ) + ".csv" );

        if( file.open( QIODevice::WriteOnly | QIODevice::Text ) == false )
        {
            return;
        }

        statisticList.clear();
        statisticList = m_database->load( Database::LOCAL_VEHICLE_WAITING_TIME, i );

        for( int i = 0 ; i < statisticList.count() ; i++ )
        {
            writer << statisticList.at( i ) << "\n";
        }
    }

    qApp->quit();
}

void MainWindow::clearDatabase()
{
    ui->m_experimentsComboBox->clear();
    m_database->clearDatabase();
}

void MainWindow::createFolder( const QString & name )
{
    QDir dir;

    dir.mkdir( dir.currentPath() + "/" + name );
}
