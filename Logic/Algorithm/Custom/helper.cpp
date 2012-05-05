#include "helper.h"
#include "../GA/GA1DBinStrGenome.h"
#include "../GA/GAGenome.h"


GA1DBinaryStringGenome& Helper::genomeToBinaryGenome( GAGenome& genome )
{
    GA1DBinaryStringGenome& binaryGenome = ( GA1DBinaryStringGenome & )genome;

    return binaryGenome;
}

Junction* Helper::userDataToJunction( GAGenome& genome )
{
    return reinterpret_cast<Junction*>( genome.userData() );
}
#include <QDebug>
int Helper::toDec( GAGenome& genome )
{
    GA1DBinaryStringGenome& binaryGenome = genomeToBinaryGenome( genome );

    for( int i = binaryGenome.length() - 1 ; i >= 0 ; i-- )
    {
        qDebug() << binaryGenome.gene( i );
    }

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
