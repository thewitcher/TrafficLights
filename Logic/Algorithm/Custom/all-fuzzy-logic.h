#ifndef ALLFUZZYLOGIC_H
#define ALLFUZZYLOGIC_H

#include "base-algorithm.h"
#include <QHash>

namespace fl {
class RuleBlock;
}

class Junction;

class AllFuzzyLogic : public BaseAlgorithm
{
public:
    AllFuzzyLogic( Junction *junction, const QString& algorithmType );
    QVector<int> startAlgorithm();
    enum NumberOfCycle { FIRST, SECOND, THIRD, FOURTH };
    enum Term { FIRST_TERM, SECOND_TERM };
    enum Set { SMALL_SET, MEDIUM_SET, LARGE_SET };


private:
    int m_runCount, m_nullVectorCount, m_start, m_medium, m_end;
    bool m_firstRun;
    int m_vehiclesCountAtLane, m_vehiclesCountAtJunction;

    void vehiclesCountForSimpleJunction();
    void vehiclesCountForBladzioJunction();

    void setNumberOfCycleForSimpleJunction();
    void setNumberOfCycleForBladzioJunction();
    NumberOfCycle m_numberOfCycle;


    QVector<int> returnTimeVectorForSimple( const int& value );
    QVector<int> returnTimeVectorForBladzio( const int& value );


    void exceptionForSimpleJunction( QVector<int>& vector );
    void exceptionForBladzioJunction( QVector<int>& vector );
    int startSimulation();
    Term m_term;
    Set m_set;
    QHash<int,float> m_hash;
    void whichSet( const int& value );
    void whichTerm( const int& value );
    int startDefuzzy( const float& value );
    void setTerm( fl::RuleBlock* block );
};

#endif // ALLFUZZYLOGIC_H
