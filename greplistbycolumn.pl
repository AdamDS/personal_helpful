#!/bin/perl
#30 July 2014 - Adam D Scott - updated 13 October 2014

use strict;
use warnings;

my $usage = 'perl greplistbycolumn.pl file_to_read word column match_or_mismatch
';
die $usage , unless @ARGV == 4;

my ( $file_to_read , $list_of_words , $col , $match ) = @ARGV;

my %list_of_words = ();
open ( IN , "<".$list_of_words ) or die "Could not open $list_of_words $!";
while ( <IN> )
{
	chomp;
	$list_of_words{$_} = 1;
}
close IN;

open ( file_to_read , "<".$file_to_read ) or die "Could not open $file_to_read $!";
#if ( $match )
#{
#	open ( file_to_read_of_word , ">"."$file_to_read\_$list_of_words.$col.match" ) or die "Could not open "."$file_to_read\_$list_of_words"." $!";
#}
#else
#{
#	open ( file_to_read_of_word , ">"."$file_to_read\_$list_of_words.$col.mismatch" ) or die "Could not open "."$file_to_read\_$list_of_words"." $!";
#}
while ( <file_to_read> )
{
	chomp;
	my @line = split( "\t" , $_ );
	if ( $match == 2 )
	{#match exact
		if ( exists $list_of_words{$line[$col-1]} )
		{
#			print file_to_read_of_word $_."\n";
			print $_."\n";
		}
	}
	elsif ( $match == 1 )
	{#partial match
		my $search = $line[$col-1];
		if ( grep { $search =~ /$_/ } keys %list_of_words )
		{
			print $_."\n";
		}
	}
	else
	{#not match
		if ( ! exists $list_of_words{$line[$col-1]} )
		{
#			print file_to_read_of_word $_."\n";
			print $_."\n";
		}
	}
}
#close file_to_read_of_word;
close file_to_read;
