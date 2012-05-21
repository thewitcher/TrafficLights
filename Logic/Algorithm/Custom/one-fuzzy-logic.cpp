#include "one-fuzzy-logic.h"
#include "../Ui/TrafficLights_manager/junction.h"

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

    return vector;
}


int OneFuzzyLogic::estimateGreenLight()
{
    return 5000;
}
