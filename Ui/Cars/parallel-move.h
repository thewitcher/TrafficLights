#ifndef PARALLELMOVE_H
#define PARALLELMOVE_H

#include "simple-move.h"
#include <QParallelAnimationGroup>

class ParallelMove: public QParallelAnimationGroup, public SimpleMove
{

    Q_OBJECT

public:
    explicit ParallelMove( QObject *parent = 0 );

protected:
    void updateCurrentTime( int currentTime );
};

#endif // PARALLELMOVE_H
