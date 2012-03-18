#ifndef CLASSICALGENETICALGORITHMFRAMEWORK_H
#define CLASSICALGENETICALGORITHMFRAMEWORK_H

#include "../Base_classes/algorithm-framework.h"

class ClassicalGeneticAlgorithmFramework: public AlgorithmFramework
{
public:
    ClassicalGeneticAlgorithmFramework( PopulationManager *populationManager, Constraint *constraint );

    Chromosome run();
};

#endif // CLASSICALGENETICALGORITHMFRAMEWORK_H
