#include "classical-genetic-algorithm-framework.h"
#include <QDebug>

ClassicalGeneticAlgorithmFramework::ClassicalGeneticAlgorithmFramework( PopulationManager *populationManager,
                                                                        Constraint *constraint ):
    AlgorithmFramework( populationManager, constraint )
{
}

Chromosome ClassicalGeneticAlgorithmFramework::run()
{
    qDebug() << "Start ClassicalGeneticAlgorithmFramework::Run";

    m_populationManager->createInitialPopulation();
    m_populationManager->measurePopulation();

    while( m_constraint->endAlgorithm() )
    {
        qDebug() << "$$$$$$$$$$$$$$$$$$$$$$";
        m_populationManager->chooseNewPopulation();
        m_populationManager->modifyPopulation();
        m_populationManager->measurePopulation();
        qDebug() << "$$$$$$$$$$$$$$$$$$$$$$";
    }

    qDebug() << "Stop ClassicalGeneticAlgorithmFramework::Run";

    return Chromosome();
}
