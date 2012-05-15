#ifndef JUNCTION_H
#define JUNCTION_H

#include <QObject>
#include <QVector>
#include <QHash>
#include <QTimer>

class QLCDNumber;
class TrafficLight;
class Vehicle;
class AlgorithmManager;

/*!
 * This is abstract base class for all junctions in our program.
 */
class Junction: public QObject
{

    Q_OBJECT

public:
    enum JUNCTION_TYPE { BLADZIO, SIMPLE, NO_TYPE };

    Junction( const QVector<TrafficLight*>& junction, QLCDNumber* m_vehicleCounter, int junctionId, JUNCTION_TYPE junctionType );
    virtual ~Junction();

    /// It is called when vehicles arrived or leave junction.
    void manageVehicle( uint flags, int checkpointId, Vehicle* vehicle );
    /// Current number of vehicles on whole junction.
    int currentNumberOfVehicles() const;
    JUNCTION_TYPE junctionType() const;
    bool isVehicleFirst( Vehicle* vehicle );
    int id() const;
    const QHash<int,int> vehicleCountOnLanes() const;
    const QMultiHash<int,Vehicle*> waitingTime() const;

    virtual void runForSubcycles() = 0;

    /// It uses genetic algorithm to create appropriate time vector for that junction.
    virtual void setTimeVectorByAlgorithm( const QVector<int>& timeVector );
    void setDefaultTimeVector();

protected:
    Vehicle* firstArrived( int checkpointId );

    /// Contains all traffic lights uses by this junction.
    const QVector<TrafficLight*> m_trafficLightVector;

    /// Time for all cycles in this junction.
    QVector<int> m_timeVectorForSubcycles;

    /// Break between subcycles.
    const int m_pauseBetweenSubcycles;

    /// Specifying the length of times lights activation.
    const int m_interval;

    /// Just number of vehicles before red lights (it counts all vehicles on junction)
    int m_currentNumberOfVehicles;

    /// Counter to show how many vehicles are currently on junction
    QLCDNumber* m_vehicleCounter;
    QHash<int,int> m_vehicleCountOnLanes;
    QMultiHash<int,Vehicle*> m_waitingTime;
    int m_junctionId;
    AlgorithmManager *m_algorithmManager;
    JUNCTION_TYPE m_junctionType;

    void timerEvent( QTimerEvent *event );
    /// If it returns true then time vector should be changed, otherwise it is ok and should not be changed.
    bool changeTimeVector();

protected slots:
    void addVehicleToStatistic( int checkpointId, Vehicle* vehicle );
    void subtractVehicleFromStatistic( int checkpointId, Vehicle* vehicle );
    void startAlgorithm();

protected:

    /*! Following templates functions: runFirstSubcycle(), runSecondSubcycle(), runThirdSubcycle(),
        and runFourthSubcycle() trigger start up subcycles for appropriate junction. The remaining
        functions are auxiliary for the above_mentioned.
        Each function as the last parameter assumes pointer to appropriate junction.
        This pointer allows you to call correct function, which manages the approriate light.
        For example when you call junction->subcycleIDSubcycle() or junction->holdSubcycleIDSubcycle(),
        you directly turn on or turn off appropriate light.
    */

    /*! This template function triggers first subcycle. Assumes as a first arrgument burning time
        the green lights for first subcycle. Inside is call auxiliary function, which is calls when
        burning time the green light is different than zero. When this time is equal zero first subcycle
        is not calls.
    */
    template<typename T>
    void runFirstSubcycle( const uint& subcycle_1, T* junction )
    {
        if( subcycle_1 != 0 )
        {
            runSingleShotForSubcycle_1_WhenTimeIsDiferrentThanZero( subcycle_1, junction );
        }
    }

    /*! This template function triggers second subcycle. Assumes as a first two parameters burning
        times the green lights of the following subcycles: first and second. Inside is call
        auxiliary functions, which are call when burning time the green light for second subcycle is
        different than zero. When this time is equal zero second subcycle is not call.
    */
    template<typename T>
    void runSecondSubcycle( const uint& subcycle_1, const uint& subcycle_2, T* junction )
    {
        if( subcycle_2 != 0 )
        {
            if( subcycle_1 != 0 )
            {
                runSingleShotForSubcycle_2_WhenTimeIsDiferrentThanZero( subcycle_1, subcycle_2, junction );
            }
            else{
                runSingleShotForSubcycle_2_WhenTimeAreEqualZero( subcycle_2, junction );
            }
        }
    }

