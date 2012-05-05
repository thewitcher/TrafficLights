#include "mutex-singleton.h"


MutexSingleton::MutexSingleton()
{
}

MutexSingleton::~MutexSingleton()
{
}

QMutex& MutexSingleton::mutexInstance()
{
    static QMutex mutex;

    return mutex;
}
