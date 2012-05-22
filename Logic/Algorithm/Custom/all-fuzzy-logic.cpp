#include "all-fuzzy-logic.h"
#include "../Ui/TrafficLights_manager/junction.h"
#include "../Ui/TrafficLights_manager/vehicle-count-manager.h"

AllFuzzyLogic::AllFuzzyLogic( Junction *junction ): BaseAlgorithm( junction, "ALL_FUZZY_LOGIC" ),
  runCount( 0 ),
  nullVectorCount( 0 ),
  firstRun( false )
{
}

QVector<int> AllFuzzyLogic::startAlgorithm()
{
    clearAll();
    QVector<int> vector ;
    vector << 3000 << 4000 << 5000 << 6000 ;
    if( firstRun == false )
    {
        vector.clear();
        vector << 3000 << 3000 << 3000 << 3000;
        firstRun = true;
        return vector;
    }

    switch( m_junction->junctionType() )
    {
    case Junction::SIMPLE:
        setNumberOfCycleForSimpleJunction();
        if(m_junction->id() == 6)
        qDebug() << "S_RUN_COUNT: " << runCount ;
        vehiclesCountForSimpleJunction();
        startFuzzyForSimple();
        baseOfRulesForSimpleJunction();
        fuzzyActions();
        vector = sharpening();
        if(m_junction->id() == 6)
            qDebug() << vector;
        break;
    case Junction::BLADZIO:
//        setNumberOfCycleForBladzioJunction();
//        vehiclesCountForBladzioJunction();
//        startFuzzyForBladzio();
//        baseOfRulesForBladzioJunction();
//        fuzzyActions();
//        vector = sharpening();
        break;
    default:
        break;
    }

    runCount++;
    if( vector.at( 0 ) == 0 && vector.at( 1 )== 0 && vector.at( 2 ) == 0 && nullVectorCount < 3 )
    {
        nullVectorCount++;
        if(m_junction->id() == 6)
        qDebug() << "nul < 3";
        vector = startAlgorithm();
    }
    else if( vector.at( 0 ) == 0 && vector.at( 1 )== 0 && vector.at( 2 ) == 0 && nullVectorCount == 3 )
    {
        vector.clear();
        nullVectorCount = 0;
        vector << 0 << 4000 << 0 << 0;
    }

    return vector;
}

void AllFuzzyLogic::startFuzzyForSimple()
{
    /* For Lane */
    setGroupValuesForLaneAtSimpleJunction( SMALL_AT_SIMPLE_JUNCTION );
    m_degreeOfMembershipForTheFirstSet.insert( SMALL_AT_SIMPLE_JUNCTION, fuzzyValueForTriangle( m_vehiclesCountAtLane ) );

    setGroupValuesForLaneAtSimpleJunction( MEDIUM_AT_SIMPLE_JUNCTION );
    m_degreeOfMembershipForTheFirstSet.insert( MEDIUM_AT_SIMPLE_JUNCTION, fuzzyValueForTriangle( m_vehiclesCountAtLane ) );

    setGroupValuesForLaneAtSimpleJunction( LARGE_AT_SIMPLE_JUNCTION );
    m_degreeOfMembershipForTheFirstSet.insert( LARGE_AT_SIMPLE_JUNCTION, fuzzyValueForTrapeze( m_vehiclesCountAtLane ) );

    /* For Junction */
    setGroupValuesForSimpleJunction( SMALL_AT_SIMPLE_CROSSROADS );
    m_degreeOfMembershipForTheSecondSet.insert( SMALL_AT_SIMPLE_CROSSROADS, fuzzyValueForTriangle( m_vehiclesCountAtJunction ) );

    setGroupValuesForSimpleJunction( MEDIUM_AT_SIMPLE_CROSSROADS );
    m_degreeOfMembershipForTheSecondSet.insert( MEDIUM_AT_SIMPLE_CROSSROADS, fuzzyValueForTriangle( m_vehiclesCountAtJunction ) );

    setGroupValuesForSimpleJunction( LARGE_AT_SIMPLE_CROSSROADS );
    m_degreeOfMembershipForTheSecondSet.insert( LARGE_AT_SIMPLE_CROSSROADS, fuzzyValueForTrapeze( m_vehiclesCountAtJunction ) );
}

