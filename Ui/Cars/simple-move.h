#ifndef SIMPLEMOVE_H
#define SIMPLEMOVE_H

class Vehicle;

class SimpleMove
{
public:
    explicit SimpleMove( Vehicle *target );

protected:
    Vehicle *m_currentVehicle;

    void collisionDetection();
    /*!
     * Return true if the car cause collision with other.
     */
    bool isGuiltyOfACollision( const Vehicle* target ) const;
};

#endif // SIMPLEMOVE_H
