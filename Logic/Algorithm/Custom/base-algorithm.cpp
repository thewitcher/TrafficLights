#include "base-algorithm.h"
#include "../Ui/TrafficLights_manager/junction.h"
#include "../Settings/settings.h"

BaseAlgorithm::BaseAlgorithm( Junction *junction, const QString &algorithmType ):
    m_algorithmType( algorithmType ),
    m_genomeSize( Settings::takeValue( "GENOME_SIZE", m_algorithmType, 1 ).toInt() ),
    m_replacementProbability( Settings::takeValue( "REPLACEMENT_PROBABILITY", m_algorithmType, 0.5 ).toDouble() ),
    m_populationSize( Settings::takeValue( "POPULATION_SIZE", m_algorithmType, 50 ).toInt() ),
    m_generations( Settings::takeValue( "GENERATIONS", m_algorithmType, 100 ).toInt() ),
    m_scoreFrequency( Settings::takeValue( "SCORE_FREQUENCY", m_algorithmType, 1 ).toInt() ),
    m_flushFrequency( Settings::takeValue( "FLUSH_FREQUENCY", m_algorithmType, 5 ).toInt() ),
    m_mutation( Settings::takeValue( "MUTATION_PROBABILITY", m_algorithmType, 0.01 ).toDouble() ),
    m_crossover( Settings::takeValue( "CROSSOVER_PROBABILITY", m_algorithmType, 0.01 ).toDouble() ),
    m_logFile( Settings::takeValue( "LOG_FILE_NAME", m_algorithmType, "log_file" ).toString()
               + QString::number( junction->id() ) + ".txt" ),
    m_junction( junction )
{}

Junction* BaseAlgorithm::junction()
{
    return m_junction;
}

void BaseAlgorithm::start()
{
    m_junction->setTimeVectorByAlgorithm( startAlgorithm() );
}
