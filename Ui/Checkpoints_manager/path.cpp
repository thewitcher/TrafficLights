#include "path.h"
#include "../../Logger/logger.h"
#include "../Cars/vehicle.h"
#include <QPropertyAnimation>

Path::Path( Checkpoint *targetCheckpoint, int duration, const QByteArray property, const QVariant &startValue, const QVariant &endValue ):
    m_targetCheckpoint( targetCheckpoint ),
    m_duration( duration ),
    m_property( property ),
    m_startValue( startValue ),
    m_endValue( endValue )
{
}

Path::~Path()
{
}

void Path::animation( Vehicle *target, QObject *parent ) const
{
    QPropertyAnimation *propertyAnimation = new QPropertyAnimation( target, m_property, parent );

    propertyAnimation->setDuration( m_duration );
    propertyAnimation->setStartValue( m_startValue );
    propertyAnimation->setEndValue( m_endValue );
    propertyAnimation->start();
    propertyAnimation->setObjectName( "propertyAnimation" );

    QObject::connect( propertyAnimation, SIGNAL(finished()), target, SLOT(onAnimationFinish()) );

    LOG_INFO( "New animation was created for %s", target->objectName().toLatin1().data() );
}

const Checkpoint* Path::targetCheckpoint() const
{
    return m_targetCheckpoint;
}
