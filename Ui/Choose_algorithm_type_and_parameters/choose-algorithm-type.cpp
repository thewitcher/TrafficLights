#include "choose-algorithm-type.h"
#include "ui_choose-algorithm-type.h"
#include "../Settings/settings.h"
#include "../Ui/Root_window/graphics-view.h"

bool ChooseAlgorithmType::S_CAN_RUN = false;

ChooseAlgorithmType::ChooseAlgorithmType( QWidget *parent ) :
    QDialog( parent ),
    ui( new Ui::ChooseAlgorithmType )
{
    ui->setupUi( this );
    setAutoExclusiveForRadioButtons();
    setNamesForRadioButtons();
    involvementForRadioButtons();
    involvementForOkOrNextOrDefaultButtons();
    involvementForBackButtons();
    setFixedSize( 491, 301 );
}

ChooseAlgorithmType::~ChooseAlgorithmType()
{
    delete ui;
}

void ChooseAlgorithmType::nextPage()
{
    if( ui->allGAradioButton->isChecked() || ui->OneGAradioButton->isChecked() )
        ui->stackedWidget->setCurrentIndex( 1 );
    else if( ui->AllFLradioButton->isChecked() || ui->OneFLradioButton->isChecked()
             || ui->standardRadioButton->isChecked() )
        ui->stackedWidget->setCurrentIndex( 2 );
}

void ChooseAlgorithmType::setParametersForAlgorithm()
{
    QList<QRadioButton*> radioButtonsList;
    radioButtonsList << ui->allGAradioButton << ui->OneGAradioButton
                     << ui->AllFLradioButton << ui->OneFLradioButton
                     << ui->standardRadioButton;

    int i = 0;
    while( radioButtonsList.at( i )->isChecked() == false )
    {
        i++;
    }

    customParametersForGeneral( i, radioButtonsList );
    customParametersForGA( i, radioButtonsList );
    S_CAN_RUN = true; /* chyba tu */
    close();
}

void ChooseAlgorithmType::customParametersForGeneral( const int& position, const QList<QRadioButton*> &list )
{
    int vehiclesFrequency = Settings::takeValue( "S_NEW_CAR_FREQUENCY", "GENERAL", 500 ).toInt();
    int numberOfCars = Settings::takeValue( "S_CAR_COUNT", "GENERAL", 200 ).toInt();
    int carsSpeed = Settings::takeValue( "S_CAR_SPEED", "GENERAL", 1 ).toInt();
    int busesSpeed = Settings::takeValue( "S_BUS_SPEED", "GENERAL", 3 ).toInt();
    int numberOfTheBuses = Settings::takeValue( "S_BUS_COUNT", "GENERAL", 5 ).toInt();
    int timeout = Settings::takeValue( "S_TIMEOUT", "GENERAL", 360 ).toInt();

    /* Algorithm type */
    Settings::setValues( "ALGORITHM_TYPE", "GENERAL", list.at( position )->accessibleName() );

    /* Count of cars */
    if( ui->countOfVehiclesLineEdit->text().isEmpty() == false && ui->countOfVehiclesLineEdit->text().toInt() <= 300 )
    {
        numberOfCars = ui->countOfVehiclesLineEdit->text().toInt();
        Settings::setValues( "S_CAR_COUNT", "GENERAL", ui->countOfVehiclesLineEdit->text() );
    }

    /* Number of the buses */
    if( ui->numberOfBusesLineEdit->text().isEmpty() == false )
    {
        numberOfTheBuses = ui->numberOfBusesLineEdit->text().toInt();
        Settings::setValues( "S_BUS_COUNT", "GENERAL", ui->numberOfBusesLineEdit->text() );
    }

    /* Vehicles frequency */
    if( ui->vehiclesFrequencyLineEdit->text().isEmpty() == false )
    {
        vehiclesFrequency = ui->vehiclesFrequencyLineEdit->text().toInt();
        Settings::setValues( "S_NEW_CAR_FREQUENCY", "GENERAL", ui->vehiclesFrequencyLineEdit->text() );
    }

    /* Cars speed */
    if( ui->carSpeedLineEdit->text().isEmpty() == false )
    {
        carsSpeed = ui->carSpeedLineEdit->text().toInt();
        Settings::setValues( "S_CAR_SPEED", "GENERAL", ui->carSpeedLineEdit->text() );
    }

    /* Buses speed */
    if( ui->busSpeedLineEdit->text().isEmpty() == false )
    {
        busesSpeed = ui->busSpeedLineEdit->text().toInt();
        Settings::setValues( "S_BUS_SPEED", "GENERAL", ui->busSpeedLineEdit->text() );
    }

    /* Timeout */
    if( ui->timeoutLineEdit->text().isEmpty() == false )
    {
        busesSpeed = ui->timeoutLineEdit->text().toInt();
        Settings::setValues( "S_TIMEOUT", "GENERAL", ui->timeoutLineEdit->text() );
    }

    GraphicsView::updateStaticVariables( numberOfCars, numberOfTheBuses,
                                         vehiclesFrequency, carsSpeed, busesSpeed, timeout );
}

