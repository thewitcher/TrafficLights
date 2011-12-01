#ifndef PATH_H
#define PATH_H

#include "checkpoint.h"
#include <QVariant>

class Vehicle;

/*!
 * Path contains target checkpoint and fucntion, which can create property animation. This animation is set to target object and will
 * be deleted by this object (this object is now parent of this animation).
 */
class Path
{
public:
    Path( Checkpoint *targetCheckpoint, int duration, const QByteArray property, const QVariant& startValue, const QVariant& endValue );
    ~Path();

    void animation( Vehicle *target, QObject *parent ) const;
    const Checkpoint* targetCheckpoint() const;

private:
    const Checkpoint *m_targetCheckpoint; // This will be deleted by checkpoint manager
    int m_duration;
    QByteArray m_property;
    const QVariant m_startValue;
    const QVariant m_endValue;
};

#endif // PATH_H
