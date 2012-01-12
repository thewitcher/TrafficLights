#include "deploy-trafficlights.h"
#include "../Ui/Lights/trafficlight.h"
#include "../Ui/Root_window/qml-helper.h"
#include "../Logger/logger.h"

DeployTrafficLights::DeployTrafficLights()
{
    setLights();
}

/*!
 * This function sets coordinates for all TrafficLight items in cross.
 */
void DeployTrafficLights::setLights()
{

    QVector<qreal> cross1;           /* Cross 1 */
    cross1 << 286 << 90 << 0
              << 372 << 90 << 0
                 << 380 << -8.5 << -90
                    << 160 << 72 << 90;
    templateSimpleCross( cross1, 1 );

    QVector<qreal> cross2;           /* Cross 2 */
    cross2 << 101 << 471 << -90
              << 101 << 386 << -90
                 << 3.5 << 376 << 180
                    << 88 << 600 << 0;
    templateSimpleCross( cross2, 2 );

    QVector<qreal> cross3;           /* Cross 3 */
    cross3 << 286.5 << 372 << 180                   /* 3 a */
              << 170 << 372 << 180
                 << 150 << 372 << 180
           << 158 << 469 << 90                      /* 3 b */
              << 158 << 583 << 90
                 << 158 << 603 << 90
           << 254 << 599 << 0                       /* 3 c */
              << 370 << 599 << 0
                 << 390 << 599 << 0
           << 381 << 501 << -90                     /* 3 d */
              << 381 << 386 << -90
                 << 381 << 366 << -90;
    templatecomplexCross( cross3, 3 );

    QVector<qreal> cross4;           /* Cross 4 */
    cross4 << 255 << 940 << 180
              << 171 << 940 << 180
                 << 160 << 1038 << 90
                    << 385 << 955 << -90;
    templateSimpleCross( cross4, 4 );

    QVector<qreal> cross5;           /* Cross 5 */
    cross5 << 751 << 940 << 180
              << 666 << 940 << 180
                 << 652 << 1038 << 90
                    << 880 << 955 << -90;
    templateSimpleCross( cross5, 5 );

    QVector<qreal> cross6;           /* Cross 6 */
    cross6 << 1212 << 500 << 90
              << 1212 << 585 << 90
                 << 1307 << 596 << 0
                    << 1227 << 370 << 180;
    templateSimpleCross( cross6, 6 );

    QVector<qreal> cross7;           /* Cross 7 */
    cross7 << 780 << 90 << 0
              << 865 << 90 << 0
                 << 883 << -8.5 << -90
                    << 652.5 << 72 << 90;
    templateSimpleCross( cross7, 7 );
}

/*!
 * It's simple template for creates TrafficLight item for simple cross.
 */

void DeployTrafficLights::templateSimpleCross( QVector<double> vector, unsigned int id )
{
    QVector<TrafficLight*> container;

    if( vector.count() == 12 )
    {
        TrafficLight * light1 = QmlHelper::createLightsFromQml( "Lights" );
        light1->setPos( vector.at( 0 ), vector.at( 1 ) );
        light1->setRotation( vector.at( 2 ) );
        light1->setDirection( light1, TrafficLight::LEFT );

        TrafficLight * light2 = QmlHelper::createLightsFromQml( "Lights" );
        light2->setPos( vector.at( 3 ), vector.at( 4 ) );
        light2->setRotation( vector.at( 5 ) );
        light2->setDirection( light2, TrafficLight::RIGHT );

        TrafficLight * light3 = QmlHelper::createLightsFromQml( "Lights" );
        light3->setPos( vector.at( 6 ), vector.at( 7 ) );
        light3->setRotation( vector.at( 8 ) );
        light3->setDirection( light3, TrafficLight::STRAIGHT_AND_LEFT );

        TrafficLight * light4 = QmlHelper::createLightsFromQml( "Lights" );
        light4->setPos( vector.at( 9 ), vector.at( 10 ) );
        light4->setRotation( vector.at( 11 ) );
        light4->setDirection( light4, TrafficLight::STRAIGHT_AND_RIGHT );

        light1->changeState();   // for test
        container << light1 << light2 << light3 << light4;
    }
    lights.insert( id, container );
}

/*!
 * It's complex template for creates TrafficLight item for Bladzio cross.
 */
void DeployTrafficLights::templatecomplexCross( QVector<qreal> vector, unsigned int id )
{
    if( vector.count() == 36 ){

        unsigned int x = 0;
        unsigned int y = 1;
        unsigned int angle = 2;
        QVector<TrafficLight*> container;

        for( unsigned int i = 0; i < 4; i++ )
        {
            TrafficLight * light1 = QmlHelper::createLightsFromQml( "Lights" );
            light1->setPos( vector.at( x ), vector.at( y ) );
            light1->setRotation( vector.at( angle ) );
            light1->setDirection( light1, TrafficLight::LEFT );

            LOG_INFO( "%s was created and added to scene", light1->objectName().toLatin1().data() );
            x += 3, y += 3, angle += 3;

            TrafficLight * light2 = QmlHelper::createLightsFromQml( "Lights" );
            light2->setPos( vector.at( x ), vector.at( y ) );
            light2->setRotation( vector.at( angle ) );
            light2->setDirection( light2, TrafficLight::STRAIGHT );

            LOG_INFO( "%s was created and added to scene", light2->objectName().toLatin1().data() );
            x += 3, y += 3, angle += 3;

            TrafficLight * light3 = QmlHelper::createLightsFromQml( "Lights" );
            light3->setPos( vector.at( x ), vector.at( y ) );
            light3->setRotation( vector.at( angle ) );
            light3->setDirection( light3, TrafficLight::RIGHT );

            LOG_INFO( "%s was created and added to scene", light3->objectName().toLatin1().data() );
            x += 3, y += 3, angle += 3;

            container << light1 << light2 << light3;
        }
        lights.insert( id, container );
    }
}

/*!
 * Returns map all TrafficLight items.
 */
QMap< int, QVector<TrafficLight*> >& DeployTrafficLights::trafficLightsMap()
{
    return lights;
}
