#include "all-fuzzy-logic.h"

AllFuzzyLogic::AllFuzzyLogic( Junction *junction, const QString& algorithmType ): BaseAlgorithm( junction, algorithmType )
{
}

QVector<int> AllFuzzyLogic::startAlgorithm()
{
    QVector<int> vector ;
    vector << 3000 << 4000 << 5000 << 6000 ;

    return vector;
}