    /*! This template function triggers third subcycle. Except a pointer assume are three burning times
        the green lights for the following subcycles: first, second, third. Inside is call auxiliary functions,
        which are call when burning time the green light for third subcycle is different than zero.
        Otherwise third subcycle is not call.
    */
    template<typename T>
    void runThirdSubcycle( const uint& subcycle_1, const uint& subcycle_2, const uint& subcycle_3, T* junction )
    {
        if( subcycle_3 != 0 )
        {
            if( subcycle_1 != 0 && subcycle_2 != 0 )
            {
                runSingleShotForSubcycle_3_WhenAllTimesAreDiferrentThanZero( subcycle_1, subcycle_2, subcycle_3, junction );
            }
            else if( subcycle_1 == 0 && subcycle_2 != 0 )
            {
                runSingleShotForSubcycle_3_WhenOneTimeIsDiferrentThanZero( subcycle_2, subcycle_3, junction );
            }
            else if( subcycle_1 != 0 && subcycle_2 == 0 )
            {
                runSingleShotForSubcycle_3_WhenOneTimeIsDiferrentThanZero( subcycle_1, subcycle_3, junction );
            }
            else if( subcycle_1 == 0 && subcycle_2 == 0 )
            {
                runSingleShotForSubcycle_3_WhenAllTimesAreEqualZero( subcycle_3, junction );
            }
        }
    }

    /*! This template function triggers second subcycle. Except a pointer assume are four times the green lights
        for the following subcycles: first, second, third and fourth. Inside is call auxiliary functions,
        which is call when burning time the green light for fourth subcycle is different than zero. Otherwise
        fourth subcycle is not call.
    */
    template<typename T>
    void runFourthSubcycle( const uint& subcycle_1, const uint& subcycle_2, const uint& subcycle_3, const uint& subcycle_4, T* junction )
    {
        if( subcycle_4 != 0 )
        {
            if( subcycle_1 != 0 && subcycle_2 != 0 && subcycle_3 != 0 )
            {
                runSingleShotForSubcycle_4_WhenAllTimesAreDiferrentThanZero( subcycle_1, subcycle_2, subcycle_3, subcycle_4, junction );
            }
            else if( subcycle_1 != 0 && subcycle_2 != 0 && subcycle_3 == 0 )
            {
                runSingleShotForSubcycle_4_WhenTwoTimesAreDiferrentThanZero( subcycle_1, subcycle_2, subcycle_4, junction );
            }
            else if( subcycle_1 == 0 && subcycle_2 != 0 && subcycle_3 != 0 )
            {
                runSingleShotForSubcycle_4_WhenTwoTimesAreDiferrentThanZero( subcycle_2, subcycle_3, subcycle_4, junction );
            }
            else if( subcycle_1 != 0 && subcycle_2 == 0 && subcycle_3 != 0 )
            {
                runSingleShotForSubcycle_4_WhenTwoTimesAreDiferrentThanZero( subcycle_1, subcycle_3, subcycle_4, junction );
            }
            else if( subcycle_1 != 0 && subcycle_2 == 0 && subcycle_3 == 0 )
            {
                runSingleShotForSubcycle_4_WhenOneTimeIsDiferrentThanZero( subcycle_1, subcycle_4, junction );
            }
            else if( subcycle_1 == 0 && subcycle_2 != 0 && subcycle_3 == 0 )
            {
                runSingleShotForSubcycle_4_WhenOneTimeIsDiferrentThanZero( subcycle_2, subcycle_4, junction );
            }
            else if( subcycle_1 == 0 && subcycle_2 == 0 && subcycle_3 != 0 )
            {
                runSingleShotForSubcycle_4_WhenOneTimeIsDiferrentThanZero( subcycle_3, subcycle_4, junction );
            }
            else if( subcycle_1 == 0 && subcycle_2 == 0 && subcycle_3 == 0 )
            {
                runSingleShotForSubcycle_4_WhenAllTimesAreEqualZero( subcycle_4, junction );
            }
        }
    }

    /*! Auxiliary function, activates first subcycle and at the right time hold this subcycle. */
    template<typename T>
    void runSingleShotForSubcycle_1_WhenTimeIsDiferrentThanZero( const uint& time, T* junction )
    {
        junction->firstSubcycle();
        QTimer::singleShot( time + m_interval, junction, SLOT(holdFirstSubcycle()));
    }

    /*! Auxiliary function, activates second subcycle and at the right time hold this subcycle.
        This function is calls when first subcycle time is equal zero.
    */
    template<typename T>
    void runSingleShotForSubcycle_2_WhenTimeAreEqualZero( const uint& time, T* junction )
    {
        junction->secondSubcycle();
        QTimer::singleShot( time + m_interval, junction, SLOT(holdSecondSubcycle()));
    }

    /*! Auxiliary function, at the right time activates second subcycle and hold this subcycle.
        This function is calls when first subcycle time is different than zero.
    */
    template<typename T>
    void runSingleShotForSubcycle_2_WhenTimeIsDiferrentThanZero( const uint& time_1, const uint& time_2, T* junction )
    {
        QTimer::singleShot( time_1 + ( m_interval * 2 ) + m_pauseBetweenSubcycles, junction, SLOT(secondSubcycle()));
        QTimer::singleShot( time_1 + time_2 + ( m_interval * 3 ) + m_pauseBetweenSubcycles,
                            junction, SLOT(holdSecondSubcycle()));
    }

