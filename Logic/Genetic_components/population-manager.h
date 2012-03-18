#ifndef POPULATIONMANAGER_H
#define POPULATIONMANAGER_H

#include "population.h"
#include "chromosome.h"
#include <QDebug>

struct PopulationManager
{
    Population m_population;

    virtual void chooseNewPopulation() { qDebug() << "PopulationManager::modifyPopulation"; }
    virtual void chooseNeighbours( int count ) { Q_UNUSED( count ); qDebug() << "PopulationManager::chooseNeghbours"; }
    virtual void modifyPopulation() { qDebug() << "PopulationManager::modifyPopulation"; }
    virtual Chromosome& createOneChromosome() = 0;
    virtual void createInitialPopulation() { qDebug() << "PopulationManager::createInitialPopulation"; }
    virtual void measurePopulation() { qDebug() << "PopulationManager::measurePopulation"; }
    virtual int measureOneChromosome( Chromosome* chromosome )
    {
        Q_UNUSED( chromosome );

        qDebug() << "PopulationManager::measureOneChromosome";

        return 0;
    }
    virtual Chromosome& theMostValuableChromosome() = 0;
    virtual void clearPopulation() { m_population.clearPopulation(); }
};

#endif // POPULATIONMANAGER_H
