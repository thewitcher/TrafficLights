#include "one-subcycle-algorithm.h"
#include "../Ui/TrafficLights_manager/junction.h"

OneSubcycleAlgorithm::OneSubcycleAlgorithm()
{
}

QVector<int> OneSubcycleAlgorithm::start( Junction* junction )
{
    switch( junction->junctionType() )
    {
    case Junction::BLADZIO:
        break;
    case Junction::SIMPLE:
        break;
    default:
        break;
    }

    QVector<int> vector;
    vector << 5000 << 5000 << 5000 << 5000;
    return vector;
}

void OneSubcycleAlgorithm::chooseTheMostBlockSubcycle()
{

}
