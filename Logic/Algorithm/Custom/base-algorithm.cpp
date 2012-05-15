#include "base-algorithm.h"
#include "../Ui/TrafficLights_manager/junction.h"

BaseAlgorithm::BaseAlgorithm( Junction *junction ):
    m_genomeSize( 5 ),
    m_replacementProbability( 0.4 ),
    m_populationSize( 90 ),
    m_generations( 100 ),
    m_scoreFrequency( 1 ),
    m_flushFrequency( 5 ),
    m_mutation( 0.09 ),
    m_crossover( 0.2 ),
    m_logFile( ( char* )"log_file.txt" ),
    m_junction( junction )
{
}

Junction* BaseAlgorithm::junction()
{
    return m_junction;
}

void BaseAlgorithm::start()
{
    m_junction->setTimeVectorByAlgorithm( startAlgorithm() );
}
