#!/usr/bin/perl
#31 July 2015 - Adam D Scott - 

use strict;
use warnings;

use IO::File;
use FileHandle;

my $usage = 'perl random_lines.pl <input> #n-picks# <output> 
';

die $usage , unless @ARGV == 3;
my ( $type_ids , $n_picks , $output ) = @ARGV;

my $IN1 = FileHandle->new( "$type_ids" , "r" );
if ( not defined $IN1 ) { die "ADSERROR: Could not open/read $type_ids\n"; }

my $OUT = FileHandle->new( "$output" , "w" );
if ( not defined $OUT ) { die "ADSERROR: Could not open/write $output\n"; }

my @lines = $IN1->getlines();
$IN1->close();

my $wcl = scalar @lines;
for( my $i = 0; $i < $n_picks; $i++ ) {
	my $choose = int($wcl*rand());
	$OUT->print( $lines[$choose] );
}
$OUT->close();
