#include "genome-data.h"
#include "GA1DArrayGenome.h"
#include <QObject>

GenomeData::GenomeData( int genomeSize, std::vector< float > &averages, std::vector< int > &vehiclesCount ):
    m_averages( averages ),
    m_vehiclesCount( vehiclesCount )
{
    Q_ASSERT( genomeSize == averages.size() &&
              genomeSize == vehiclesCount.size() );
}
