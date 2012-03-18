#ifndef SIMPLEALGORITHMFORTHEGREATESTGROWTHPOPULATIONMANAGER_H
#define SIMPLEALGORITHMFORTHEGREATESTGROWTHPOPULATIONMANAGER_H

#include "../Genetic_components/population-manager.h"

class SimpleAlgorithmForTheGreatestGrowthPopulationManager: public PopulationManager
{
public:
    SimpleAlgorithmForTheGreatestGrowthPopulationManager();

    void chooseNeighbours( int count );
    Chromosome& createOneChromosome();
    int measureOneChromosome( Chromosome& chromosome );
    Chromosome& theMostValuableChromosome();
};

#endif // SIMPLEALGORITHMFORTHEGREATESTGROWTHPOPULATIONMANAGER_H
