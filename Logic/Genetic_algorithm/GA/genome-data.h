#ifndef GENOMEDATA_H
#define GENOMEDATA_H

#include <qglobal.h>
#include <vector>

class GenomeData
{
public:
    GenomeData( uint genomeSize, std::vector< float >& averages, std::vector< int >& vehiclesCount );

    std::vector< float > m_averages;
    std::vector< int > m_vehiclesCount;
};

#endif // GENOMEDATA_H
