#include "algorithm-for-the-greatest-growth-with-temperature-framework.h"

AlgorithmForTheGreatestGrowthWithTemperature::AlgorithmForTheGreatestGrowthWithTemperature( PopulationManager *populationManager,
                                                                                           Constraint *constraint ):
    AlgorithmFramework( populationManager, constraint )
{
}

Chromosome AlgorithmForTheGreatestGrowthWithTemperature::run()
{
    qDebug() << "Start AlgorithmForTheGreatestGrowthWithTemperature::run";

    m_constraint->createCounter( "t", 0, 4 );

    Temperature temperature( 10, 3 );

    Chromosome currentChromosome;
    Chromosome theBestNeighbourChromosome;

    currentChromosome = m_populationManager->createOneChromosome();
    m_populationManager->measureOneChromosome( &currentChromosome );

    while( temperature.isToLow() == false )
    {
        qDebug() << "Restart counter";
        m_constraint->restartCounter( "t" );

        while( m_constraint->isCounterFinished( "t" ) == false )
        {
            m_populationManager->chooseNeighbours( 1 );
            theBestNeighbourChromosome = m_populationManager->theMostValuableChromosome();

            qDebug() << "Current chromosome: " << currentChromosome.value();
            qDebug() << "The best neighbour chromosome: " << theBestNeighbourChromosome.value();

            if( currentChromosome.value() < theBestNeighbourChromosome.value() )
            {
                currentChromosome = theBestNeighbourChromosome;
            }
            else if( canAddRegardless() )
            {
                qDebug() << "Add chromosome regardless his low value";
                currentChromosome = theBestNeighbourChromosome;
            }
        }
        temperature.newValue();

        qDebug() << "New temperature: " << temperature.value();
    }

    qDebug() << "Stop AlgorithmForTheGreatestGrowthWithTemperature::run";

    m_constraint->clearCounters();
    m_populationManager->clearPopulation();

    return currentChromosome;
}

bool AlgorithmForTheGreatestGrowthWithTemperature::canAddRegardless()
{
    return true;
}

//////////////// Temperature ////////////////
Temperature::Temperature( double initValue, double minValue ):
    m_value( initValue ),
    m_minValue( minValue )
{
    qDebug() << "Temperature constructor: init value: " << m_value << ", minValue: " << minValue;
}

void Temperature::newValue()
{
    m_value -= 1;
}

bool Temperature::isToLow() const
{
    if( m_value <= m_minValue )
    {
        return true;
    }

    return false;
}

double Temperature::value() const
{
    return m_value;
}
