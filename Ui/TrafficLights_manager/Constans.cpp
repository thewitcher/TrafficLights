#include <QHash>
#include <QDebug>


uchar fun(uchar)
{
    static bool dddddd = true;

    if( dddddd )
    {
        dddddd = false;
        QHash<uchar,uchar> hash;
    }


}
