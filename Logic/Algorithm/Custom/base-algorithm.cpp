#include "base-algorithm.h"
#include "../Ui/TrafficLights_manager/junction.h"

BaseAlgorithm::BaseAlgorithm( Junction *junction ):
    m_genomeSize( 3 ),
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

Junction* BaseAlgorithm::junction()
{
    return m_junction;
}

void BaseAlgorithm::start()
{
    m_junction->setTimeVectorByAlgorithm( startAlgorithm() );
}
