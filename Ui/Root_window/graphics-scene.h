#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QMap>
#include <QLCDNumber>

class Vehicle;
class TrafficLight;
class Checkpoint;

class GraphicsScene: public QGraphicsScene
{

    Q_OBJECT

public:
    explicit GraphicsScene( QObject *parent = 0 );

    void addVehicle( Vehicle *newVehicle );
    QList<Vehicle*>& allVehicles();

    void addVehicleCounter();
    QVector<QLCDNumber*>& allVehicleCounters();

    void addTrafficLightsToScene( QMap< int, QVector<TrafficLight*> >& junctionsMap, QVector<Checkpoint*> );
    QMap< int, QVector<TrafficLight*> >& allTrafficLights();

protected:
    QMap< int, QVector<TrafficLight*> > m_trafficLights;
    QList<Vehicle*> m_vehicles;
    QVector<QLCDNumber*> m_vehicleCouters;
};

#endif // GRAPHICSSCENE_H
