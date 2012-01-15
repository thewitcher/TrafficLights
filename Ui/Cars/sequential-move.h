#ifndef SEQUENTIALMOVE_H
#define SEQUENTIALMOVE_H

#include "simple-move.h"
#include <QSequentialAnimationGroup>

/*!
 * @file sequential-move.h
 *
 * @brief Here we have more advance animation class, which check some condition while it is running.
 *
 * @author Marcin Haber
 *
 * This class inherits QSequentialAnimationGroup and SimpleMove. The main reason of implement this class is to reimplement updateCurrentTime()
 * method from QAbstractAnimation. SimpleMove provide method to manage conditions while animation is running (see SimpleMove documentation)
 */

class SequentialMove: public QSequentialAnimationGroup, public SimpleMove
{

    Q_OBJECT

public:
    /*!
     * Creates sequential animation for target.
     *
     * @param target Object to animate.
     */
    explicit SequentialMove( Vehicle *target, QObject *parent = 0 );

protected:
    /*!
     * Reimplement method from QAbstractAnimation.
     *
     * @param currentTime Time interval used to manage animation.
     */
    void updateCurrentTime(int);
};

#endif // SEQUENTIALMOVE_H
