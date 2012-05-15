#include "junction.h"
#include "../Lights/trafficlight.h"
#include "../Logger/logger.h"
#include "constans.h"
#include "vector"
#include "../Cars/vehicle.h"
#include "vehicle-count-manager.h"
#include "../Logic/Algorithm/Custom/algorithm-manager.h"
#include <QTimerEvent>
#include <QTimer>
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
    startAlgorithm();
}

Junction::~Junction()
{
    if( m_algorithmManager )
    {
        delete m_algorithmManager;
    }
}

void Junction::setDefaultTimeVector()
{
    m_timeVectorForSubcycles << 3000 << 3000 << 3000 << 3000;
}

void Junction::timerEvent( QTimerEvent *event )
{
    Q_UNUSED( event );

    LOG_INFO( "### --- Count - junction id: %i ---", m_junctionId );

    LOG_INFO( "### EAST_BOTTOM: %i",
    VehicleCountManager::vehicleCountOnLane( this, VehicleCountManager::EAST_BOTTOM ) );

    LOG_INFO( "### EAST_MIDDLE: %i",
    VehicleCountManager::vehicleCountOnLane( this, VehicleCountManager::EAST_MIDDLE ) );

    LOG_INFO( "### EAST_TOP: %i",
    VehicleCountManager::vehicleCountOnLane( this, VehicleCountManager::EAST_TOP ) );

    LOG_INFO( "### WEST_BOTTOM: %i",
    VehicleCountManager::vehicleCountOnLane( this, VehicleCountManager::WEST_BOTTOM ) );

    LOG_INFO( "### WEST_MIDDLE: %i",
    VehicleCountManager::vehicleCountOnLane( this, VehicleCountManager::WEST_MIDDLE ) );

    LOG_INFO( "### WEST_TOP: %i",
    VehicleCountManager::vehicleCountOnLane( this, VehicleCountManager::WEST_TOP ) );

    LOG_INFO( "### NORTH_LEFT: %i",
    VehicleCountManager::vehicleCountOnLane( this, VehicleCountManager::NORTH_LEFT ) );

    LOG_INFO( "### NORTH_MIDDLE: %i",
    VehicleCountManager::vehicleCountOnLane( this, VehicleCountManager::NORTH_MIDDLE ) );

    LOG_INFO( "### NORTH_RIGHT: %i",
    VehicleCountManager::vehicleCountOnLane( this, VehicleCountManager::NORTH_RIGHT ) );

    LOG_INFO( "### SOUTH_LEFT: %i",
    VehicleCountManager::vehicleCountOnLane( this, VehicleCountManager::SOUTH_LEFT ) );

    LOG_INFO( "### SOUTH_MIDDLE: %i",
    VehicleCountManager::vehicleCountOnLane( this, VehicleCountManager::SOUTH_MIDDLE ) );

    LOG_INFO( "### SOUTH_RIGHT: %i",
    VehicleCountManager::vehicleCountOnLane( this, VehicleCountManager::SOUTH_RIGHT ) );

    LOG_INFO( "TT --- Time - junction id: %i ---", m_junctionId );

    LOG_INFO( "TT EAST_BOTTOM: %i",
    VehicleCountManager::wholeVehicleWaitingTimeOnLane( this, VehicleCountManager::EAST_BOTTOM ) );

    LOG_INFO( "TT EAST_MIDDLE: %i",
    VehicleCountManager::wholeVehicleWaitingTimeOnLane( this, VehicleCountManager::EAST_MIDDLE ) );

    LOG_INFO( "TT EAST_TOP: %i",
    VehicleCountManager::wholeVehicleWaitingTimeOnLane( this, VehicleCountManager::EAST_TOP ) );

    LOG_INFO( "TT WEST_BOTTOM: %i",
    VehicleCountManager::wholeVehicleWaitingTimeOnLane( this, VehicleCountManager::WEST_BOTTOM ) );

    LOG_INFO( "TT WEST_MIDDLE: %i",
    VehicleCountManager::wholeVehicleWaitingTimeOnLane( this, VehicleCountManager::WEST_MIDDLE ) );

    LOG_INFO( "TT WEST_TOP: %i",
    VehicleCountManager::wholeVehicleWaitingTimeOnLane( this, VehicleCountManager::WEST_TOP ) );

    LOG_INFO( "TT NORTH_LEFT: %i",
    VehicleCountManager::wholeVehicleWaitingTimeOnLane( this, VehicleCountManager::NORTH_LEFT ) );

    LOG_INFO( "TT NORTH_MIDDLE: %i",
    VehicleCountManager::wholeVehicleWaitingTimeOnLane( this, VehicleCountManager::NORTH_MIDDLE ) );

    LOG_INFO( "TT NORTH_RIGHT: %i",
    VehicleCountManager::wholeVehicleWaitingTimeOnLane( this, VehicleCountManager::NORTH_RIGHT ) );

    LOG_INFO( "TT SOUTH_LEFT: %i",
    VehicleCountManager::wholeVehicleWaitingTimeOnLane( this, VehicleCountManager::SOUTH_LEFT ) );

    LOG_INFO( "TT SOUTH_MIDDLE: %i",
    VehicleCountManager::wholeVehicleWaitingTimeOnLane( this, VehicleCountManager::SOUTH_MIDDLE ) );

    LOG_INFO( "TT SOUTH_RIGHT: %i",
    VehicleCountManager::wholeVehicleWaitingTimeOnLane( this, VehicleCountManager::SOUTH_RIGHT ) );
}

