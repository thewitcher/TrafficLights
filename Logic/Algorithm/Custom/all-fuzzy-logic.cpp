#include "all-fuzzy-logic.h"
#include "../Ui/TrafficLights_manager/junction.h"
#include "../Ui/TrafficLights_manager/vehicle-count-manager.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/TriangularTerm.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/ShoulderTerm.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/TrapezoidalTerm.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyEngine.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/RuleBlock.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/MamdaniRule.h"
#include "../Logic/Algorithm/FIS/fuzzylite-1.03/fuzzylite/fuzzylite/FuzzyOperator.h"
#include "../Logger/logger.h"


AllFuzzyLogic::AllFuzzyLogic( Junction *junction, const QString& algorithmType ):
  BaseAlgorithm( junction, algorithmType ),
  m_runCount( 0 ),
  m_nullVectorCount( 0 ),
  m_firstRun( false )
{
}

QVector<int> AllFuzzyLogic::startAlgorithm()
{
    QVector<int> vector ;
    if( m_firstRun == false )
    {
        vector.clear();
        vector << 3000 << 3000 << 3000 << 3000;
        m_firstRun = true;
        return vector;
    }

    switch( m_junction->junctionType() )
    {
    case Junction::SIMPLE:
        setNumberOfCycleForSimpleJunction();
        vehiclesCountForSimpleJunction();
        if( m_vehiclesCountAtLane != 0 ){
            vector = returnTimeVectorForSimple( startSimulation() );
            m_runCount++;
        }
        else{
            exceptionForSimpleJunction( vector );
        }
        break;
    case Junction::BLADZIO:
        setNumberOfCycleForBladzioJunction();
        vehiclesCountForBladzioJunction();
        if( m_vehiclesCountAtLane != 0 ){
            vector = returnTimeVectorForBladzio( startSimulation() );
            m_runCount++;
        }
        else{
            exceptionForBladzioJunction( vector );
        }

        break;
    default:
        break;
    }
    return vector;
}

/*! If at simple junction doesn't have vehicles, timeVector is set as follows timeVector << 0 << 4000 << 0. */
void AllFuzzyLogic::exceptionForSimpleJunction( QVector<int>& vector )
{
    vector << 0 << 0 << 0;
    m_runCount++;
    if( vector.at( 0 ) == 0 && vector.at( 1 )== 0 && vector.at( 2 ) == 0 && m_nullVectorCount < 3 )
    {
        m_nullVectorCount++;
        vector = startAlgorithm();
    }
    else if( vector.at( 0 ) == 0 && vector.at( 1 )== 0 && vector.at( 2 ) == 0 && m_nullVectorCount == 3 )
    {
        vector.clear();
        m_nullVectorCount = 0;
        vector << 0 << 4000 << 0;
    }
}

/*! If at Bladzio junction doesn't have vehicles, timeVector is set as follows timeVector << 0 << 4000 << 0 << 0. */
void AllFuzzyLogic::exceptionForBladzioJunction( QVector<int> &vector )
{
    vector << 0 << 0 << 0 << 0;
    m_runCount++;
    if( vector.at( 0 ) == 0 && vector.at( 1 )== 0 && vector.at( 2 ) == 0
            && vector.at( 3 ) == 0 && m_nullVectorCount < 4 )
    {
        m_nullVectorCount++;
        vector = startAlgorithm();
    }
    else if( vector.at( 0 ) == 0 && vector.at( 1 )== 0 && vector.at( 2 ) == 0
             && vector.at( 3 ) == 0 && m_nullVectorCount == 4 )
    {
        vector.clear();
        m_nullVectorCount = 0;
        vector << 0 << 4000 << 0 << 0;
    }
}

QVector<int> AllFuzzyLogic::returnTimeVectorForSimple( const int &value )
{
    QVector<int> vector;
    switch( m_runCount )
    {
    case 0:
        vector << value * 1000 << 0 << 0;
        break;
    case 1:
        vector << 0 << value * 1000 << 0;
        break;
    case 2:
        vector << 0 << 0 << value * 1000;
        break;
    default:
        LOG_CRITICAL( "[ALL_FUZZY] : return bad time vector for Simple Junction. m_runCount = %i", m_runCount );
        break;
    }
    return vector;
}

