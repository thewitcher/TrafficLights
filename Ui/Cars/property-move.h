#ifndef PROPERTYMOVE_H
#define PROPERTYMOVE_H

#include "simple-move.h"
#include <QPropertyAnimation>

/*!
 * @file property-move.h
 *
 * @brief Here we have more advance animation class, which check some condition while it is running.
 *
 * @author Marcin Haber
 *
 * This class inherits QPropertyAnimation and SimpleMove. The main reason of implement this class is to reimplement updateCurrentTime()
 * method from QAbstractAnimation. SimpleMove provide method to manage conditions while animation is running (see SimpleMove documentation)
 */

class PropertyMove: public QPropertyAnimation, public SimpleMove
{

    Q_OBJECT

public:
    /*!
     * Creates property animation for target. It animate property propertyName in target object.
     *
     * @param target Target is the vehicle associate with this animation.
     * @param propertyName Property to animate.
     */
    explicit PropertyMove( Vehicle* target, const QByteArray & propertyName, QObject * parent = 0 );

protected:
    /*!
     * Reimplement method from QAbstractAnimation.
     *
     * @param currentTime Time interval used to manage animation.
     */
    void updateCurrentTime( int currentTime );
};

#endif // PROPERTYMOVE_H
