#include "algorithm-manager.h"
#include "../Settings/settings.h"
#include "normal-algorithm.h"
#include "one-subcycle-algorithm.h"
#include "all-subcycle-algorithm.h"
#include "all-fuzzy-logic.h"
#include "one-fuzzy-logic.h"
#include "../Ui/TrafficLights_manager/junction.h"

AlgorithmManager::AlgorithmManager( Junction* junction ):
    QObject( NULL ),
    m_baseAlgorithm( NULL )
{
    updateAlgorithm( junction );
}

AlgorithmManager::~AlgorithmManager()
{
    if( m_baseAlgorithm )
    {
        delete m_baseAlgorithm;
    }
}

void AlgorithmManager::start()
{
    m_baseAlgorithm->start();
}

void AlgorithmManager::updateAlgorithm( Junction* junction )
{
    QString type = Settings::takeValue( "ALGORITHM_TYPE", "GENERAL" , "NORMAL" ).toString();

    if( type == "NORMAL" )
    {
        m_baseAlgorithm = new NormalAlgorithm( junction, "NORMAL" );
    }
    else if( type == "ONE_SUBCYCLE_ALGORITHM" )
    {
        m_baseAlgorithm = new OneSubcycleAlgorithm( junction, "ONE_SUBCYCLE_ALGORITHM" );
    }
    else if( type == "ALL_SUBCYCLE_ALGORITHM" )
    {
        m_baseAlgorithm = new AllSubcycleAlgorithm( junction, "ALL_SUBCYCLE_ALGORITHM" );
    }
    else if( type == "ALL_FUZZY_LOGIC" )
    {
        m_baseAlgorithm = new AllFuzzyLogic( junction, "ALL_FUZZY_LOGIC" );
    }
    else if( type == "ONE_FUZZY_LOGIC" )
    {
        m_baseAlgorithm = new OneFuzzyLogic( junction, "ONE_FUZZY_LOGIC" );
    }
}
