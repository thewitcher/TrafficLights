#ifndef ALGORITHMFORTHEGREATESTGROWTHWITHTEMPERATURE_H
#define ALGORITHMFORTHEGREATESTGROWTHWITHTEMPERATURE_H

#include "../Base_classes/algorithm-framework.h"

class AlgorithmForTheGreatestGrowthWithTemperature: public AlgorithmFramework
{
public:
    AlgorithmForTheGreatestGrowthWithTemperature( PopulationManager *populationManager, Constraint *constraint );

    Chromosome run();

private:
    bool canAddRegardless();
};

class Temperature
{
public:
    Temperature( double initValue, double minValue );

    void newValue();
    double value() const;
    bool isToLow() const;

private:
    double m_value;
    double m_minValue;
};

#endif // ALGORITHMFORTHEGREATESTGROWTHWITHTEMPERATURE_H
