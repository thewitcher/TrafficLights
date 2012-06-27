#include "one-fuzzy-logic.h"
#include "../Ui/TrafficLights_manager/junction.h"
#include "../FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyEngine.h"
#include "../FIS/fuzzylite-1.03/fuzzylite/fuzzylite/ShoulderTerm.h"
#include "../FIS/fuzzylite-1.03/fuzzylite/fuzzylite/TrapezoidalTerm.h"
#include "../FIS/fuzzylite-1.03/fuzzylite/fuzzylite/TriangularTerm.h"
#include "../FIS/fuzzylite-1.03/fuzzylite/fuzzylite/MamdaniRule.h"
#include "../FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyOperator.h"
#include "../FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyOperation.h"
#include "../FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyExceptions.h"
#include "../Logger/logger.h"


OneFuzzyLogic::OneFuzzyLogic( Junction *junction, const QString& algorithmType ):
    OneSubcycleAlgorithm( junction, algorithmType )
{
}

QVector<int> OneFuzzyLogic::startAlgorithm()
{
    if( m_firstRun == true )
    {
        m_firstRun = false;
        return QVector<int>() << 3000 << 3000 << 3000 << 3000;
    }

    int greenTime = 0;

    switch( m_junction->junctionType() )
    {
    case Junction::SIMPLE:
        chooseTheMostBlockSubcycleForSimple();
        loadDataForSimple();
        if( m_vehicleCount == 0 )
        {
            return QVector<int>() << 1000 << 1000 << 1000 << 1000;
        }
        greenTime = estimateGreenLight();
        break;
    case Junction::BLADZIO:
        chooseTheMostBlockSubcycleForBladzio();
        loadDataForBladzio();
        if( m_vehicleCount == 0 )
        {
            return QVector<int>() << 1000 << 1000 << 1000 << 1000;
        }
        greenTime = estimateGreenLight();
        break;
    default:
        break;
    }

    QVector<int> vector;
    /// 4 - subcycles count
    for( int i = 0 ; i < 4 ; i++ )
    {
        if( i == int( m_currentSubcycle ) )
        {
            vector << greenTime;
        }
        else
        {
            vector << 0;
        }
    }

    qDebug() << "Id: " << m_junction->id() << " " << vector;

    return vector;
}

/// Take care about vehicle count. It should be in approriate range.
int OneFuzzyLogic::estimateGreenLight()
{
    fl::FuzzyOperator& op = fl::FuzzyOperator::DefaultFuzzyOperator();
    fl::FuzzyEngine engine("complex-mamdani", op);

    /// Check what is it!!
    engine.hedgeSet().add( new fl::HedgeNot );
    engine.hedgeSet().add( new fl::HedgeSomewhat );
    engine.hedgeSet().add( new fl::HedgeVery );

    /// Current - means on chosen subcycle
    fl::InputLVar* current = new fl::InputLVar( "Current" );
    current->addTerm( new fl::ShoulderTerm( "CURRENT_FEW", 0, 14, true ) );
    current->addTerm( new fl::TriangularTerm( "CURRENT_MANY", 0, 30 ) );
    current->addTerm( new fl::ShoulderTerm( "CURRENT_ENORMOUS", 14, 30, false ) );
    engine.addInputLVar( current );

    /// Rest - means on the rest subcycles
    fl::InputLVar* rest = new fl::InputLVar( "Rest" );
    rest->addTerm( new fl::ShoulderTerm( "REST_FEW", 0, 30, true ) );
    rest->addTerm( new fl::TriangularTerm( "REST_MANY", 0, 60 ) );
    rest->addTerm( new fl::ShoulderTerm( "REST_ENORMOUS", 30, 60, false ) );
    engine.addInputLVar( rest );

    fl::OutputLVar* greenTime = new fl::OutputLVar( "GreenTime" );
    greenTime->addTerm( new fl::ShoulderTerm( "SHORT", 0, 8, true ) );

    fl::TrapezoidalTerm * trapezoidalTerm = new fl::TrapezoidalTerm( "VERY_LONG", 0, 30 );
    trapezoidalTerm->setB( 12 );
    trapezoidalTerm->setC( 16 );
    greenTime->addTerm( trapezoidalTerm );

    greenTime->addTerm( new fl::ShoulderTerm( "FOREVER", 20, 30, false ) );
    engine.addOutputLVar( greenTime );

    fl::RuleBlock* block = new fl::RuleBlock();
    block->addRule( new fl::MamdaniRule( "if Current is CURRENT_FEW and Rest is REST_FEW then GreenTime is SHORT", engine ) );
    block->addRule( new fl::MamdaniRule( "if Current is CURRENT_FEW and Rest is REST_MANY then GreenTime is SHORT", engine ) );
    block->addRule( new fl::MamdaniRule( "if Current is CURRENT_FEW and Rest is REST_ENORMOUS then GreenTime is SHORT", engine ) );
    block->addRule( new fl::MamdaniRule( "if Current is CURRENT_MANY and Rest is REST_FEW then GreenTime is SHORT", engine ) );
    block->addRule( new fl::MamdaniRule( "if Current is CURRENT_MANY and Rest is REST_MANY then GreenTime is VERY_LONG", engine ) );
    block->addRule( new fl::MamdaniRule( "if Current is CURRENT_MANY and Rest is REST_ENORMOUS then GreenTime is SHORT", engine ) );
    block->addRule( new fl::MamdaniRule( "if Current is CURRENT_ENORMOUS and Rest is REST_FEW then GreenTime is FOREVER", engine ) );
    block->addRule( new fl::MamdaniRule( "if Current is CURRENT_ENORMOUS and Rest is REST_MANY then GreenTime is VERY_LONG", engine ) );
    block->addRule( new fl::MamdaniRule( "if Current is CURRENT_ENORMOUS and Rest is REST_ENORMOUS then GreenTime is SHORT", engine ) );
    engine.addRuleBlock( block );

    /// Here we can set value for fuzzyfication ( current and rest value )
    int currentValue = VehicleCountManager::vehicleCountOnSubcycle( m_junction, m_currentSubcycle ); /// vehicle count on appropriate subcycle
    int restValue = VehicleCountManager::vehicleCountOnRestSubcycle( m_junction, m_currentSubcycle ); /// vehicle count on the rest subcycles

    if( currentValue > 30 )
    {
        currentValue = 30;
    }
    if( currentValue < 1 )
    {
        currentValue = 1;
    }

    if( restValue > 60 )
    {
        restValue = 60;
    }
    if( restValue < 1 )
    {
        restValue = 1;
    }

    current->setInput( currentValue );
    rest->setInput( restValue );

    engine.process();

    int result = greenTime->output().defuzzify();

    LOG_INFO( "[FUZZY] Current is: %s", current->fuzzify( currentValue ).data() );
    LOG_INFO( "[FUZZY] Rest is: %s", rest->fuzzify( restValue ).data() );
    LOG_INFO( "[FUZZY] Result: %f", greenTime->output().defuzzify() );

#ifdef LOGGER
    for ( int i = 0 ; i < block->numberOfRules() ; i++ )
    {
        LOG_INFO( "[FUZZY] rule: %s", block->rule(i)->toString().data() );
        LOG_INFO( "[FUZZY] firing strength: %f", block->rule(i)->firingStrength() );
    }
#endif

    if( result <= 0 )
    {
        result = 1;
    }

    return ( result * 1000 );
}
