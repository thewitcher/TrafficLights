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
};

#endif // SIMPLEMOVE_H
