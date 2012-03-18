#include "chromosome.h"

Chromosome::Chromosome():
    m_value( 0 )
{
}

int Chromosome::value() const
{
    return m_value;
}

void Chromosome::setValue( int value )
{
    m_value = value;
}

const QVector<int>& Chromosome::greenLigthDurations() const
{
    return m_greenLightDurations;
}
