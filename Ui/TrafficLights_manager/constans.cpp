#include "constans.h"

int Constans::mapCheckpointId( const int& checkpoinId )
{
    static QHash<int,int> hash;

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

int Constans::mapCheckpointId2( const int checkpoinId )
{
    static QHash<int,int> hash2;

    if( hash2.isEmpty() )
    {
        hash2.insert( 2, 2080 );
        hash2.insert( 8, 2080 );
        hash2.insert( 3, 3090 );
        hash2.insert( 9, 3090 );
        hash2.insert( 4, 4010 );
        hash2.insert( 10, 4010 );
        hash2.insert( 17, 1718 );
        hash2.insert( 18, 1718 );
        hash2.insert( 26, 2627 );
        hash2.insert( 27, 2627 );
        hash2.insert( 32, 3233 );
        hash2.insert( 33, 3233 );
        hash2.insert( 42, 4243 );
        hash2.insert( 43, 4243 );
        hash2.insert( 44, 4445 );
        hash2.insert( 45, 4445 );
        hash2.insert( 53, 5354 );
        hash2.insert( 54, 5354 );
    }

    if( hash2.contains( checkpoinId ) )
    {
        return hash2.value( checkpoinId );
    }

    return checkpoinId;
}

void Constans::setMapCheckpointIdFromJunction_id0( QHash<int, int> & hash )
{
    hash.insert( 107, 128 );
    hash.insert( 6, 127 );
    hash.insert( 48, 47 );
    hash.insert( 38, 37 );
}

void Constans::setMapCheckpointIdFromJunction_id1( QHash<int, int> & hash )
{
    hash.insert( 11, 137 );
    hash.insert( 20, 12 );
    hash.insert( 0, 138 );
    hash.insert( 21, 13 );
}

void Constans::setMapCheckpointIdFromJunction_id2( QHash<int, int> &hash )
{
    // We shoud join two id to one in order to create unique id. We can join id by connect less id and bigger.
    // If id is one digit numberthen we should add 0 to it.

    hash.insert( 2080, 14 );
    hash.insert( 3090, 15 );
    hash.insert( 4010, 16 );
    hash.insert( 1718, 19 );
    hash.insert( 2627, 28 );
    hash.insert( 3233, 34 );
    hash.insert( 4243, 40 );
    hash.insert( 4445, 41 );
    hash.insert( 5354, 52 );
    hash.insert( 102, 84 );
    hash.insert( 104, 85 );
    hash.insert( 119, 83 );
}

void Constans::setMapCheckpointIdFromJunction_id3( QHash<int, int> &hash )
{
    hash.insert( 5, 136 );
    hash.insert( 23, 24 );
    hash.insert( 29, 30 );
    hash.insert( 101, 135 );
}

void Constans::setMapCheckpointIdFromJunction_id4( QHash<int, int> &hash )
{
    hash.insert( 72, 133 );
    hash.insert( 90, 57 );
    hash.insert( 100, 134 );
    hash.insert( 103, 58 );
}

void Constans::setMapCheckpointIdFromJunction_id5( QHash<int, int> &hash )
{
    hash.insert( 71, 132 );
    hash.insert( 81, 131 );
    hash.insert( 105, 75 );
    hash.insert( 108, 76 );
}

void Constans::setMapCheckpointIdFromJunction_id6( QHash<int, int> &hash )
{
    hash.insert( 82, 130 );
    hash.insert( 106, 65 );
    hash.insert( 121, 66 );
    hash.insert( 139, 129 );
}
