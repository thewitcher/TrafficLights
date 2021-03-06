#include "all-subcycle-algorithm.h"
#include "../Ui/TrafficLights_manager/junction.h"
#include "helper.h"
#include "../GA/GA1DArrayGenome.h"
#include "../GA/GASStateGA.h"
#include "../GA/garandom.h"
#include <cmath>
#include <iostream>

/*! Special global objective function for all subcycle algorithm. Grades each chromosome. */
float allSubcycleObjective( GAGenome& genome )
{
    float currentScore = 0.0;
    GA1DArrayGenome<int>& arrayGenome = Helper::genomeToArrayGenome( genome );

    AllSubcycleAlgorithm *allAlgorithm = Helper::userDataToAllSubcycleAlgorithm( genome );

    for( int i = 0; i < arrayGenome.size(); i++ )
        allAlgorithm->m_timeVector.append( arrayGenome.gene( i ));

    for( int i = 0; i < allAlgorithm->m_timeVector.size(); i++ )
        allAlgorithm->m_totalTimes += allAlgorithm->m_timeVector.at( i );

    allAlgorithm->allSubcycleFitness( currentScore );

    allAlgorithm->clearAll();

    return currentScore;
}

/*! This is help function. Computes values for chromosomes. */
void AllSubcycleAlgorithm::allSubcycleFitness( float &score )
{
    if( std::isnan( m_totalTimes ) == false && m_totalTimes != 0 )
    {
        float sumVehiclesAtJunctionVariable = VehicleCountManager::sumVehiclesAtJunction( m_junction );
        float expression = ( m_numberOfVehiclesThatWillDrive / sumVehiclesAtJunctionVariable );
        score = (((( expression * 10000 )
                   - theSumOfTheRemainingVehiclesAtJunction() ) * exp( m_alpha ) )
               + m_magicE );

            if( score <= 0 )
                score = 1.0;
    }
    else{
    score = 0.1;
    }
}

/*! Special global initializer function for all subcycle algorithm. Initiates chromosomes initial values. */
void allSubcycleInitializer( GAGenome& genome )
{
    AllSubcycleAlgorithm *allAlgorithm = Helper::userDataToAllSubcycleAlgorithm( genome );
    GA1DArrayGenome<int>& arrayGenome = Helper::genomeToArrayGenome( genome );
    int max = VehicleCountManager::sumVehiclesAtJunction( allAlgorithm->junction() ) * 0.8;

    if( max < 6 )
        max = 6;

    switch( allAlgorithm->junction()->junctionType() )
    {
    case Junction::BLADZIO:
        for( unsigned int position = 0; position < 4; position++ )
        {
            arrayGenome.gene( position, GARandomInt( 0, max ) );
        }
        break;
    case Junction::SIMPLE:
        for( unsigned int position = 0; position < 3; position++ )
        {
            arrayGenome.gene( position, GARandomInt( 0, max ) );
        }
        break;
    default:
        break;
    }
}

/*! This is global help function for all subcycle algorithm.
    It makes mutation in individuals with random propability.
*/
int allSubcycleMutation( GAGenome& genome, float pmut )
{
    if( pmut <= 0.0 )
        return 0;

    AllSubcycleAlgorithm *allAlgorithm = Helper::userDataToAllSubcycleAlgorithm( genome );
    GA1DArrayGenome<int>& arrayGenome = Helper::genomeToArrayGenome( genome );
    int max = VehicleCountManager::sumVehiclesAtJunction( allAlgorithm->junction() ) * 0.8;

    int position1, position2;
    int value1 = GARandomInt( 0, max );
    int value2 = GARandomInt( 0, max );
    int nmut = 0;

    switch( allAlgorithm->junction()->junctionType() )
    {
    case Junction::BLADZIO:
        position1 = GARandomInt( 0, 3 );
        position2 = GARandomInt( 0, 3 );

        if( position1 <= 3 && position2 <= 3 )
        {
            arrayGenome.gene( position1, value1 );
            arrayGenome.gene( position2, value2 );
        }
        nmut = 2;
        break;
    case Junction::SIMPLE:
        position1 = GARandomInt( 0, 2 );
        position2 = GARandomInt( 0, 2 );

        if( position1 <= 2 && position2 <= 2 )
        {
            arrayGenome.gene( position1, value1 );
            arrayGenome.gene( position2, value2 );
        }
        nmut = 2;
        break;
    default:
        nmut = 0;
        break;
    }

    return nmut;
}

