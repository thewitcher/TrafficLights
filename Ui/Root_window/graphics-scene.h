#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QMap>

class Vehicle;
class TrafficLight;

class GraphicsScene: public QGraphicsScene
{

    Q_OBJECT

public:
    explicit GraphicsScene( QObject *parent = 0 );

    void addVehicle( Vehicle *newVehicle );
    QList<Vehicle*>& allVehicles();

    void addTrafficLightsToScene( QMap< int, QVector<TrafficLight*> >& junctionsMap );
    QMap< int, QVector<TrafficLight*> >& allTrafficLights();

protected:
    QMap< int, QVector<TrafficLight*> > m_trafficLights;
    QList<Vehicle*> m_vehicles;
};

#endif // GRAPHICSSCENE_H
