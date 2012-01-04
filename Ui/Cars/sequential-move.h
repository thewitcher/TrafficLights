#ifndef SEQUENTIALMOVE_H
#define SEQUENTIALMOVE_H

#include "simple-move.h"
#include <QSequentialAnimationGroup>

class Vehicle;

class SequentialMove: public QSequentialAnimationGroup, public SimpleMove
{

    Q_OBJECT

public:
    explicit SequentialMove( Vehicle* vehicle, QObject *parent = 0 );

protected:
    void updateCurrentTime(int);
};

#endif // SEQUENTIALMOVE_H
