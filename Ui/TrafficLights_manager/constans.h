#ifndef CONSTANS_H
#define CONSTANS_H

#include <QHash>
#include <QVector>

class Constans
{
public:
    static int mapCheckpointId( const int& checkpoinId );
    static int mapCheckpointId2( const int checkpoinId ); // It maps checkpoint to joined value

private:
    static void setMapCheckpointIdFromJunction_id0( QHash<int,int>& hash );
    static void setMapCheckpointIdFromJunction_id1( QHash<int,int>& hash );
    static void setMapCheckpointIdFromJunction_id2( QHash<int,int>& hash );
    static void setMapCheckpointIdFromJunction_id3( QHash<int,int>& hash );
    static void setMapCheckpointIdFromJunction_id4( QHash<int,int>& hash );
    static void setMapCheckpointIdFromJunction_id5( QHash<int,int>& hash );
    static void setMapCheckpointIdFromJunction_id6( QHash<int,int>& hash );
};

#endif // CONSTANS_H