void ChooseAlgorithmType::customParametersForGA( const int& position, const QList<QRadioButton*> &list )
{
    /* GA parameters */
    if( ui->replacementProbabilityLineEdit->text().isEmpty() == false )
    Settings::setValues( "REPLACEMENT_PROBABILITY", "%" + list.at( position )->accessibleName(),
                         ui->replacementProbabilityLineEdit->text() );

    if( ui->populationSizeLineEdit->text().isEmpty() == false )
    Settings::setValues( "POPULATION_SIZE", "%" + list.at( position )->accessibleName(),
                         ui->populationSizeLineEdit->text() );

    if( ui->generationsLineEdit->text().isEmpty() == false )
    Settings::setValues( "GENERATIONS", "%" + list.at( position )->accessibleName(),
                         ui->generationsLineEdit->text() );

    if( ui->mutationProbabilityLineEdit->text().isEmpty() == false )
    Settings::setValues( "MUTATION_PROBABILITY", "%" + list.at( position )->accessibleName(),
                         ui->mutationProbabilityLineEdit->text() );

    if( ui->crossoverProbabilityLineEdit->text().isEmpty() == false )
    Settings::setValues( "CROSSOVER_PROBABILITY", "%" + list.at( position )->accessibleName(),
                         ui->crossoverProbabilityLineEdit->text() );
}

void ChooseAlgorithmType::setNamesForRadioButtons()
{
    ui->AllFLradioButton->setAccessibleName( "ALL_FUZZY_LOGIC" );
    ui->allGAradioButton->setAccessibleName( "ALL_SUBCYCLE_ALGORITHM" );
    ui->OneFLradioButton->setAccessibleName( "ONE_FUZZY_LOGIC" );
    ui->OneGAradioButton->setAccessibleName( "ONE_SUBCYCLE_ALGORITHM" );
    ui->standardRadioButton->setAccessibleName( "NORMAL" );
}

void ChooseAlgorithmType::setdefaultValuesForGA()
{
    QList<QString> list;
    if( ui->allGAradioButton->isChecked() )
        list = defaultValuesForAllSubcycleAlgorithm();
    else if( ui->OneGAradioButton->isChecked() )
        list = defaultValuesForOneSubcycleAlgorithm();

    ui->replacementProbabilityLineEdit->setText( list.at( 0 ) );
    ui->populationSizeLineEdit->setText( list.at( 1 ) );
    ui->generationsLineEdit->setText( list.at( 2 ) );
    ui->mutationProbabilityLineEdit->setText( list.at( 3 ) );
    ui->crossoverProbabilityLineEdit->setText( list.at( 4 ) );
}

void ChooseAlgorithmType::setDefaultValuesForGeneral()
{
    QList<QString> list = defaultValuesForGeneral();

    ui->vehiclesFrequencyLineEdit->setText( list.at( 0 ) );
    ui->countOfVehiclesLineEdit->setText( list.at( 1 ) );
    ui->carSpeedLineEdit->setText( list.at( 2 ) );
    ui->busSpeedLineEdit->setText( list.at( 3 ) );
    ui->numberOfBusesLineEdit->setText( list.at( 4 ) );
    ui->timeoutLineEdit->setText( list.at( 5 ) );
}