QVector<int> AllFuzzyLogic::returnTimeVectorForBladzio( const int &value )
{
    QVector<int> vector;
    switch( m_runCount )
    {
    case 0:
        vector << value * 1000 << 0 << 0 << 0;
        break;
    case 1:
        vector << 0 << value * 1000 << 0 << 0;
        break;
    case 2:
        vector << 0 << 0 << value * 1000 << 0;
        break;
    case 3:
        vector << 0 << 0 << 0 << value * 1000;
        break;
    default:
        LOG_CRITICAL( "[ALL_FUZZY] : return bad time vector for Bladzio Junction. m_runCount = %i", m_runCount );
        break;
    }
    return vector;
}


void AllFuzzyLogic::vehiclesCountForSimpleJunction()
{
    int sLeft, sRight;
    switch( m_numberOfCycle )
    {
    case FIRST:
        sLeft = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::SOUTH_LEFT );
        sRight = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::SOUTH_RIGHT );
        m_vehiclesCountAtLane = ( sLeft > sRight ) ? sLeft : sRight;
        break;
    case SECOND:
        m_vehiclesCountAtLane = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::EAST_MIDDLE );
        break;
    case THIRD:
        m_vehiclesCountAtLane = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::WEST_MIDDLE );
        break;
    default:
        break;
    }
    int count = VehicleCountManager::vehicleCountOnSubcycle( m_junction, VehicleCountManager::SUBCYCLE_0 );
    count += VehicleCountManager::vehicleCountOnSubcycle( m_junction, VehicleCountManager::SUBCYCLE_1 );
    count += VehicleCountManager::vehicleCountOnSubcycle( m_junction, VehicleCountManager::SUBCYCLE_2 );
    m_vehiclesCountAtJunction = count;
}

void AllFuzzyLogic::vehiclesCountForBladzioJunction()
{
    int sMiddle,sRight, max1, nMiddle,nLeft,max2,sLeft,nRight,wMiddle,wBottom,max3,eMiddle,eTop,max4,wTop,eBottom;
    switch( m_numberOfCycle )
    {
    case FIRST:
        sMiddle = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::SOUTH_MIDDLE );
        sRight = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::SOUTH_RIGHT );
        max1 = ( sMiddle > sRight ) ? sMiddle : sRight;

        nMiddle = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::NORTH_MIDDLE );
        nLeft = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::NORTH_LEFT);
        max2 = ( nMiddle > nLeft ) ? nMiddle : nLeft;

        m_vehiclesCountAtLane = ( max1 > max2 ) ? max1 : max2;
        break;
    case SECOND:
        sLeft = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::SOUTH_LEFT );
        nRight = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::NORTH_RIGHT );
        m_vehiclesCountAtLane = ( sLeft > nRight ) ? sLeft : nRight;
        break;
    case THIRD:
        wMiddle = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::WEST_MIDDLE );
        wBottom = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::WEST_BOTTOM );
        max3 = ( wMiddle > wBottom ) ? wMiddle : wBottom;

        eMiddle = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::EAST_MIDDLE );
        eTop = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::EAST_TOP );
        max4 = ( eMiddle > eTop ) ? eMiddle : eTop;

        m_vehiclesCountAtLane = ( max3 > max4 ) ? max3 : max4;
        break;
    case FOURTH:
        wTop = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::WEST_TOP );
        eBottom = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::EAST_BOTTOM );
        m_vehiclesCountAtLane = ( wTop > eBottom ) ? wTop : eBottom;
        break;
    default:
        break;
    }
    int count = VehicleCountManager::vehicleCountOnSubcycle( m_junction, VehicleCountManager::SUBCYCLE_0 );
    count += VehicleCountManager::vehicleCountOnSubcycle( m_junction, VehicleCountManager::SUBCYCLE_1 );
    count += VehicleCountManager::vehicleCountOnSubcycle( m_junction, VehicleCountManager::SUBCYCLE_2 );
    count += VehicleCountManager::vehicleCountOnSubcycle( m_junction, VehicleCountManager::SUBCYCLE_3 );
    m_vehiclesCountAtJunction = count;
}