    /*! Auxiliary function, activates third subcycle and at the right time hold this subcycle.
        This function is calls when first and second subcycles times are equal zero.
    */
    template<typename T>
    void runSingleShotForSubcycle_3_WhenAllTimesAreEqualZero( const uint& time, T* junction )
    {
        junction->thirdSubcycle();
        QTimer::singleShot( time + m_interval, junction, SLOT(holdThirdSubcycle()));
    }

    /*! Auxiliary function, at the right time activates third subcycle and hold this subcycle.
        This function is calls when first and second subcycles times are different than zero.
    */
    template<typename T>
    void runSingleShotForSubcycle_3_WhenAllTimesAreDiferrentThanZero( const uint& time_1, const uint& time_2, const uint& time_3, T* junction )
    {
        QTimer::singleShot( time_1 + time_2 + ( m_interval * 4 ) + ( m_pauseBetweenSubcycles * 2 ),
                            junction, SLOT(thirdSubcycle()));
        QTimer::singleShot( time_1 + time_2 + time_3 + ( m_interval * 5 ) + ( m_pauseBetweenSubcycles * 2 ),
                            junction, SLOT(holdThirdSubcycle()));
    }

    /*! Auxiliary function, at the right time activates third subcycle and time hold this subcycle.
        This function is calls when first subcycle time is equal zero and second subcycle time
        is different than zero or vice versa.
    */
    template<typename T>
    void runSingleShotForSubcycle_3_WhenOneTimeIsDiferrentThanZero( const uint& time_1, const uint& time_2, T* junction )
    {
        QTimer::singleShot( time_1 + ( m_interval * 2 ) + m_pauseBetweenSubcycles, junction, SLOT(thirdSubcycle()));
        QTimer::singleShot( time_1 + time_2 + ( m_interval * 3 ) + m_pauseBetweenSubcycles,
                            junction, SLOT(holdThirdSubcycle()));
    }

    /*! Auxiliary function, at the right time activates fourth subcycle and hold this subcycle.
        This function is calls when two of three subcycles times are equal zero. As the first argument
        assume is non-zero time one of the following subcycles: first, second or third and as second argument
        assume is burning time the green light for fourth subcycle.
    */
    template<typename T>
    void runSingleShotForSubcycle_4_WhenOneTimeIsDiferrentThanZero( const uint& time_1, const uint& time_2, T* junction )
    {
        QTimer::singleShot( time_1 + ( m_interval * 2 ) + m_pauseBetweenSubcycles,
                            junction, SLOT(fourthSubcycle()));
        QTimer::singleShot( time_1 + time_2 + ( m_interval * 3 ) + m_pauseBetweenSubcycles,
                            junction, SLOT(holdFourthSubcycle()));
    }

    /*! Auxiliary function, at the right time activates fourth subcycle and hold this subcycle.
        This function is calls when one of the following subcycles: first, second or third are equal zero.
        First two assume arguments are burning times the green lights for appropriate subcycles. Third argument
        is burning time the green light.
    */
    template<typename T>
    void runSingleShotForSubcycle_4_WhenTwoTimesAreDiferrentThanZero( const uint& time_1, const uint& time_2, const uint& time_3, T* junction )
    {
        QTimer::singleShot( time_1 + time_2 + ( m_interval * 4 ) + ( m_pauseBetweenSubcycles * 2 ),
                            junction, SLOT(fourthSubcycle()));
        QTimer::singleShot( time_1 + time_2 + time_3 + ( m_interval * 5 ) + ( m_pauseBetweenSubcycles * 2 ),
                            junction, SLOT(holdFourthSubcycle()));
    }

    /*! Auxiliary function, at the right time activates fourth subcycle and hold this subcycle.
        This function is calls when all lights burning times of the following subcycles: first, second
        or third are different than zero.
    */
    template<typename T>
    void runSingleShotForSubcycle_4_WhenAllTimesAreDiferrentThanZero( const uint& time_1, const uint& time_2, const uint& time_3, const uint& time_4, T* junction )
    {
        QTimer::singleShot( time_1 + time_2 + time_3 + ( m_interval * 6 ) + ( m_pauseBetweenSubcycles * 3),
                            junction, SLOT(fourthSubcycle()));
        QTimer::singleShot( time_1 + time_2 + time_3 + time_4 + ( m_interval * 7 ) + ( m_pauseBetweenSubcycles * 3),
                            junction, SLOT(holdFourthSubcycle()));
    }

    /*! Auxiliary function, activates fourth subcycle and at the right time hold this subcycle.
        This function is calls when all of the following subcycles: first, second and third are equal zero.
        As argument is assume burning time the green light.
    */
    template<typename T>
    void runSingleShotForSubcycle_4_WhenAllTimesAreEqualZero( const uint& time, T* junction )
    {
        junction->fourthSubcycle();
        QTimer::singleShot( time + m_interval, junction, SLOT(holdFourthSubcycle()));
    }
};

#endif // JUNCTION_H
