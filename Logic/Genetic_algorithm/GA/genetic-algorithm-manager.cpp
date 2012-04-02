#include "genetic-algorithm-manager.h"
#include "GADemeGA.h"
#include "GA1DArrayGenome.h"
#include "genome-data.h"
#include <iostream>
#include <QDebug>

unsigned int GeneticAlgorithmManager::S_GENOME_SIZE = 2;
int GeneticAlgorithmManager::S_PARALLEL_POPULATIONS = 4;
int GeneticAlgorithmManager::S_POPULATION_SIZE = 10;
int GeneticAlgorithmManager::S_GENERATIONS = 12;
float GeneticAlgorithmManager::S_MUTATION = 0.02;
float GeneticAlgorithmManager::S_CROSSOVER = 0.2;

float objective( GAGenome& genome )
{
    return 0;
}

void initializer( GAGenome& genome )
{
    GA1DArrayGenome< int > &arrayGenome = ( GA1DArrayGenome< int > & )genome;

    arrayGenome.gene( 0, 2 );
    arrayGenome.gene( 1, 1);

    //qDebug() << "Data: " << reinterpret_cast<GenomeData*>(arrayGenome.userData())->m_test;
}

GeneticAlgorithmManager::GeneticAlgorithmManager()
{
    void * data = new GenomeData;

    GA1DArrayGenome< int > arrayGenome( S_GENOME_SIZE, objective, data);
    arrayGenome.initializer( initializer );

    GADemeGA gaDemeGA( arrayGenome );
    gaDemeGA.nPopulations( S_PARALLEL_POPULATIONS );
    gaDemeGA.populationSize( S_POPULATION_SIZE );
    gaDemeGA.nGenerations( S_GENERATIONS );
    gaDemeGA.pMutation( S_MUTATION );
    gaDemeGA.pCrossover( S_CROSSOVER );
    qDebug() << "Init...";
    gaDemeGA.initialize();
    qDebug() << "After init...";
    int step = 0;
    while( gaDemeGA.done() == false )
    {

        gaDemeGA.step();
        qDebug() << "Next step: " << step++;
    }
    qDebug() << "After loop";

    std::cout << "Best chromosome: " << gaDemeGA.statistics().bestIndividual() << endl;
    std::cout << "Statistic: " << gaDemeGA.statistics() << endl;
    std::cout.flush();
}
