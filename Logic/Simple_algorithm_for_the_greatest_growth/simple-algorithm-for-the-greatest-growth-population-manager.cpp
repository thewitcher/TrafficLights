#include "simple-algorithm-for-the-greatest-growth-population-manager.h"

SimpleAlgorithmForTheGreatestGrowthPopulationManager::SimpleAlgorithmForTheGreatestGrowthPopulationManager()
{
}

Chromosome& SimpleAlgorithmForTheGreatestGrowthPopulationManager::createOneChromosome()
{
    qDebug() << "SimpleAlgorithmForTheGreatestGrowthPopulationManager::createOneChromosome";

    Chromosome chromosome;

    m_population.addChromosome( chromosome );

    return m_population.lastAddedChromosome();
}

int SimpleAlgorithmForTheGreatestGrowthPopulationManager::measureOneChromosome( Chromosome &chromosome )
{
    qDebug() << "SimpleAlgorithmForTheGreatestGrowthPopulationManager::measureOneChromosome";

    chromosome.setValue( 0 );

    return 0;
}

Chromosome& SimpleAlgorithmForTheGreatestGrowthPopulationManager::theMostValuableChromosome()
{
    qDebug() << "SimpleAlgorithmForTheGreatestGrowthPopulationManager::theMostValuableChromosome";

    return m_population.theBestChromosome();
}

void SimpleAlgorithmForTheGreatestGrowthPopulationManager::chooseNeighbours( int count )
{
    qDebug() << "SimpleAlgorithmForTheGreatestGrowthPopulationManager::chooseNeghbours";

    m_population.clearPopulation();

    for( int i = 0 ; i < count ; i++ )
    {
        Chromosome chromosome;
        chromosome.setValue( i );

        m_population.addChromosome( chromosome );
    }
}
