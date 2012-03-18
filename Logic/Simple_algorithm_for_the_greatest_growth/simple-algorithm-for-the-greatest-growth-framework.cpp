#include "simple-algorithm-for-the-greatest-growth-framework.h"
#include <QDebug>

SimpleAlgorithmForTheGreatestGrowth::SimpleAlgorithmForTheGreatestGrowth( PopulationManager *populationManager,
                                                                          Constraint *constraint ):
    AlgorithmFramework( populationManager, constraint )
{
}

Chromosome SimpleAlgorithmForTheGreatestGrowth::run()
{
    qDebug() << "Start SimpleAlgorithmForTheGreatestGrowth::run";

    m_constraint->createCounter( "t", 0, 4 );

    Chromosome currentChromosome;
    Chromosome theBestNeighbourChromosome;

    Chromosome theBestChromosomeEver = currentChromosome;

    while( m_constraint->isCounterFinished( "t" ) == false )
    {
        bool local = false;

        currentChromosome = m_populationManager->createOneChromosome();
        m_populationManager->measureOneChromosome( &currentChromosome );

        while( local == false )
        {
            m_populationManager->chooseNeighbours( 4 );
            theBestNeighbourChromosome = m_populationManager->theMostValuableChromosome();

            qDebug() << "Current chromosome: " << currentChromosome.value();
            qDebug() << "The best neighbour chromosome: " << theBestNeighbourChromosome.value();
            qDebug() << "The best chromosome ever: " << theBestChromosomeEver.value();

            if( currentChromosome.value() < theBestNeighbourChromosome.value() )
            {
                currentChromosome = theBestNeighbourChromosome;
            }
            else
            {
                if( currentChromosome.value() > theBestChromosomeEver.value() )
                {
                    theBestChromosomeEver = currentChromosome;
                }

                local = true;
            }
        }
    }

    qDebug() << "Stop SimpleAlgorithmForTheGreatestGrowth::run";

    m_constraint->clearCounters();
    m_populationManager->clearPopulation();

    return theBestChromosomeEver;
}
