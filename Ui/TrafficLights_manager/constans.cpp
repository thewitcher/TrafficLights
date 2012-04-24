#include "constans.h"

uchar Constans::mapCheckpointId( const uchar& checkpoinId )
{
    static QHash<uchar,uchar> hash;

    if( hash.isEmpty() )
    {
        setMapCheckpointIdFromJunction_id0( hash );
        setMapCheckpointIdFromJunction_id1( hash );
        setMapCheckpointIdFromJunction_id2( hash );
        setMapCheckpointIdFromJunction_id3( hash );
        setMapCheckpointIdFromJunction_id4( hash );
        setMapCheckpointIdFromJunction_id5( hash );
        setMapCheckpointIdFromJunction_id6( hash );
    }

    return hash.key( checkpoinId );
}

void Constans::setMapCheckpointIdFromJunction_id0( QHash<uchar, uchar> & hash )
{
    hash.insert( 107, 128 );
    hash.insert( 6, 127 );
    hash.insert( 48, 47 );
    hash.insert( 38, 37 );
}

void Constans::setMapCheckpointIdFromJunction_id1( QHash<uchar, uchar> & hash )
{
    hash.insert( 11, 137 );
    hash.insert( 20, 12 );
    hash.insert( 0, 138 );
    hash.insert( 21, 13 );
}

void Constans::setMapCheckpointIdFromJunction_id2( QHash<uchar, uchar> &hash )
{
    hash.insert( 2, 14 );
    hash.insert( 3, 15 );
    hash.insert( 4, 16 );
    hash.insert( 8, 14 );
    hash.insert( 9, 15 );
    hash.insert( 10, 16 );
    hash.insert( 17, 19 );
    hash.insert( 18, 19 );
    hash.insert( 26, 28 );
    hash.insert( 27, 28 );
    hash.insert( 32, 34 );
    hash.insert( 33, 34 );
    hash.insert( 42, 40 );
    hash.insert( 43, 40 );
    hash.insert( 44, 41 );
    hash.insert( 45, 41 );
    hash.insert( 53, 52 );
    hash.insert( 54, 52 );
    hash.insert( 102, 84 );
    hash.insert( 104, 85 );
    hash.insert( 119, 83 );
}

void Constans::setMapCheckpointIdFromJunction_id3( QHash<uchar, uchar> &hash )
{
    hash.insert( 5, 136 );
    hash.insert( 23, 24 );
    hash.insert( 29, 30 );
    hash.insert( 101, 135 );
}

void Constans::setMapCheckpointIdFromJunction_id4( QHash<uchar, uchar> &hash )
{
    hash.insert( 72, 133 );
    hash.insert( 90, 57 );
    hash.insert( 100, 134 );
    hash.insert( 103, 58 );
}

void Constans::setMapCheckpointIdFromJunction_id5( QHash<uchar, uchar> &hash )
{
    hash.insert( 71, 132 );
    hash.insert( 81, 131 );
    hash.insert( 105, 75 );
    hash.insert( 108, 76 );
}

void Constans::setMapCheckpointIdFromJunction_id6( QHash<uchar, uchar> &hash )
{
    hash.insert( 82, 130 );
    hash.insert( 106, 65 );
    hash.insert( 121, 66 );
    hash.insert( 139, 129 );
}
