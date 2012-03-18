#include "population.h"

Population::Population()
{}

void Population::addChromosome( Chromosome chromosome )
{
    if( m_theBestChromosome.value() < chromosome.value() )
    {
        m_theBestChromosome = chromosome;
    }

    m_population.append( chromosome );
}

Chromosome& Population::theBestChromosome()
{
    return m_theBestChromosome;
}

Chromosome& Population::lastAddedChromosome()
{
    Q_ASSERT( m_population.isEmpty() == false );

    return m_population.last();
}

void Population::clearPopulation()
{
    m_population.clear();
    m_theBestChromosome = Chromosome();
}
