#ifndef SEQUENTIALMOVE_H
#define SEQUENTIALMOVE_H

#include "simple-move.h"
#include <QSequentialAnimationGroup>

class SequentialMove: public QSequentialAnimationGroup, public SimpleMove
{

    Q_OBJECT

public:
    explicit SequentialMove( QObject *parent = 0 );

protected:
    void updateCurrentTime(int);
};

#endif // SEQUENTIALMOVE_H