AllSubcycleAlgorithm::AllSubcycleAlgorithm( Junction *junction, const QString& algorithmType ):
    BaseAlgorithm( junction, algorithmType ),
    m_numberOfVehiclesThatWillDrive( 0 ),
    m_alpha( 0 ),
    m_magicE( 0 )
{}

QVector<int> AllSubcycleAlgorithm::startAlgorithm()
{
    QVector<int> timeVector;

    int traffic = VehicleCountManager::sumVehiclesAtJunction( m_junction );

        switch( m_junction->junctionType() )
        {
        case Junction::BLADZIO:
            if( traffic > 24 )
            {
                m_genomeSize = 4;
                timeVector = setParameters();
            }
            else
            {
                timeVector = normalTraffic();
            }
            exceptionForBladzio( timeVector );
            break;
        case Junction::SIMPLE:
            if( traffic > 18 )
            {
                m_genomeSize = 3;
                timeVector = setParameters();
            }
            else
            {
                timeVector = normalTraffic();
            }
            exceptionForSimple( timeVector );
            break;
        default:
            break;
        }

    return timeVector;
}

QVector<int> AllSubcycleAlgorithm::setParameters()
{
    QVector<int> vector;

    GA1DArrayGenome<int> genome( m_genomeSize, allSubcycleObjective, this );
    genome.initializer( allSubcycleInitializer );
    genome.initialize();
    genome.mutator( allSubcycleMutation );


    GASteadyStateGA steadyStateGA( genome );

    steadyStateGA.populationSize( m_populationSize );
    steadyStateGA.pReplacement( m_replacementProbability );
    steadyStateGA.nGenerations( m_generations );
    steadyStateGA.pMutation( m_mutation );
    steadyStateGA.pCrossover( m_crossover );
    steadyStateGA.scoreFilename( m_logFile.toAscii().constData() );
    steadyStateGA.scoreFrequency( m_scoreFrequency );
    steadyStateGA.flushFrequency( m_flushFrequency );
    steadyStateGA.selectScores( GAStatistics::AllScores );
    steadyStateGA.evolve();

    GA1DArrayGenome<int>& bestGenome = Helper::genomeToArrayGenome( steadyStateGA.population().best() );
    for(int i = 0; i < bestGenome.size(); i++)
    {
        vector.append( bestGenome.gene( i ) * 1000 );
    }

    return vector;
}

float AllSubcycleAlgorithm::theSumOfTheRemainingVehiclesAtJunction()
{
   float score = 0;

   if( m_junction->id() != 2 )
       m_numberOfVehiclesThatWillDrive = evalForSimpleJunction();
   else
       m_numberOfVehiclesThatWillDrive = evalForBladzioJunction();


   score = m_junction->currentNumberOfVehicles() - m_numberOfVehiclesThatWillDrive;

   setAlphaParam( m_numberOfVehiclesThatWillDrive );

   return score;
}
/*! This function evals how many vehicles can pass through Simple junction and computes magic E parameter. */
float AllSubcycleAlgorithm::evalForSimpleJunction()
{
    int numberOfVehiclesThatWillDrive = 0;

    /* SouthLeft */
    int numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::SOUTH_LEFT );
    int countFromLane_1 = howMuchVehiclesAtLaneWillDrive( 0, numberVehiclesOnLane );
    numberOfVehiclesThatWillDrive += countFromLane_1;

    /* SouthRight */
    numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::SOUTH_RIGHT );
    int countFromLane_2 = howMuchVehiclesAtLaneWillDrive( 0, numberVehiclesOnLane );
    numberOfVehiclesThatWillDrive += countFromLane_2;
    int max = ( countFromLane_1 > countFromLane_2 ) ? countFromLane_1 : countFromLane_2;
    m_magicE = checkAllSubcycles( max, m_timeVector.at( 0 ) );

    /* EastMiddle */
    numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::EAST_MIDDLE );
    numberOfVehiclesThatWillDrive += howMuchVehiclesAtLaneWillDrive( 1, numberVehiclesOnLane );
    m_magicE += checkAllSubcycles( numberVehiclesOnLane, m_timeVector.at( 1 ) );

    /* WestMiddle */
    numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::WEST_MIDDLE );
    numberOfVehiclesThatWillDrive += howMuchVehiclesAtLaneWillDrive( 2, numberVehiclesOnLane );
    m_magicE += checkAllSubcycles( numberVehiclesOnLane, m_timeVector.at( 2 ) );

    return numberOfVehiclesThatWillDrive;
}

