#ifndef ALLFUZZYLOGIC_H
#define ALLFUZZYLOGIC_H

#include "base-algorithm.h"
#include <QMap>
#include <QMultiHash>

class Junction;

class AllFuzzyLogic : public BaseAlgorithm
{
public:
    AllFuzzyLogic( Junction *junction );
    QVector<int> startAlgorithm();
    enum GroupForLaneAtJunction { SMALL_AT_SIMPLE_JUNCTION, MEDIUM_AT_SIMPLE_JUNCTION, LARGE_AT_SIMPLE_JUNCTION,
                                       SMALL_AT_BLADZIO_JUNCTION, MEDIUM_AT_BLADZIO_JUNCTION, LARGE_AT_BLADZIO_JUNCTION };
    enum GroupForCrossroads { SMALL_AT_SIMPLE_CROSSROADS, MEDIUM_AT_SIMPLE_CROSSROADS, LARGE_AT_SIMPLE_CROSSROADS,
                                  SMALL_AT_BLADZIO_CROSSROADS, MEDIUM_AT_BLADZIO_CROSSROADS, LARGE_AT_BLADZIO_CROSSROADS};
    enum NumberOfCycle { FIRST, SECOND, THIRD, FOURTH };
    enum TimeForSubcycle { SMALL, MEDIUM, LARGE };


private:
    int runCount, nullVectorCount;
    bool firstRun, lastRun;
    float m_startValueForLane, m_medianValueForLane, m_finalValueForLane;
    float m_vehiclesCountAtLane, m_vehiclesCountAtJunction;
    QMap<GroupForLaneAtJunction, float> m_degreeOfMembershipForTheFirstSet;
    QMap<GroupForCrossroads, float> m_degreeOfMembershipForTheSecondSet;
    QMultiHash<TimeForSubcycle,float> m_fuzzyActions;
    float fuzzyValueForTriangle( const int& value );
    float fuzzyValueForTrapeze( const int& value );
    int inverseFuzzyValue( const float& value );
    void setGroupValuesForLaneAtSimpleJunction( const GroupForLaneAtJunction& group );
    void setGroupValuesForSimpleJunction( const GroupForCrossroads& group );

    void setGroupValuesForLaneAtBladzioJunction( const GroupForLaneAtJunction& group );
    void setGroupValuesForBladzioJunction( const GroupForCrossroads& group );

    void setGroupValuesForFuzzyTime( const TimeForSubcycle& group );

    void vehiclesCountForSimpleJunction();
    void vehiclesCountForBladzioJunction();
    NumberOfCycle m_numberOfCycle;
    GroupForLaneAtJunction m_groupForLaneAtJunction;
    GroupForCrossroads m_groupForCrossroads;
    void setNumberOfCycleForSimpleJunction();
    void setNumberOfCycleForBladzioJunction();

    void baseOfRulesForSimpleJunction();
    void baseOfRulesForBladzioJunction();
    QList<TimeForSubcycle> baseOfRules();
    void fuzzyActions();
    QVector<int> sharpening();
    QHash<TimeForSubcycle,float> m_afterFuzzyActions;
    void startFuzzyForSimple();
    void startFuzzyForBladzio();

    QVector<int> returnTimeVectorForSimple( const int& value );
    QVector<int> returnTimeVectorForBladzio( const int& value );
    QVector<int> returnTimeVector( const int& value );

    void clearAll();


};

#endif // ALLFUZZYLOGIC_H
