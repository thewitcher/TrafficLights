#ifndef SIMPLEMOVE_H
#define SIMPLEMOVE_H

class Vehicle;

class SimpleMove
{
public:
    explicit SimpleMove( Vehicle *currentVehicle );

protected:
    void doItWhileMoving();

    Vehicle *m_currentVehicle;
};

#endif // SIMPLEMOVE_H
