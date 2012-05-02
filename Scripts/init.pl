#!/bin/perl -w

use File::Copy;
use File::Find;
use Cwd;

my $checkpointConfigurationFile = 'Checkpoints_positions.pos';
my $targetDirectory = getcwd().'/TrafficLights_builded/Data/';
my $sourceDirectory = getcwd().'/Ui/Data/';

print "S: $sourceDirectory\n";
print "T: $targetDirectory\n";

copy( $sourceDirectory.$checkpointConfigurationFile, $targetDirectory.$checkpointConfigurationFile );
