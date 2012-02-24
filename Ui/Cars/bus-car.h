#ifndef BUSCAR_H
#define BUSCAR_H

#include "vehicle.h"

class BusCar: public Vehicle
{

    Q_OBJECT

public:
    BusCar( QDeclarativeItem *parent = 0 );

    void setDarkDesign( bool dark = false );
};

#endif // BUSCAR_H
