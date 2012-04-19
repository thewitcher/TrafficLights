#include "junction.h"
#include "../Lights/trafficlight.h"
#include "../Logger/logger.h"
#include "vector"
#include "vehicle-count-manager.h"
#include <QTimerEvent>
#include <QLCDNumber>


Junction::Junction( const QVector<TrafficLight *> &junction, QLCDNumber *m_vehicleCounter, int junctionId ):
    QObject( NULL ),
    m_trafficLightVector( junction ),
    m_interval( 500 ),
    m_currentNumberOfVehicles( 0 ),
    m_vehicleCounter( m_vehicleCounter ),
    m_junctionId( junctionId )
{
    startTimer( 10000 );
}

Junction::~Junction()
{
}

void Junction::timerEvent( QTimerEvent *event )
{
    Q_UNUSED( event );

    LOG_INFO( "### --- Junction id: %i ---", m_junctionId );

    LOG_INFO( "### EAST_BOTTOM: %i",
              VehicleCountManager::vehicleCountOnLane( m_vehicleCountOnLanes, VehicleCountManager::EAST_BOTTOM, m_junctionId ) );

    LOG_INFO( "### EAST_MIDDLE: %i",
    VehicleCountManager::vehicleCountOnLane( m_vehicleCountOnLanes, VehicleCountManager::EAST_MIDDLE, m_junctionId ) );

    LOG_INFO( "### EAST_TOP: %i",
    VehicleCountManager::vehicleCountOnLane( m_vehicleCountOnLanes, VehicleCountManager::EAST_TOP, m_junctionId ) );

    LOG_INFO( "### WEST_BOTTOM: %i",
    VehicleCountManager::vehicleCountOnLane( m_vehicleCountOnLanes, VehicleCountManager::WEST_BOTTOM, m_junctionId ) );

    LOG_INFO( "### WEST_MIDDLE: %i",
    VehicleCountManager::vehicleCountOnLane( m_vehicleCountOnLanes, VehicleCountManager::WEST_MIDDLE, m_junctionId ) );

    LOG_INFO( "### WEST_TOP: %i",
    VehicleCountManager::vehicleCountOnLane( m_vehicleCountOnLanes, VehicleCountManager::WEST_TOP, m_junctionId ) );

    LOG_INFO( "### NORTH_LEFT: %i",
    VehicleCountManager::vehicleCountOnLane( m_vehicleCountOnLanes, VehicleCountManager::NORTH_LEFT, m_junctionId ) );

    LOG_INFO( "### NORTH_MIDDLE: %i",
    VehicleCountManager::vehicleCountOnLane( m_vehicleCountOnLanes, VehicleCountManager::NORTH_MIDDLE, m_junctionId ) );

    LOG_INFO( "### NORTH_RIGHT: %i",
    VehicleCountManager::vehicleCountOnLane( m_vehicleCountOnLanes, VehicleCountManager::NORTH_RIGHT, m_junctionId ) );

    LOG_INFO( "### SOUTH_LEFT: %i",
    VehicleCountManager::vehicleCountOnLane( m_vehicleCountOnLanes, VehicleCountManager::SOUTH_LEFT, m_junctionId ) );

    LOG_INFO( "### SOUTH_MIDDLE: %i",
    VehicleCountManager::vehicleCountOnLane( m_vehicleCountOnLanes, VehicleCountManager::SOUTH_MIDDLE, m_junctionId ) );

    LOG_INFO( "### SOUTH_RIGHT: %i",
    VehicleCountManager::vehicleCountOnLane( m_vehicleCountOnLanes, VehicleCountManager::SOUTH_RIGHT, m_junctionId ) );
}

void Junction::setTimeVector( QVector<int> &time )
{
    m_timeVector = time;
}

void Junction::setTimeVectorByGeneticAlgorithm()
{
}

void Junction::run()
{
}

int Junction::currentNumberOfVehicles() const
{
    return m_currentNumberOfVehicles;
}

void Junction::manageVehicle( uint flags, uchar checkpointId )
{
    Q_UNUSED( checkpointId );

    if( flags & 256 )
    {
        m_vehicleCountOnLanes[ checkpointId ]++;
        m_currentNumberOfVehicles++;
    }
    else
    {
        m_vehicleCountOnLanes[ checkpointId ]--;
        m_currentNumberOfVehicles--;
    }

    m_vehicleCounter->display( m_currentNumberOfVehicles );
}
