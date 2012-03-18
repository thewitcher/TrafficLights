#ifndef ALGORITHMFRAMEWORK_H
#define ALGORITHMFRAMEWORK_H

#include "../Genetic_components/population-manager.h"
#include "constraint.h"

class AlgorithmFramework
{
public:
    AlgorithmFramework( PopulationManager *populationManager, Constraint *constraint );
    ~AlgorithmFramework();

    virtual Chromosome run() = 0;

protected:
    PopulationManager *m_populationManager;
    Constraint *m_constraint;
};

#endif // ALGORITHMFRAMEWORK_H