void Junction::setTimeVectorByAlgorithm( const QVector<int> &timeVector )
{
    m_timeVectorForSubcycles = timeVector;
}

void Junction::runForSubcycles()
{
}

int Junction::currentNumberOfVehicles() const
{
    return m_currentNumberOfVehicles;
}

void Junction::addVehicleToStatistic( int checkpointId, Vehicle *vehicle )
{
    vehicle->setCurrentJunction( this );
    m_vehicleCountOnLanes[ Constans::mapCheckpointId2( checkpointId ) ]++;

    vehicle->setVehicleCanMove( false );
    m_waitingTime.insert( Constans::mapCheckpointId2( checkpointId ), vehicle );
    vehicle->updateWaitingTime();

    m_currentNumberOfVehicles++;
}

#ifdef COLLISIONS
void Junction::subtractVehicleFromStatistic( int checkpointId, Vehicle *vehicle )
{
    m_waitingTime.remove( Constans::mapCheckpointId( checkpointId ), vehicle );

    m_vehicleCountOnLanes[ Constans::mapCheckpointId( checkpointId ) ]--;

    m_currentNumberOfVehicles--;
}
#else

void Junction::subtractVehicleFromStatistic( int checkpointId, Vehicle *vehicle )
{
    LOG_INFO( "Vehicle with id: %i leave junction with time: %i", vehicle->vehicleId(), vehicle->waitingTimeInSeconds() );

    Vehicle* first = firstArrived( Constans::mapCheckpointId( checkpointId ) );

    m_waitingTime.remove( Constans::mapCheckpointId( checkpointId ), first );

    m_vehicleCountOnLanes[ Constans::mapCheckpointId( checkpointId ) ]--;

    m_currentNumberOfVehicles--;
}
#endif

Vehicle* Junction::firstArrived( int checkpointId )
{
    return m_waitingTime.values( checkpointId ).last();
}

void Junction::manageVehicle( uint flags, int checkpointId, Vehicle* vehicle )
{
    if( flags & 256 )
    {
        addVehicleToStatistic( checkpointId, vehicle );
    }
    else
    {
        subtractVehicleFromStatistic( checkpointId, vehicle );
    }

    m_vehicleCounter->display( m_currentNumberOfVehicles );
}

Junction::JUNCTION_TYPE Junction::junctionType() const
{
    return m_junctionType;
}

bool Junction::isVehicleFirst( Vehicle *vehicle )
{
    if( firstArrived( Constans::mapCheckpointId( vehicle->currentCheckpointId() ) )  == vehicle )
    {
        return true;
    }

    return false;
}

int Junction::id() const
{
    return m_junctionId;
}

const QHash<int,int> Junction::vehicleCountOnLanes() const
{
    return m_vehicleCountOnLanes;
}

const QMultiHash<int,Vehicle*> Junction::waitingTime() const
{
    return m_waitingTime;
}

void Junction::startAlgorithm()
{
    m_algorithmManager->start();
}
