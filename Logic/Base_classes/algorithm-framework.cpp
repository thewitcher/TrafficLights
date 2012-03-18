#include "algorithm-framework.h"

AlgorithmFramework::AlgorithmFramework( PopulationManager *populationManager, Constraint *constraint ):
    m_populationManager( populationManager ),
    m_constraint( constraint )
{
}

AlgorithmFramework::~AlgorithmFramework()
{
    delete m_populationManager;
    delete m_constraint;
}
