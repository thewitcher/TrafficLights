#ifndef PROPERTYMOVE_H
#define PROPERTYMOVE_H

#include "simple-move.h"
#include <QPropertyAnimation>

class PropertyMove: public QPropertyAnimation, public SimpleMove
{

    Q_OBJECT

public:
    explicit PropertyMove( Vehicle* target, const QByteArray & propertyName, QObject * parent = 0 );

protected:
    void updateCurrentTime( int currentTime );
};

#endif // PROPERTYMOVE_H
