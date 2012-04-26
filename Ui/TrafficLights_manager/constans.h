#ifndef CONSTANS_H
#define CONSTANS_H

#include <QHash>
#include <QVector>

class Constans
{
public:
    static uchar mapCheckpointId( const uchar& checkpoinId );

private:
    static void setMapCheckpointIdFromJunction_id0( QHash<uchar,uchar>& hash );
    static void setMapCheckpointIdFromJunction_id1( QHash<uchar,uchar>& hash );
    static void setMapCheckpointIdFromJunction_id2( QHash<uchar,uchar>& hash );
    static void setMapCheckpointIdFromJunction_id3( QHash<uchar,uchar>& hash );
    static void setMapCheckpointIdFromJunction_id4( QHash<uchar,uchar>& hash );
    static void setMapCheckpointIdFromJunction_id5( QHash<uchar,uchar>& hash );
    static void setMapCheckpointIdFromJunction_id6( QHash<uchar,uchar>& hash );
};

#endif // CONSTANS_H
