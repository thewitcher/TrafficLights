#include "algorithm-manager.h"
#include "../Settings/settings.h"
#include "normal-algorithm.h"

AlgorithmManager::AlgorithmManager():
    m_baseAlgorithm( NULL )
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
    return m_baseAlgorithm->start();
}

void AlgorithmManager::updateAlgorithm()
{
    QString type = Settings::settingsInstance().value( "ALGORITHM_TYPE", "NORMAL" ).toString();

    if( type == "NORMAL" )
    {
        m_baseAlgorithm = new NormalAlgorithm;
    }
    else if( type == "ONE_SUBCYCLE_ALGORITHM" )
    {
        m_baseAlgorithm = NULL;
    }
    else if( type == "ALL_SUBCYCLE_ALGORITHM" )
    {
        m_baseAlgorithm = NULL;
    }
}
