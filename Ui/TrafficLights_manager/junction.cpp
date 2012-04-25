#include "junction.h"
#include "../Lights/trafficlight.h"
#include "../Logger/logger.h"
#include "constans.h"
#include "vector"
#include "../Cars/vehicle.h"
#include "vehicle-count-manager.h"
#include "../Logic/Algorithm/Custom/algorithm-manager.h"
#include <QTimerEvent>
#include <QLCDNumber>


Junction::Junction( const QVector<TrafficLight *> &junction, QLCDNumber *m_vehicleCounter, int junctionId,
                    JUNCTION_TYPE junctionType ):
    QObject( NULL ),
    m_trafficLightVector( junction ),
    m_pauseBetweenSubcycles( 2000 ),
    m_interval( 500 ),
    m_currentNumberOfVehicles( 0 ),
    m_vehicleCounter( m_vehicleCounter ),
    m_junctionId( junctionId ),
    m_junctionType( junctionType )
{
    m_algorithmManager = new AlgorithmManager( this );

    startTimer( 10000 );
    setTimeVectorByAlgorithm();
}

Junction::~Junction()
{
    if( m_algorithmManager )
    {
        delete m_algorithmManager;
    }
}

void Junction::timerEvent( QTimerEvent *event )
{
    Q_UNUSED( event );

    LOG_INFO( "### --- Count - junction id: %i ---", m_junctionId );

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

    LOG_INFO( "TT --- Time - junction id: %i ---", m_junctionId );

    LOG_INFO( "TT EAST_BOTTOM: %i",
    VehicleCountManager::wholeVehicleWaitingTimeOnLane( m_waitingTime, VehicleCountManager::EAST_BOTTOM, m_junctionId ) );

    LOG_INFO( "TT EAST_MIDDLE: %i",
    VehicleCountManager::wholeVehicleWaitingTimeOnLane( m_waitingTime, VehicleCountManager::EAST_MIDDLE, m_junctionId ) );

    LOG_INFO( "TT EAST_TOP: %i",
    VehicleCountManager::wholeVehicleWaitingTimeOnLane( m_waitingTime, VehicleCountManager::EAST_TOP, m_junctionId ) );

    LOG_INFO( "TT WEST_BOTTOM: %i",
    VehicleCountManager::wholeVehicleWaitingTimeOnLane( m_waitingTime, VehicleCountManager::WEST_BOTTOM, m_junctionId ) );

    LOG_INFO( "TT WEST_MIDDLE: %i",
    VehicleCountManager::wholeVehicleWaitingTimeOnLane( m_waitingTime, VehicleCountManager::WEST_MIDDLE, m_junctionId ) );

    LOG_INFO( "TT WEST_TOP: %i",
    VehicleCountManager::wholeVehicleWaitingTimeOnLane( m_waitingTime, VehicleCountManager::WEST_TOP, m_junctionId ) );

    LOG_INFO( "TT NORTH_LEFT: %i",
    VehicleCountManager::wholeVehicleWaitingTimeOnLane( m_waitingTime, VehicleCountManager::NORTH_LEFT, m_junctionId ) );

    LOG_INFO( "TT NORTH_MIDDLE: %i",
    VehicleCountManager::wholeVehicleWaitingTimeOnLane( m_waitingTime, VehicleCountManager::NORTH_MIDDLE, m_junctionId ) );

    LOG_INFO( "TT NORTH_RIGHT: %i",
    VehicleCountManager::wholeVehicleWaitingTimeOnLane( m_waitingTime, VehicleCountManager::NORTH_RIGHT, m_junctionId ) );

    LOG_INFO( "TT SOUTH_LEFT: %i",
    VehicleCountManager::wholeVehicleWaitingTimeOnLane( m_waitingTime, VehicleCountManager::SOUTH_LEFT, m_junctionId ) );

    LOG_INFO( "TT SOUTH_MIDDLE: %i",
    VehicleCountManager::wholeVehicleWaitingTimeOnLane( m_waitingTime, VehicleCountManager::SOUTH_MIDDLE, m_junctionId ) );

    LOG_INFO( "TT SOUTH_RIGHT: %i",
    VehicleCountManager::wholeVehicleWaitingTimeOnLane( m_waitingTime, VehicleCountManager::SOUTH_RIGHT, m_junctionId ) );
}

void Junction::setTimeVectorByAlgorithm()
{
    m_timeVectorForSubcycles = m_algorithmManager->start();
}

void Junction::runForSubcycles()
{
}

int Junction::currentNumberOfVehicles() const
{
    return m_currentNumberOfVehicles;
}

void Junction::manageVehicle( uint flags, uchar checkpointId, Vehicle* vehicle )
{
    if( flags & 256 )
    {
        m_vehicleCountOnLanes[ checkpointId ]++;

        m_waitingTime.insert( checkpointId, vehicle );
        vehicle->updateWaitingTime();

        m_currentNumberOfVehicles++;
    }
    else
    {
        m_waitingTime.remove( Constans::mapCheckpointId( checkpointId ), vehicle );

        m_vehicleCountOnLanes[ Constans::mapCheckpointId( checkpointId ) ]--;

        m_currentNumberOfVehicles--;
    }

    m_vehicleCounter->display( m_currentNumberOfVehicles );
}

Junction::JUNCTION_TYPE Junction::junctionType() const
{
    return m_junctionType;
}
