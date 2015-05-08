#!/bin/perl
#18 December 2014 - Adam D Scott - 
 
use strict;
use warnings;
 
my $usage = 'perl numhead.pl <input1>  
';
 
die $usage , unless @ARGV == 1;
my ( $input1 ) = @ARGV;
 
open ( IN , "<$input1" ) or die "Cannot open $input1: $!";
my @line = split( "\t" , <IN> );
close IN;
my $n = 1;
foreach ( @line )
{
	print $n."\t".$_."\n";
	$n++;
}
