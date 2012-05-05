#ifndef MUTEXSINGLETON_H
#define MUTEXSINGLETON_H

#include <QMutex>

class MutexSingleton
{
public:
    static QMutex& mutexInstance();

private:
    MutexSingleton();
    ~MutexSingleton();
};

#endif // MUTEXSINGLETON_H
