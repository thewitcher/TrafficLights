#include "algorithm-manager.h"
#include "../Settings/settings.h"
#include "normal-algorithm.h"
#include "one-subcycle-algorithm.h"
#include "all-subcycle-algorithm.h"
#include "all-fuzzy-logic.h"
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
        m_baseAlgorithm = new NormalAlgorithm( junction );
    }
    else if( type == "ONE_SUBCYCLE_ALGORITHM" )
    {
        m_baseAlgorithm = new OneSubcycleAlgorithm( junction );
    }
    else if( type == "ALL_SUBCYCLE_ALGORITHM" )
    {
        m_baseAlgorithm = new AllSubcycleAlgorithm( junction );
    }
    else if( type == "ALL_FUZZY_LOGIC" )
    {
        m_baseAlgorithm = new AllFuzzyLogic( junction );
    }
}