/*! This function evals how many vehicles can pass through Bladzio junction and computes magic E parameter. */
float AllSubcycleAlgorithm::evalForBladzioJunction()
{
    int numberOfVehiclesThatWillDrive = 0;

    /* Subcycle 0 */
    evalForBladzioJunctionSubcycle_0( numberOfVehiclesThatWillDrive );

    /* Subcycle 1 */
    evalForBladzioJunctionSubcycle_1( numberOfVehiclesThatWillDrive );

    /* Subcycle 2 */
    evalForBladzioJunctionSubcycle_2( numberOfVehiclesThatWillDrive );

    /* Subcycle 3 */
    evalForBladzioJunctionSubcycle_3( numberOfVehiclesThatWillDrive );

    return numberOfVehiclesThatWillDrive;
}

/*! Help function for computes how many vehicles can pass and magic E parameter for first subcycle. */
void AllSubcycleAlgorithm::evalForBladzioJunctionSubcycle_0( int& numberOfVehiclesThatWillDrive )
{
    /* South subcycle 0 */
    int numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::SOUTH_MIDDLE );
    int countFromLane_1 = howMuchVehiclesAtLaneWillDrive( 0, numberVehiclesOnLane );
    numberOfVehiclesThatWillDrive += countFromLane_1;

    numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::SOUTH_RIGHT );
    int countFromLane_2 = howMuchVehiclesAtLaneWillDrive( 0, numberVehiclesOnLane );
    numberOfVehiclesThatWillDrive += countFromLane_2;

    /* North subcycle 0 */
    numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::NORTH_MIDDLE );
    int countFromLane_3 = howMuchVehiclesAtLaneWillDrive( 0, numberVehiclesOnLane );
    numberOfVehiclesThatWillDrive += countFromLane_3;

    numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::NORTH_LEFT );
    int countFromLane_4 = howMuchVehiclesAtLaneWillDrive( 0, numberVehiclesOnLane );
    numberOfVehiclesThatWillDrive += countFromLane_4;

    int max1 = ( countFromLane_1 >= countFromLane_2 ) ? countFromLane_1 : countFromLane_2;
    int max2 = ( countFromLane_3 >= countFromLane_4 ) ? countFromLane_3 : countFromLane_4;
    int max = ( max1 >= max2 ) ? max1 : max2;
    m_magicE = checkAllSubcycles( max, m_timeVector.at( 0 ) );
}

/*! Help function for computes how many vehicles can pass and magic E parameter for second subcycle. */
void AllSubcycleAlgorithm::evalForBladzioJunctionSubcycle_1( int& numberOfVehiclesThatWillDrive )
{
    /* South subcycle 1 */
    int numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::SOUTH_LEFT );
    int countFromLane_1 = howMuchVehiclesAtLaneWillDrive( 1, numberVehiclesOnLane );
    numberOfVehiclesThatWillDrive += countFromLane_1;

    /* North subcycle 1 */
    numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::NORTH_RIGHT );
    int countFromLane_2 = howMuchVehiclesAtLaneWillDrive( 1, numberVehiclesOnLane );
    numberOfVehiclesThatWillDrive += countFromLane_2;

    int max = ( countFromLane_1 > countFromLane_2 ) ? countFromLane_1 : countFromLane_2;
    m_magicE += checkAllSubcycles( max, m_timeVector.at( 1 ) );
}

/*! Help function for computes how many vehicles can pass and magic E parameter for third subcycle. */
void AllSubcycleAlgorithm::evalForBladzioJunctionSubcycle_2( int& numberOfVehiclesThatWillDrive )
{
    /* West subcycle 2 */
    int numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::WEST_MIDDLE );
    int countFromLane_1 = howMuchVehiclesAtLaneWillDrive( 2, numberVehiclesOnLane );
    numberOfVehiclesThatWillDrive += countFromLane_1;

    numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::WEST_BOTTOM );
    int countFromLane_2 = howMuchVehiclesAtLaneWillDrive( 2, numberVehiclesOnLane );
    numberOfVehiclesThatWillDrive += countFromLane_2;

    /* East subcycle 2 */
    numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::EAST_MIDDLE );
    int countFromLane_3 = howMuchVehiclesAtLaneWillDrive( 2, numberVehiclesOnLane );
    numberOfVehiclesThatWillDrive += countFromLane_3;

    numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::EAST_TOP );
    int countFromLane_4 = howMuchVehiclesAtLaneWillDrive( 2, numberVehiclesOnLane );
    numberOfVehiclesThatWillDrive += countFromLane_4;

    int max1 = ( countFromLane_1 >= countFromLane_2 ) ? countFromLane_1 : countFromLane_2;
    int max2 = ( countFromLane_3 >= countFromLane_4 ) ? countFromLane_3 : countFromLane_4;
    int max = ( max1 >= max2 ) ? max1 : max2;
    m_magicE += checkAllSubcycles( max, m_timeVector.at( 2 ) );
}

