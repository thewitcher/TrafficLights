#ifndef PARALLELMOVE_H
#define PARALLELMOVE_H

#include "simple-move.h"
#include <QParallelAnimationGroup>

class Vehicle;

class ParallelMove: public QParallelAnimationGroup, public SimpleMove
{

    Q_OBJECT

public:
    explicit ParallelMove( Vehicle* vehicle, QObject *parent = 0 );

protected:
    void updateCurrentTime( int currentTime );
};

#endif // PARALLELMOVE_H
