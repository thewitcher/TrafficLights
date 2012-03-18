#ifndef POPULATION_H
#define POPULATION_H

#include <QList>
#include "chromosome.h"

class Population
{
public:
    Population();

    void addChromosome( Chromosome chromosome );
    Chromosome& lastAddedChromosome();
    Chromosome& theBestChromosome();

    void clearPopulation();

private:
    QList< Chromosome > m_population;
    Chromosome m_theBestChromosome;
};

#endif // POPULATION_H
