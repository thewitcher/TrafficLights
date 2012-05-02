#include "algorithm-manager.h"
#include "../Settings/settings.h"
#include "normal-algorithm.h"
#include "one-subcycle-algorithm.h"
#include "../Ui/TrafficLights_manager/junction.h"

AlgorithmManager::AlgorithmManager( Junction* junction ):
    m_baseAlgorithm( NULL ),
    m_junction( junction )
{
    updateAlgorithm();
}

AlgorithmManager::~AlgorithmManager()
{
    if( m_baseAlgorithm )
    {
        delete m_baseAlgorithm;
    }
}

QVector<int> AlgorithmManager::start()
{
    return m_baseAlgorithm->start( m_junction );
}

void AlgorithmManager::updateAlgorithm()
{
    QString type = Settings::settingsInstance().value( "ALGORITHM_TYPE", "ONE_SUBCYCLE_ALGORITHM" ).toString();

    if( type == "NORMAL" )
    {
        m_baseAlgorithm = new NormalAlgorithm;
    }
    else if( type == "ONE_SUBCYCLE_ALGORITHM" )
    {
        m_baseAlgorithm = new OneSubcycleAlgorithm;
    }
    else if( type == "ALL_SUBCYCLE_ALGORITHM" )
    {
        m_baseAlgorithm = NULL;
    }
}
