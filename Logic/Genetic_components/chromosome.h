#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <QVector>

class Chromosome
{
public:
    Chromosome();

    int value() const;
    void setValue( int value );
    const QVector<int>& greenLigthDurations() const;

private:
    int m_value;
    QVector<int> m_greenLightDurations;
};

#endif // CHROMOSOME_H
