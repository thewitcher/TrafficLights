#ifndef SIMPLEJUNCTION_H
#define SIMPLEJUNCTION_H

#include "junction.h"

class SimpleJunction: public Junction
{
public:
    SimpleJunction( const QVector<TrafficLight*>& junction );
};

#endif // SIMPLEJUNCTION_H