/*! This is help function for simple junction. Sets the number subcycle, which must be checked. */
void AllFuzzyLogic::setNumberOfCycleForSimpleJunction()
{
    if( m_runCount == 3 )
        m_runCount = 0;
    switch( m_runCount )
    {
    case 0:
        m_numberOfCycle = FIRST;
        break;
    case 1:
        m_numberOfCycle = SECOND;
        break;
    case 2:
        m_numberOfCycle = THIRD;
        break;
    default:
        break;
    }
}
/*! This is help function for Bladzio junction. Sets the number subcycle, which must be checked. */
void AllFuzzyLogic::setNumberOfCycleForBladzioJunction()
{
    if( m_runCount == 4 )
        m_runCount = 0;
    switch( m_runCount )
    {
    case 0:
        m_numberOfCycle = FIRST;
        break;
    case 1:
        m_numberOfCycle = SECOND;
        break;
    case 2:
        m_numberOfCycle = THIRD;
        break;
    case 3:
        m_numberOfCycle = FOURTH;
    default:;
        break;
    }
}

int AllFuzzyLogic::startSimulation()
{
    fl::FuzzyOperator &op = fl::FuzzyOperator::DefaultFuzzyOperator();
    fl::FuzzyEngine engine( "complex-mamdani", op );
    engine.hedgeSet().add( new fl::HedgeNot );
    engine.hedgeSet().add( new fl::HedgeSomewhat );
    engine.hedgeSet().add( new fl::HedgeVery );

    fl::InputLVar *inPutLane = new fl::InputLVar( "Lane" );
    inPutLane->addTerm( new fl::ShoulderTerm( "SMALL_L", 0, 10, true ) );
    inPutLane->addTerm( new fl::TriangularTerm( "MEDIUM_L", 0, 20 ) ); //30
    fl::TrapezoidalTerm *trapezoidalTerm = new fl::TrapezoidalTerm( "LARGE_L", 10, 250 );
    trapezoidalTerm->setB( 30 );
    trapezoidalTerm->setC( 250 );
    trapezoidalTerm->setD( 250 );
    inPutLane->addTerm( trapezoidalTerm );
    engine.addInputLVar( inPutLane );

    fl::InputLVar *inPutJunction = new fl::InputLVar( "Junction" );
    inPutJunction->addTerm( new fl::ShoulderTerm( "SMALL_J", 0, 30, true ) );
    inPutJunction->addTerm( new fl::TriangularTerm( "MEDIUM_J", 0, 60 ) );
    fl::TrapezoidalTerm *trapezoidalTermJunction = new fl::TrapezoidalTerm( "LARGE_J", 30, 250 );
    trapezoidalTermJunction->setB( 60 );
    trapezoidalTermJunction->setC( 250 );
    trapezoidalTermJunction->setD( 250 );
    inPutJunction->addTerm( trapezoidalTermJunction );
    engine.addInputLVar( inPutJunction );

    fl::OutputLVar *outPutValues = new fl::OutputLVar( "Time" );
    outPutValues->addTerm( new fl::ShoulderTerm( "SMALL_T", 0, 10, true ) );
    outPutValues->addTerm( new fl::TriangularTerm( "MEDIUM_T", 0, 20 ) );  //bylo 20
    outPutValues->addTerm( new fl::ShoulderTerm( "LARGE_T", 10, 30, false ) );
    engine.addOutputLVar( outPutValues );
    fl::FuzzyOperator& opFuzzy = fl::FuzzyOperator::DefaultFuzzyOperator();
    opFuzzy.setAreaCentroidAlgorithm( new fl::TriangulationAlgorithm );
    opFuzzy.setTnorm( new fl::FuzzyAndMin );
    opFuzzy.setSnorm( new fl::FuzzyOrMax );


    fl::RuleBlock *block = new fl::RuleBlock();
    block->addRule( new fl::MamdaniRule( "if Lane is SMALL_L and Junction is SMALL_J then Time is SMALL_T", engine ) );
    block->addRule( new fl::MamdaniRule( "if Lane is SMALL_L and Junction is MEDIUM_J then Time is SMALL_T", engine ) );
    block->addRule( new fl::MamdaniRule( "if Lane is SMALL_L and Junction is LARGE_J then Time is SMALL_T", engine ) );

    block->addRule( new fl::MamdaniRule( "if Lane is MEDIUM_L and Junction is SMALL_J then Time is MEDIUM_T", engine ) );
    block->addRule( new fl::MamdaniRule( "if Lane is MEDIUM_L and Junction is MEDIUM_J then Time is MEDIUM_T", engine ) );
    block->addRule( new fl::MamdaniRule( "if Lane is MEDIUM_L and Junction is LARGE_J then Time is MEDIUM_T", engine ) );

    block->addRule( new fl::MamdaniRule( "if Lane is LARGE_L and Junction is SMALL_J then Time is LARGE_T", engine ) );
    block->addRule( new fl::MamdaniRule( "if Lane is LARGE_L and Junction is MEDIUM_J then Time is LARGE_T", engine ) );
    block->addRule( new fl::MamdaniRule( "if Lane is LARGE_L and Junction is LARGE_J then Time is MEDIUM_T", engine ) );
    engine.addRuleBlock( block );

    inPutLane->setInput( m_vehiclesCountAtLane );
    inPutJunction->setInput( m_vehiclesCountAtJunction );

    setTerm( block );
    QHash<int,float>::iterator it = m_hash.begin();
    whichSet( it.key() );
    whichTerm( m_vehiclesCountAtLane );
    engine.process();
    int score = startDefuzzy( it.value() );
    m_hash.clear();
    return score;
}

