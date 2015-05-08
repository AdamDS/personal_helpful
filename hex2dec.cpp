//hex2dec.cpp
//26 March 2015 - Adam D Scott - 
 
#include <iostream> //cin, cout, cerr, clog
#include <cstdlib> //rand, string conversion
#include <cstdio> //rand, string conversion
#include <sstream> //stringstream
#include <string> //string, C++11: stoi, stod, to_string
#include <vector> //vector, 
#include <map> //map, multimap
#include <cmath> //trig, hyperbolics, exp, log

typedef std::string str;
typedef std::stringstream strm;

str int2str( const int& );
int str2int( const str& );
str num2str( const double& );
double str2num( const str& );
str hex22decnum( const int& , str& );
void convert( str& );
 
int main( int argc , char** argv )
{
	str color;
	str original;
	std::vector<str> vals;
	int decbase = 10;

	for ( int i = 1; i < argc; i++ ) {
		original = argv[i];
		color = argv[i];
		color = hex22decnum( decbase , original );
		std::cout << "#" << original << "\t" << color << std::endl;
	}
	std::cout << std::endl;

	return 0;
}

str int2str( const int& ent ) {
	strm ss;
	ss << ent;
	str str = ss.str();

	return str;
}

int str2int( const str& str ) {
	return atoi( str.c_str() );
}

str num2str( const double& ent ) {
	strm ss;
	ss << ent;
	str str = ss.str();

	return str;
}

double str2num( const str& str ) {
	return atof( str.c_str() );
}

str hex22decnum( const int& decbase , str& ent ) {
	int values = 0;
	str out = "[";
	str frac = "[";
	int hexbase = 16;

	int i = 0;
	int product = 0;
	for( i; i < 7; i++ ) {
		if ( i % 2 == 0 ) { //multiplier
			str mult = ent.substr( i , 1 );
			convert( mult );
			int multiplier = str2int( mult );
			product = hexbase*( multiplier );
			//values = product;
		} else {
			str rem = ent.substr( i , 1 );
			convert( rem );
			int remainder = str2int( rem );
			values = product + remainder;
			out += int2str( values );
			frac += num2str( double( ( 1 + values )/pow( hexbase , 2 ) ) );
			if ( i < 5 ) {
				out += ", ";
				frac += ", ";
			}
		}
	}
	out += "] " + frac + "]";
	return out;
}

void convert( str& s ) {
	if ( s == "A" ) {
		s = "10";
	} else if ( s == "B" ) {
		s = "11";
	} else if ( s == "C" ) {
		s = "12";
	} else if ( s == "D" ) {
		s = "13";
	} else if ( s == "E" ) {
		s = "14";
	} else if ( s == "F" ) {
		s = "15";
	}
}