void AllFuzzyLogic::startFuzzyForBladzio()
{
    /* For Lane */
    setGroupValuesForLaneAtBladzioJunction( SMALL_AT_BLADZIO_JUNCTION );
    m_degreeOfMembershipForTheFirstSet.insert( SMALL_AT_BLADZIO_JUNCTION, fuzzyValueForTriangle( m_vehiclesCountAtLane ) );

    setGroupValuesForLaneAtBladzioJunction( MEDIUM_AT_BLADZIO_JUNCTION );
    m_degreeOfMembershipForTheFirstSet.insert( MEDIUM_AT_BLADZIO_JUNCTION, fuzzyValueForTriangle( m_vehiclesCountAtLane ) );

    setGroupValuesForLaneAtBladzioJunction( LARGE_AT_BLADZIO_JUNCTION );
    m_degreeOfMembershipForTheFirstSet.insert( LARGE_AT_BLADZIO_JUNCTION, fuzzyValueForTrapeze( m_vehiclesCountAtLane ) );

    /* For Junction */
    setGroupValuesForBladzioJunction( SMALL_AT_BLADZIO_CROSSROADS );
    m_degreeOfMembershipForTheSecondSet.insert( SMALL_AT_BLADZIO_CROSSROADS, fuzzyValueForTriangle( m_vehiclesCountAtJunction ) );

    setGroupValuesForBladzioJunction( MEDIUM_AT_BLADZIO_CROSSROADS );
    m_degreeOfMembershipForTheSecondSet.insert( MEDIUM_AT_BLADZIO_CROSSROADS, fuzzyValueForTriangle( m_vehiclesCountAtJunction ) );

    setGroupValuesForBladzioJunction( LARGE_AT_BLADZIO_CROSSROADS );
    m_degreeOfMembershipForTheSecondSet.insert( LARGE_AT_BLADZIO_CROSSROADS, fuzzyValueForTrapeze( m_vehiclesCountAtJunction ) );
}

void AllFuzzyLogic::fuzzyActions()
{
    QMultiHash<TimeForSubcycle, float>::iterator it = m_fuzzyActions.begin();
    QMultiHash<TimeForSubcycle,float>::iterator it2 = m_fuzzyActions.begin();

    float max = it.value();
    while( it2 != m_fuzzyActions.end() )
    {
        max = it.value();
        while(it.key() == it2.key())
        {
            if( max < it2.value() )
                max = it2.value();

            ++it2;
        }
        m_afterFuzzyActions.insert(it.key(),max);
        it = it2;
    }
    if(m_junction->id() == 6)
    qDebug() << "afterfuzzy: " << m_afterFuzzyActions;
}

QVector<int> AllFuzzyLogic::sharpening()
{
    QVector<int> vector;
    QMultiHash<TimeForSubcycle, float>::iterator it = m_afterFuzzyActions.begin();
    QMultiHash<TimeForSubcycle, float>::iterator itWhichSet = it;

    float max = it.value();
    while( it != m_afterFuzzyActions.end() )
    {
        if( max < it.value() )
        {
            max = it.value();
            itWhichSet = it;
        }
        ++it;
    }
    if(m_junction->id() == 6)
    qDebug() << "max: " << max << "itWhichSet: " << itWhichSet.key();
    setGroupValuesForFuzzyTime( itWhichSet.key() ); // tu byl max
    vector = returnTimeVector( inverseFuzzyValue( max ) );
    return vector;
}

QVector<int> AllFuzzyLogic::returnTimeVector( const int &value )
{
    QVector<int> vector;
    switch( m_junction->junctionType() )
    {
    case Junction::SIMPLE:
        vector = returnTimeVectorForSimple( value );
    case Junction::BLADZIO:
        vector = returnTimeVectorForBladzio( value );
    default:
        break;
    }
    return vector;
}


QVector<int> AllFuzzyLogic::returnTimeVectorForSimple( const int &value )
{
    QVector<int> vector;
    switch( runCount )
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
        break;
    }
    return vector;
}

QVector<int> AllFuzzyLogic::returnTimeVectorForBladzio( const int &value )
{
    QVector<int> vector;
    switch( runCount )
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
    default:
        break;
    }
    return vector;
}

