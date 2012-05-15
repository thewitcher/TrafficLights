#include "all-fuzzy-logic.h"

AllFuzzyLogic::AllFuzzyLogic( Junction *junction ): BaseAlgorithm( junction, "ALL_FUZZY_LOGIC" )
{
}

QVector<int> AllFuzzyLogic::startAlgorithm()
{
    QVector<int> vector ;
    vector << 3000 << 4000 << 5000 << 6000 ;

    return vector;
}
