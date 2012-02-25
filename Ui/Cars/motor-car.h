#ifndef MOTOR_CAR_H
#define MOTOR_CAR_H

#include "vehicle.h"

/*!
 * @file vehicle.h
 *
 * @brief Inherit Vehicle class.
 *
 * @author Marcin Haber
 *
 * Some parameters are different for other type of vehicle. This is class describing motor car object. It inherits from Vehicle class.
 */
class MotorCar: public Vehicle
{

    Q_OBJECT

public:
    /*!
     * Standard constructor. It does nothing interesting.
     *
     * @param parent Sets object's parent.
     *
     */
    explicit MotorCar( QDeclarativeItem *parent = 0 );

    /*!
     * Standard constructor. It does nothing interesting.
     *
     * @param dark If this variable is false then dark car graphic is loaded, otherwise bright car graphics is loaded. This
     * method when night becomes day and vice versa.
     *
     */
    void setDarkDesign( bool dark = false );
};

#endif // MOTOR_CAR_H