void AllFuzzyLogic::baseOfRulesForSimpleJunction()
{

    if(m_junction->id() == 6){
    qDebug() << "Reguly: Lane: " << m_degreeOfMembershipForTheFirstSet;
    qDebug() << "Reguly: Junction: " << m_degreeOfMembershipForTheSecondSet;
    }

    QMap<GroupForLaneAtJunction,float>::iterator itFirstSet = m_degreeOfMembershipForTheFirstSet.begin();
    while( itFirstSet != m_degreeOfMembershipForTheFirstSet.end() )
    {
        m_groupForLaneAtJunction = itFirstSet.key();
        float value1 = itFirstSet.value();
        QMap<GroupForCrossroads,float>::iterator itSecondSet = m_degreeOfMembershipForTheSecondSet.begin();
        while( itSecondSet != m_degreeOfMembershipForTheSecondSet.end() )
        {
            m_groupForCrossroads = itSecondSet.key();
            float value2 = itSecondSet.value();

            float min = ( value1 < value2 ) ? value1 : value2;

            /* Base for simple junction */
            if( m_groupForLaneAtJunction == SMALL_AT_SIMPLE_JUNCTION &&
                    m_groupForCrossroads == SMALL_AT_SIMPLE_CROSSROADS )
            {
                m_fuzzyActions.insert( SMALL, min );
            }
            if( m_groupForLaneAtJunction == SMALL_AT_SIMPLE_JUNCTION &&
                    m_groupForCrossroads == MEDIUM_AT_SIMPLE_CROSSROADS )
            {
                m_fuzzyActions.insert( SMALL, min );
            }
            if( m_groupForLaneAtJunction == SMALL_AT_SIMPLE_JUNCTION &&
                    m_groupForCrossroads == LARGE_AT_SIMPLE_CROSSROADS )
            {
                m_fuzzyActions.insert( SMALL, min );
            }
            if( m_groupForLaneAtJunction == MEDIUM_AT_SIMPLE_JUNCTION &&
                    m_groupForCrossroads == SMALL_AT_SIMPLE_CROSSROADS )
            {
                m_fuzzyActions.insert( MEDIUM, min );
            }
            if( m_groupForLaneAtJunction == MEDIUM_AT_SIMPLE_JUNCTION &&
                    m_groupForCrossroads == MEDIUM_AT_SIMPLE_CROSSROADS )
            {
                m_fuzzyActions.insert( MEDIUM, min );
            }
            if( m_groupForLaneAtJunction == MEDIUM_AT_SIMPLE_JUNCTION &&
                    m_groupForCrossroads == LARGE_AT_SIMPLE_CROSSROADS )
            {
                m_fuzzyActions.insert( MEDIUM, min );
            }
            if( m_groupForLaneAtJunction == LARGE_AT_SIMPLE_JUNCTION &&
                    m_groupForCrossroads == SMALL_AT_SIMPLE_CROSSROADS )
            {
                m_fuzzyActions.insert( LARGE, min );
            }
            if( m_groupForLaneAtJunction == LARGE_AT_SIMPLE_JUNCTION &&
                    m_groupForCrossroads == MEDIUM_AT_SIMPLE_CROSSROADS )
            {
                m_fuzzyActions.insert( MEDIUM, min );
            }
            if( m_groupForLaneAtJunction == LARGE_AT_SIMPLE_JUNCTION &&
                    m_groupForCrossroads == LARGE_AT_SIMPLE_CROSSROADS )
            {
                m_fuzzyActions.insert( MEDIUM, min );
            }
            ++itSecondSet;
        }
        ++itFirstSet;
    }
    if( m_junction->id() == 6 )
        qDebug() << m_fuzzyActions;
}

void AllFuzzyLogic::baseOfRulesForBladzioJunction()
{

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
        if(m_junction->id() == 6)
            qDebug() << "first";
        break;
    case SECOND:
        m_vehiclesCountAtLane = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::EAST_MIDDLE );
        if(m_junction->id() == 6)
            qDebug() << "second";
        break;
    case THIRD:
        m_vehiclesCountAtLane = VehicleCountManager::vehicleCountOnLane( m_junction, VehicleCountManager::WEST_MIDDLE );
        if(m_junction->id() == 6)
            qDebug() << "third";
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

