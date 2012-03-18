#ifndef SIMPLEALGORITHMFORTHEGREATESTGROWTH_H
#define SIMPLEALGORITHMFORTHEGREATESTGROWTH_H

#include "../Base_classes/algorithm-framework.h"

class SimpleAlgorithmForTheGreatestGrowth: public AlgorithmFramework
{
public:
    SimpleAlgorithmForTheGreatestGrowth( PopulationManager *populationManager, Constraint *constraint );

    Chromosome run();
};

#endif // SIMPLEALGORITHMFORTHEGREATESTGROWTH_H
