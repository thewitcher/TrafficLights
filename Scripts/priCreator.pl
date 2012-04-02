#!/bin/perl -w

# This script creates .pri file with all headers and sources in given directory. You can specify the name of pri file and directory or directories
# to search for files. Prefic variable is added before every file name to correct search path.

# Parameters:
# -n -> pri file name
# -d -> directory path

use Getopt::Long;
use File::Find;

$priFileName = "";
$directory = ".";
$prefix = "";

GetOptions( "n=s" => \$priFileName,
            "d=s" => \$directory,
            "p=s" => \$prefix );
        
print "Creating .pri file with approriate files in $directory\n";

sub wanted()
{
    $path = $_;
    
    if( $path =~ /\.h$/ )
    {
        push( @headers, $prefix.$path );
    }
    if( $path =~ /\.(cpp|C)$/ )
    {
        push( @sources, $prefix.$path );
    }
}

open( PRI_FILE, ">$priFileName" ) or die( "File $priFileName not found\n" );

print PRI_FILE "SOURCES += \\\n";

find( \&wanted, "$directory" );

$hCount = @headers;
$cppCount = @sources;

for( $i = 0 ; $i < $cppCount; $i++ )
{
    if( $i == $cppCount - 1 )
    {
        print PRI_FILE "           $sources[$i] \n";    
    }
    else
    {
        print PRI_FILE "           $sources[$i] \\\n";        
    }
}

print PRI_FILE "\n\n";
print PRI_FILE "HEADERS += \\\n";

for( $i = 0 ; $i < $hCount; $i++ )
{
    if( $i == $hCount - 1 )
    {
        print PRI_FILE "           $headers[$i] \n";    
    }
    else
    {
        print PRI_FILE "           $headers[$i] \\\n";        
    }
}

close( PRI_FILE );
print "Closing file $priFileName...\n";
