#ifndef BLADZIOJUNCTION_H
#define BLADZIOJUNCTION_H

#include "junction.h"

class BladzioJunction: public Junction
{
public:
    BladzioJunction( const QVector<TrafficLight*>& junction );
};

#endif // BLADZIOJUNCTION_H