QList<QString> ChooseAlgorithmType::defaultValuesForAllSubcycleAlgorithm()
{
    QList<QString> list;
    QString replacementProbability = "0.4";
    QString populationSize = "1000";
    QString generations = "100";
    QString mutationProbability = "0.2";
    QString crossoverProbability = "0.8";
    list << replacementProbability << populationSize << generations
         << mutationProbability << crossoverProbability;

    return list;
}

QList<QString> ChooseAlgorithmType::defaultValuesForOneSubcycleAlgorithm()
{
    QList<QString> list;
    QString replacementProbability = "0.4";
    QString populationSize = "90";
    QString generations = "100";
    QString mutationProbability = "0.09";
    QString crossoverProbability = "0.2";
    list << replacementProbability << populationSize << generations
         << mutationProbability << crossoverProbability;

    return list;
}

QList<QString> ChooseAlgorithmType::defaultValuesForGeneral()
{
    QList<QString> list;
    QString vehiclesFrequency = "500";
    QString numberOfCars = "200";
    QString carsSpeed = "1";
    QString busesSpeed = "3";
    QString numberOfTheBuses = "5";
    QString timeout = "360";
    list << vehiclesFrequency << numberOfCars << carsSpeed << busesSpeed << numberOfTheBuses << timeout;

    return list;
}

void ChooseAlgorithmType::involvementForRadioButtons()
{
    connect( ui->AllFLradioButton, SIGNAL(released()), this, SLOT(nextPage()) );
    connect( ui->allGAradioButton, SIGNAL(released()), this, SLOT(nextPage()) );
    connect( ui->OneFLradioButton, SIGNAL(released()), this, SLOT(nextPage()) );
    connect( ui->OneGAradioButton, SIGNAL(released()), this, SLOT(nextPage()) );
    connect( ui->standardRadioButton, SIGNAL(released()), this, SLOT(nextPage()) );
}

void ChooseAlgorithmType::involvementForBackButtons()
{
    connect( ui->backButtonForGeneral, SIGNAL(clicked()), this, SLOT(routeToPreviousPage()) );
    connect( ui->backButtonForGA, SIGNAL(clicked()), this, SLOT(backToMainPage()) );
}

void ChooseAlgorithmType::involvementForOkOrNextOrDefaultButtons()
{
    connect( ui->closeButtonForGeneral, SIGNAL(clicked()), this, SLOT(setParametersForAlgorithm()) );
    connect( ui->nextButtonForGA, SIGNAL(clicked()), this, SLOT(routeToNextPage()) );
    connect( ui->defaultValuesButton, SIGNAL(clicked()), this, SLOT(setdefaultValuesForGA()));
    connect( ui->defaultValuesButtonForGeneral, SIGNAL(clicked()), this, SLOT(setDefaultValuesForGeneral()));
}

void ChooseAlgorithmType::routeToPreviousPage()
{
    if( ui->allGAradioButton->isChecked() || ui->OneGAradioButton->isChecked() )
        ui->stackedWidget->setCurrentIndex( 1 );
    else{
        clearAll();
        ui->stackedWidget->setCurrentIndex( 0 );
    }
}

void ChooseAlgorithmType::routeToNextPage()
{
    ui->stackedWidget->setCurrentIndex( 2 );
}

void ChooseAlgorithmType::backToMainPage()
{
    clearAll();
    ui->stackedWidget->setCurrentIndex( 0 );
}

void ChooseAlgorithmType::clearAll()
{
    ui->AllFLradioButton->setChecked( false );
    ui->allGAradioButton->setChecked( false );
    ui->OneFLradioButton->setChecked( false );
    ui->OneGAradioButton->setChecked( false );
    ui->standardRadioButton->setChecked( false );
}

void ChooseAlgorithmType::setAutoExclusiveForRadioButtons()
{
    ui->AllFLradioButton->setAutoExclusive( false );
    ui->allGAradioButton->setAutoExclusive( false );
    ui->OneFLradioButton->setAutoExclusive( false );
    ui->OneGAradioButton->setAutoExclusive( false );
    ui->standardRadioButton->setAutoExclusive( false );
}
