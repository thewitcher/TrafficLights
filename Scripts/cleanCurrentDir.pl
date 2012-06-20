#!/bin/perl -w

use Cwd 'abs_path';
use Cwd;

# Absolute path to this script
$currentDirectory = abs_path( $0 );

# Delete last part - script name to get path to directory with scripts
$currentDirectory =~ s/Scripts\/cleanCurrentDir\.pl//;

# List of directories to clean:
# - TrafficLights_builded
# - DatabaseReader_builded

$dataBaseReader = "DatabaseReader_builded";
$trafficLights = "TrafficLights_builded";

# Cleans every temporary files except some like database, checkpoints file and user logs 
opendir( DATABASE_READER_DIR, $currentDirectory.$dataBaseReader );

while( my $file = readdir( DATABASE_READER_DIR ) )
{
    if( $file =~ /^moc|\.o$|^ui_|^qrc_|^DatabaseReader$|^Makefile$|\.csv$/ )
    {
        unlink( $currentDirectory.$dataBaseReader."/".$file );
    }   
}

closedir( DATABASE_READER_DIR );

##################################################
opendir( TRAFFIC_LIGHTS_DIR, $currentDirectory.$trafficLights );

while( my $file = readdir( TRAFFIC_LIGHTS_DIR ) )
{
    if( $file =~ /^moc|\.o$|^ui_|^qrc_|^application$|^Makefile$/ )
    { 
        unlink( $currentDirectory.$trafficLights."/".$file );
    }   
}

closedir( TRAFFIC_LIGHTS_DIR );
