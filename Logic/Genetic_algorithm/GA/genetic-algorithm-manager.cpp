#include "genetic-algorithm-manager.h"
#include "GASStateGA.h"
#include "GA1DArrayGenome.h"
#include "genome-data.h"
#include "../Logger/logger.h"
#include <iostream>

unsigned int GeneticAlgorithmManager::S_GENOME_SIZE = 2;
float GeneticAlgorithmManager::S_REPLACEMENT_PROBABILITY = 0.5;
int GeneticAlgorithmManager::S_POPULATION_SIZE = 10;
int GeneticAlgorithmManager::S_GENERATIONS = 5;
int GeneticAlgorithmManager::S_SCORE_FREQUENCY = 1;
int GeneticAlgorithmManager::S_FLUSH_FREQUENCY = 5;
float GeneticAlgorithmManager::S_MUTATION = 0.02;
float GeneticAlgorithmManager::S_CROSSOVER = 0.2;
char* GeneticAlgorithmManager::S_LOG_FILE = ( char* )"log_file.txt";


float objective( GAGenome& genome )
{
    GA1DArrayGenome< int > &arrayGenome = ( GA1DArrayGenome< int > & )genome;

    GenomeData *genomeData = reinterpret_cast<GenomeData*>( genome.userData() );

    float sum = 0;
    int duration = 0;

    for( int i = 0 ; i < arrayGenome.size() ; i++ )
    {
        sum += ( arrayGenome.gene( i ) * genomeData->m_vehiclesCount.at( i ) / genomeData->m_averages.at( i ) );
        duration += arrayGenome.gene( i );
    }

    if( duration < 1 )
    {
        duration = 1;
    }
    float result = sum / duration;

    return result;
}

void initializer( GAGenome& genome )
{
    GA1DArrayGenome< int > &arrayGenome = ( GA1DArrayGenome< int > & )genome;

    arrayGenome.gene( 0, GARandomInt( 0 , 4 ) ); // green light
    arrayGenome.gene( 1, GARandomInt( 0 , 4 ) ); // red light
}

GeneticAlgorithmManager::GeneticAlgorithmManager()
{
}

GAGenome GeneticAlgorithmManager::start( GenomeData *dynamicGenomeData )
{
    GA1DArrayGenome< int > arrayGenome( S_GENOME_SIZE, objective, dynamicGenomeData );
    arrayGenome.initializer( initializer );
    GASteadyStateGA gaSteadyStateGA( arrayGenome );
    gaSteadyStateGA.populationSize( S_POPULATION_SIZE );
    gaSteadyStateGA.pReplacement( S_REPLACEMENT_PROBABILITY ); // how percentage of population will be replaced
    gaSteadyStateGA.nGenerations( S_GENERATIONS );
    gaSteadyStateGA.pMutation( S_MUTATION );
    gaSteadyStateGA.pCrossover( S_CROSSOVER );
    gaSteadyStateGA.scoreFilename( S_LOG_FILE );
    gaSteadyStateGA.scoreFrequency( S_SCORE_FREQUENCY );
    gaSteadyStateGA.flushFrequency( S_FLUSH_FREQUENCY );
    gaSteadyStateGA.selectScores( GAStatistics::AllScores );
    gaSteadyStateGA.evolve();

    delete dynamicGenomeData;

    return gaSteadyStateGA.population().best();
}