/*! Help function for computes how many vehicles can pass and magic E parameter for fourth subcycle. */
void AllSubcycleAlgorithm::evalForBladzioJunctionSubcycle_3( int& numberOfVehiclesThatWillDrive )
{
    /* West subcycle 3 */
    int numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::WEST_TOP );
    int countFromLane_1 = howMuchVehiclesAtLaneWillDrive( 3, numberVehiclesOnLane );
    numberOfVehiclesThatWillDrive += countFromLane_1;

    /* East subcycle 3 */
    numberVehiclesOnLane = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::EAST_BOTTOM );
    int countFromLane_2 = howMuchVehiclesAtLaneWillDrive( 3, numberVehiclesOnLane );
    numberOfVehiclesThatWillDrive += countFromLane_2;

    int max = ( countFromLane_1 > countFromLane_2 ) ? countFromLane_1 : countFromLane_2;
    m_magicE += checkAllSubcycles( max, m_timeVector.at( 3 ) );
}

int AllSubcycleAlgorithm::howMuchVehiclesAtLaneWillDrive( const int &subcycleId, const int& numberVehiclesOnLane )
{
    int score = 0;
    if( numberVehiclesOnLane <= m_timeVector.at( subcycleId ) )
    {
        score = numberVehiclesOnLane;
    }
    else{
        score = m_timeVector.at( subcycleId );
    }
    return score;
}

void AllSubcycleAlgorithm::setAlphaParam( const int& numberOfVehiclesThatWillDrive )
{
    int minValue = m_junction->currentNumberOfVehicles() * 0.7;
    int maxValue = m_junction->currentNumberOfVehicles() * 0.8;

    if( numberOfVehiclesThatWillDrive >= minValue && numberOfVehiclesThatWillDrive <= maxValue )
        m_alpha = 1;
    else
        m_alpha = 0;
}

/*! Reward and punishment function. */
float AllSubcycleAlgorithm::checkAllSubcycles( const int& vehiclesCountAtLane, const int& time )
{
    int diff = time - vehiclesCountAtLane;
    if( diff < 0 )
        diff = 0;

    if( vehiclesCountAtLane > 0 && time > 0 )
    {
        if( diff <= 2 )
        return 1000;
        else
        return -1000 * diff;
    }
    else if( vehiclesCountAtLane > 0 && time == 0 )
    {
        return -100000 - vehiclesCountAtLane;
    }
    else if( vehiclesCountAtLane == 0 && time > 0 )
    {
        return -100000 - ( time << 3 );
    }
    else if( vehiclesCountAtLane == 0 && time == 0 )
    {
        return 1000;
    }
    else
    return 0;
}

void AllSubcycleAlgorithm::clearAll()
{
    m_alpha = 0;
    m_magicE = 0;
    m_timeVector.clear();
    m_totalTimes = 0.0;
    m_numberOfVehiclesThatWillDrive = 0.0;
}

QVector<int> AllSubcycleAlgorithm::normalTraffic()
{
    QVector<int> vector;

    switch( m_junction->junctionType() )
    {
    case Junction::BLADZIO:
        vector = normalTrafficForBladzioJunction();
        break;
    case Junction::SIMPLE:
        vector = normalTrafficForSimpleJunction();
        break;
    default:
        break;
    }
    return vector;
}

