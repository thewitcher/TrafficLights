#include "bus-car.h"

BusCar::BusCar( QDeclarativeItem *parent ):
    Vehicle( parent )
{
}

void BusCar::setDarkDesign( bool dark )
{
    if( dark )
    {
        setProperty( "imageSource", "qrc:/graphics/Graphics/bus4_small_dark.png" );
    }
    else
    {
        setProperty( "imageSource", "qrc:/graphics/Graphics/bus4_small_bright.png" );
    }
}
