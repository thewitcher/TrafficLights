#ifndef DEPLOYTRAFFICLIGHTS_H
#define DEPLOYTRAFFICLIGHTS_H

#include <QMap>
#include <QVector>

class TrafficLight;
class CheckpointManager;
class Checkpoint;

class DeployTrafficLights
{
public:
    DeployTrafficLights( CheckpointManager * checkpoint );

    QMap< int, QVector<TrafficLight*> >& trafficLightsMap();
    QVector<Checkpoint*> allCheckpointForLights();

private:
    void templateSimpleCross( QVector<qreal> vector, unsigned int id );
    void templatecomplexCross( QVector<qreal> vector, unsigned int id );
    void setLights();
    void setCheckpointForLights( CheckpointManager * checkPoint );
    QMap< int, QVector<TrafficLight*> > m_lights;
    QVector<Checkpoint*> m_checkpointsVectorToLights;
};

#endif // DEPLOYTRAFFICLIGHTS_H