QVector<int> AllSubcycleAlgorithm::normalTrafficForBladzioJunction()
{
    QVector<int> vector;

    QList<VehicleCountManager::Lane> listWithFourLanes;
    QList<VehicleCountManager::Lane> listWithTwoLanes;

    /* First subcycle */
    listWithFourLanes << VehicleCountManager::SOUTH_MIDDLE << VehicleCountManager::SOUTH_RIGHT
                         << VehicleCountManager::NORTH_MIDDLE << VehicleCountManager::NORTH_LEFT;
    vector.append( maxTimeFromFourLanes( listWithFourLanes ) );
    listWithFourLanes.clear();

    /* Second subcycle */
    listWithTwoLanes << VehicleCountManager::SOUTH_LEFT << VehicleCountManager::NORTH_RIGHT;
    vector.append( maxTimeFromTwoLanes( listWithTwoLanes ) );
    listWithTwoLanes.clear();

    /* Third subcycle */
    listWithFourLanes << VehicleCountManager::WEST_MIDDLE << VehicleCountManager::WEST_BOTTOM
                         << VehicleCountManager::EAST_MIDDLE << VehicleCountManager::EAST_BOTTOM;
    vector.append( maxTimeFromFourLanes( listWithFourLanes ) );

    /* Fourth subcycle */
    listWithTwoLanes << VehicleCountManager::WEST_TOP << VehicleCountManager::EAST_BOTTOM;
    vector.append( maxTimeFromTwoLanes( listWithTwoLanes ) );

    return vector;
}

QVector<int> AllSubcycleAlgorithm::normalTrafficForSimpleJunction()
{
    QVector<int> vector;
    int time = 0;

    /* First subcycle */
    QList<VehicleCountManager::Lane> listWithTwoLanes;
    listWithTwoLanes << VehicleCountManager::SOUTH_LEFT << VehicleCountManager::SOUTH_RIGHT;
    vector.append( maxTimeFromTwoLanes( listWithTwoLanes ) );

    /* Second subcycle */
    time = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::EAST_MIDDLE );
    vector.append( time* 1000 );

    /* Third subcycle */
    time = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::WEST_MIDDLE );
    vector.append( time * 1000 );

    return vector;
}


/*! Help function for Bladzio Junction for four opposite lanes.
    Computes times when traffic at junction is normal. */
int AllSubcycleAlgorithm::maxTimeFromFourLanes( QList<VehicleCountManager::Lane> &list )
{
    int timeMiddle_1 = 0, timeLeftOrRight_1 = 0, timeMiddle_2 = 0, timeLeftOrRight_2 = 0;
    int max1 = 0, max2 = 0;

    timeMiddle_1 = VehicleCountManager::vehicleCountOnLane( m_junction, list.at( 0 ) );
    timeLeftOrRight_1 = VehicleCountManager::vehicleCountOnLane( m_junction, list.at( 1 ) );
    timeMiddle_2 = VehicleCountManager::vehicleCountOnLane( m_junction, list.at( 2 ) );
    timeLeftOrRight_2 = VehicleCountManager::vehicleCountOnLane( m_junction, list.at( 3 ) );

    max1 = ( timeMiddle_1 > timeLeftOrRight_1 ) ? timeMiddle_1 : timeLeftOrRight_1;
    max2 = ( timeMiddle_2 > timeLeftOrRight_2 ) ? timeMiddle_2 : timeLeftOrRight_2;

    return ( ( max1 > max2 ) ? max1 : max2 ) * 1000;
}

/*! Help function for Bladzio Junction for two opposite lanes.
    Computes times when traffic at junction is normal. */
int AllSubcycleAlgorithm::maxTimeFromTwoLanes( QList<VehicleCountManager::Lane> &list )
{
    int timeTop = 0, timeBottom = 0;

    timeTop = VehicleCountManager::vehicleCountOnLane( m_junction, list.at( 0 ) );
    timeBottom = VehicleCountManager::vehicleCountOnLane( m_junction, list.at( 1 ) );

    return ( ( timeTop > timeBottom ) ? timeTop : timeBottom ) * 1000;
}

/*! Calls for simple junction when all values in timeVector are equal zero. Then all are set to 3 sek. */
void AllSubcycleAlgorithm::exceptionForSimple( QVector<int> &vector )
{
    if( vector.at( 0 ) == 0 && vector.at( 1 ) == 0 && vector.at( 2 ) == 0 )
    {
        for( int i = 0; i < vector.size(); i++ )
            vector[ i ] = 3000;
    }
}
/*! Calls for Bladzio junction when all values in timeVector are equal zero. Then all are set to 3 sek. */
void AllSubcycleAlgorithm::exceptionForBladzio( QVector<int> &vector )
{
    if( vector.at( 0 ) == 0 && vector.at( 1 ) == 0 && vector.at( 2 ) == 0 && vector.at( 3 ) == 0)
    {
        for( int i = 0; i < vector.size(); i++ )
            vector[ i ] = 3000;
    }
}