/*! This function is defuzzificator. Based on term and fuzzy value defuzzifier the final result.  */
int AllFuzzyLogic::startDefuzzy( const float& value )
{
    int score = 0;
    if( m_term == FIRST_TERM )
        score = ( value * ( m_medium - m_start ) ) + m_start;
    else
        score = ( value * ( m_end - m_medium ) - m_end ) * (-1);

    return score;
}

/*! This function saves in hash rule number and fuzzy value. */
void AllFuzzyLogic::setTerm( fl::RuleBlock* block )
{
    fl::flScalar max = 0;
    int position = 0;
    for( int i = 0; i < block->numberOfRules(); ++i )
    {
        if( max <= block->rule( i )->firingStrength() )
        {
            max = block->rule( i )->firingStrength();
            position = i;
        }
    }
    m_hash.insert( position, max );
}

/*! Based on rule number, function sets appropriate parameters for one of three collections. */
void AllFuzzyLogic::whichSet( const int& value )
{
    if( value >= 0 && value < 3 )
    {
        m_set = SMALL_SET;
        m_start = 0, m_medium = 0, m_end = 10;
    }
    else if( value >= 3 && value < 6 )
    {
        m_set = MEDIUM_SET;
        m_start = 0, m_medium = 10, m_end = 20;
    }
    else if( value >= 6 && value < 9 )
    {
        m_set = LARGE_SET;
        m_start = 10, m_medium = 30, m_end = 30;
    }
}

/*! Based on number of vehicles, function sets appropriate half of TriangularTerm. */
void AllFuzzyLogic::whichTerm( const int &value )
{
    switch( m_set )
    {
    case SMALL_SET:
        m_term = SECOND_TERM;
        break;
    case MEDIUM_SET:
        if( value < 10 )
            m_term = FIRST_TERM;
        else
            m_term = SECOND_TERM;
        break;
    case LARGE_SET:
        m_term = FIRST_TERM;
        break;
    default:
        break;
    }
}
