#ifndef DEPLOYTRAFFICLIGHTS_H
#define DEPLOYTRAFFICLIGHTS_H

#include <QMap>

class TrafficLight;

class DeployTrafficLights
{
public:
    DeployTrafficLights();

    QMap< int, QVector<TrafficLight*> >& trafficLightsMap();

private:
    void templateSimpleCross( QVector<qreal> vector, unsigned int id );
    void templatecomplexCross( QVector<qreal> vector, unsigned int id );
    void setLights();
    QMap< int, QVector<TrafficLight*> > m_lights;
};

#endif // DEPLOYTRAFFICLIGHTS_H
