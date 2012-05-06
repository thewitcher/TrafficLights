#include "helper.h"
#include "../GA/GA1DBinStrGenome.h"
#include "../GA/GA1DArrayGenome.h"
#include "../GA/GAGenome.h"
#include "../GA/gaid.h"
#include "../Logger/logger.h"
#include <QObject>


GA1DBinaryStringGenome& Helper::genomeToBinaryGenome( GAGenome& genome )
{
    Q_ASSERT( genome.classID() == GAID::BinaryStringGenome );

    GA1DBinaryStringGenome& binaryGenome = ( GA1DBinaryStringGenome & )genome;

    return binaryGenome;
}

GA1DArrayGenome<int>& Helper::genomeToArrayGenome( GAGenome& genome )
{
    Q_ASSERT( genome.classID() == GAID::ArrayGenome );

    GA1DArrayGenome<int>& arrayGenome = ( GA1DArrayGenome<int> & )genome;

    return arrayGenome;
}

BaseAlgorithm* Helper::userDataToBaseAlgorithm( GAGenome &genome )
{
    return reinterpret_cast<BaseAlgorithm*>( genome.userData() );
}

OneSubcycleAlgorithm* Helper::userDataToOneSubcycleAlgorithm( GAGenome &genome )
{
    return reinterpret_cast<OneSubcycleAlgorithm*>( genome.userData() );
}

AllSubcycleAlgorithm* Helper::userDataToAllSubcycleAlgorithm( GAGenome &genome )
{
    return reinterpret_cast<AllSubcycleAlgorithm*>( genome.userData() );
}

int Helper::toDec( GAGenome& genome )
{
    GA1DBinaryStringGenome& binaryGenome = genomeToBinaryGenome( genome );

    int result = 0;

    if( binaryGenome.length() > 0 )
    {
        for( int i = binaryGenome.length() - 1 ; i > 0 ; i-- )
        {
            result = 2 * ( binaryGenome.gene( i ) + result );
        }

        result += binaryGenome.gene( 0 );
    }

    return result;
}
