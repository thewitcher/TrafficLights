#include "algorithm-manager.h"
#include "../Settings/settings.h"
#include "normal-algorithm.h"
#include "one-subcycle-algorithm.h"
#include "all-subcycle-algorithm.h"
#include "../Ui/TrafficLights_manager/junction.h"

AlgorithmManager::AlgorithmManager( Junction* junction ):
    QObject( NULL ),
    m_baseAlgorithm( NULL ),
    m_junction( junction ),
    m_finished( true )
{
    updateAlgorithm();

    Q_ASSERT( m_baseAlgorithm != NULL );

    connect( m_baseAlgorithm, SIGNAL(finished()), this, SLOT(timeVectorChanged()) );
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
    if( m_finished == true )
    {
        m_baseAlgorithm->start();
        m_finished = false;
    }
}

void AlgorithmManager::updateAlgorithm()
{
    QString type = Settings::settingsInstance().value( "ALGORITHM_TYPE", "NORMAL" ).toString();

    if( type == "NORMAL" )
    {
        m_baseAlgorithm = new NormalAlgorithm( m_junction );
    }
    else if( type == "ONE_SUBCYCLE_ALGORITHM" )
    {
        m_baseAlgorithm = new OneSubcycleAlgorithm( m_junction );
    }
    else if( type == "ALL_SUBCYCLE_ALGORITHM" )
    {
        m_baseAlgorithm = new AllSubcycleAlgorithm( m_junction );
    }
}

void AlgorithmManager::timeVectorChanged()
{
    m_finished = true;
    emit changeTimeVector( m_baseAlgorithm->timeVector() );
}
