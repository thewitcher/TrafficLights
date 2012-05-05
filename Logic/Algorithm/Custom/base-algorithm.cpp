#include "base-algorithm.h"
#include "../Ui/TrafficLights_manager/junction.h"

BaseAlgorithm::BaseAlgorithm( Junction *junction ):
    QThread( NULL ),
    m_genomeSize( 10 ),
    m_replacementProbability( 0.5 ),
    m_populationSize( 10 ),
    m_generations( 5 ),
    m_scoreFrequency( 1 ),
    m_flushFrequency( 5 ),
    m_mutation( 0.02 ),
    m_crossover( 0.2 ),
    m_logFile( ( char* )"log_file.txt" ),
    m_junction( junction )
{
}

void BaseAlgorithm::run()
{
    m_timeVector = startAlgorithm();
}

const QVector<int>& BaseAlgorithm::timeVector() const
{
    return m_timeVector;
}