void AllFuzzyLogic::setNumberOfCycleForSimpleJunction()
{
    if( runCount == 3 )
        runCount = 0;
    switch( runCount )
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

void AllFuzzyLogic::setNumberOfCycleForBladzioJunction()
{
    if( runCount == 4 )
        runCount = 0;
    switch( runCount )
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

float AllFuzzyLogic::fuzzyValueForTriangle( const int& value )
{
    float result = 0.0;

    if(m_junction->id() == 6)
        qDebug() << "trojkat: "<< m_startValueForLane << ", " << m_medianValueForLane <<", "<<m_finalValueForLane <<
                    ", value: " << value;
    if( value <= m_startValueForLane )
    {
        result = 0.0;
    }
    else if( value > m_startValueForLane && value <= m_medianValueForLane )
    {
        result = ( value - m_startValueForLane ) / ( m_medianValueForLane - m_startValueForLane );
    }
    else if( value > m_medianValueForLane && value <= m_finalValueForLane )
    {
        result = ( m_finalValueForLane - value ) / ( m_finalValueForLane - m_medianValueForLane );
    }
    else if( value > m_finalValueForLane )
    {
        result = 0.0;
    }

    if(m_junction->id() == 6)
        qDebug() << result;
    return result;
}

float AllFuzzyLogic::fuzzyValueForTrapeze( const int &value )
{
    float result = 0.0;
    if(m_junction->id() == 6)
        qDebug() << "trapez: "<< m_startValueForLane << ", " << m_medianValueForLane <<", "<<m_finalValueForLane <<
                    ", value: " << value;

    if( value <= m_startValueForLane )
    {
        result = 0.0;
    }
    else if( value > m_startValueForLane && value <= m_medianValueForLane )
    {
        result = ( value - m_startValueForLane ) / ( m_medianValueForLane - m_startValueForLane );
    }
    else if( value > m_medianValueForLane && value <= m_finalValueForLane )
    {
        result = 1.0;
    }
    if(m_junction->id() == 6)
        qDebug() << result;
    return result;
}

int AllFuzzyLogic::inverseFuzzyValue( const float &value ) // do zrobienia
{
    int max, max2, score = 0;

    max = (value * ( m_medianValueForLane - m_startValueForLane ) ) + m_startValueForLane;
//    max2 = ( value * ( m_finalValueForLane - m_medianValueForLane ) - m_finalValueForLane ) * (-1);
//    return score = ( max+max2 ) / 2;
    return max;
}

void AllFuzzyLogic::setGroupValuesForSimpleJunction( const GroupForCrossroads &group )
{
    switch( group )
    {
    case AllFuzzyLogic::SMALL_AT_SIMPLE_CROSSROADS:
        m_startValueForLane = 0, m_medianValueForLane = 15, m_finalValueForLane = 30;
        break;
    case AllFuzzyLogic::MEDIUM_AT_SIMPLE_CROSSROADS:
        m_startValueForLane = 20, m_medianValueForLane = 35, m_finalValueForLane = 50;
        break;
    case AllFuzzyLogic::LARGE_AT_SIMPLE_CROSSROADS:
        m_startValueForLane = 40, m_medianValueForLane = 60, m_finalValueForLane = 300;
        break;
    default:
        break;
    }
}

void AllFuzzyLogic::setGroupValuesForLaneAtSimpleJunction( const GroupForLaneAtJunction &group )
{
    switch( group )
    {
    case AllFuzzyLogic::SMALL_AT_SIMPLE_JUNCTION:
        m_startValueForLane = 0, m_medianValueForLane = 4, m_finalValueForLane = 10;
        break;
    case AllFuzzyLogic::MEDIUM_AT_SIMPLE_JUNCTION:
        m_startValueForLane = 7, m_medianValueForLane = 13, m_finalValueForLane = 20;
        break;
    case AllFuzzyLogic::LARGE_AT_SIMPLE_JUNCTION:
        m_startValueForLane = 15, m_medianValueForLane = 30, m_finalValueForLane = 300;
        break;
    default:
        break;
    }
}

void AllFuzzyLogic::setGroupValuesForLaneAtBladzioJunction( const GroupForLaneAtJunction &group )
{
    switch( group )
    {
    case AllFuzzyLogic::SMALL_AT_BLADZIO_JUNCTION:
        m_startValueForLane = 0, m_medianValueForLane = 0, m_finalValueForLane = 15;
        break;
    case AllFuzzyLogic::MEDIUM_AT_BLADZIO_JUNCTION:
        m_startValueForLane = 10, m_medianValueForLane = 17, m_finalValueForLane = 25;
        break;
    case AllFuzzyLogic::LARGE_AT_BLADZIO_JUNCTION:
        m_startValueForLane = 20, m_medianValueForLane = 35, m_finalValueForLane = 35;
        break;
    default:
        break;
    }
}

void AllFuzzyLogic::setGroupValuesForBladzioJunction( const GroupForCrossroads &group )
{
    switch( group )
    {
    case AllFuzzyLogic::SMALL_AT_BLADZIO_JUNCTION:
        m_startValueForLane = 0, m_medianValueForLane = 0, m_finalValueForLane = 40;
        break;
    case AllFuzzyLogic::MEDIUM_AT_BLADZIO_JUNCTION:
        m_startValueForLane = 30, m_medianValueForLane = 50, m_finalValueForLane = 70;
        break;
    case AllFuzzyLogic::LARGE_AT_BLADZIO_JUNCTION:
        m_startValueForLane = 60, m_medianValueForLane = 120, m_finalValueForLane = 120;
        break;
    default:
        break;
    }
}

void AllFuzzyLogic::setGroupValuesForFuzzyTime( const TimeForSubcycle& group )
{
    switch( group )
    {
    case AllFuzzyLogic::SMALL:
        m_startValueForLane = 0, m_medianValueForLane = 10, m_finalValueForLane = 15;
        break;
    case AllFuzzyLogic::MEDIUM:
        m_startValueForLane = 10, m_medianValueForLane = 20, m_finalValueForLane = 30;
        break;
    case AllFuzzyLogic::LARGE:
        m_startValueForLane = 25, m_medianValueForLane = 43, m_finalValueForLane = 60;
        break;
    default:
        break;
    }
}

void AllFuzzyLogic::clearAll()
{
    m_degreeOfMembershipForTheFirstSet.clear();
    m_degreeOfMembershipForTheSecondSet.clear();
    m_fuzzyActions.clear();
    m_afterFuzzyActions.clear();
}
