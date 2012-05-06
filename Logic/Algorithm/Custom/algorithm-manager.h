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

    void updateAlgorithm( Junction* junction );
};

#endif // ALGORITHMMANAGER_H
