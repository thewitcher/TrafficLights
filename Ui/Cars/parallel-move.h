#ifndef PARALLELMOVE_H
#define PARALLELMOVE_H

#include "simple-move.h"
#include <QParallelAnimationGroup>

/*!
 * @file parralel-move.h
 *
 * @brief Here we have more advance animation class, which check some condition while it is running.
 *
 * @author Marcin Haber
 *
 * This class inherits QParallelAnimationGroup and SimpleMove. The main reason of implementing this class is to reimplements updateCurrentTime()
 * method from QAbstractAnimation. SimpleMove provide method to manage conditions while animation is running (see SimpleMove documentation)
 */
class ParallelMove: public QParallelAnimationGroup, public SimpleMove
{

    Q_OBJECT

public:
    /*!
     * Creates parallel animation for target.
     *
     * @param target Object to animate.
     */
    explicit ParallelMove( Vehicle *target, QObject *parent = 0 );

protected:
    /*!
     * Reimplement method from QAbstractAnimation.
     *
     * @param currentTime Time interval used to manage animation.
     */
    void updateCurrentTime( int currentTime );
};

#endif // PARALLELMOVE_H
