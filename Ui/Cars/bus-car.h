#ifndef BUSCAR_H
#define BUSCAR_H

#include "vehicle.h"

/*!
 * @file vehicle.h
 *
 * @brief Inherit Vehicle class.
 *
 * @author Marcin Haber
 *
 * Some parameters are different for other type of vehicle. This is class describing bus object. It inherits from Vehicle class.
 */
class BusCar: public Vehicle
{

    Q_OBJECT

public:
    /*!
     * Standard constructor. It does nothing interesting.
     *
     * @param parent Sets object's parent.
     *
     */
    BusCar( QDeclarativeItem *parent = 0 );

    /*!
     * Standard constructor. It does nothing interesting.
     *
     * @param dark If this variable is false then dark bus graphic is loaded, otherwise bright bus graphics is loaded. This
     * method when night becomes day and vice versa.
     *
     */
    void setDarkDesign( bool dark = false );
};

#endif // BUSCAR_H
