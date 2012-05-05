#ifndef ALGORITHMMANAGER_H
#define ALGORITHMMANAGER_H

#include "base-algorithm.h"
#include <QVector>
#include <QObject>

class Junction;

class AlgorithmManager: public QObject
{

    Q_OBJECT

public:
    AlgorithmManager( Junction* junction );
    ~AlgorithmManager();

    void start();

private:
    BaseAlgorithm* m_baseAlgorithm;
    Junction* m_junction;
    bool m_finished;

    void updateAlgorithm( Junction* junction );

public slots:
    void timeVectorChanged();

signals:
    void changeTimeVector( const QVector<int>& timeVector );
};

#endif // ALGORITHMMANAGER_H
