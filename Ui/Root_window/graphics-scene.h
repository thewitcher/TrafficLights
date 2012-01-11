#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>

class Vehicle;

class GraphicsScene: public QGraphicsScene
{

    Q_OBJECT

public:
    explicit GraphicsScene( QObject *parent = 0 );

    void addVehicle( Vehicle *newVehicle );
    QList<Vehicle*>& allVehicles();

protected:
    QList<Vehicle*> m_vehicles;
};

#endif // GRAPHICSSCENE_H
