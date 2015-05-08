//frac2hex2.cpp
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

str num2str( const double& );
double str2num( const str& );
str frac2hex2( const double& , str& );
 
int main( int argc , char** argv )
{
	str color;
	str original;
	std::vector<str> vals;
	int base = 256;

	for ( int i = 1; i < argc; i++ ) {
		original = argv[i];
		color = argv[i];
		color = frac2hex2( base , original );
		std::cout << color << " ";
		if ( ( i - 1 ) % 3 == 2 ) {
			std::cout << "\t";
		}
	}
	std::cout << std::endl;

	return 0;
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

str frac2hex2( const double& base , str& ent ) {
	str hex = "000";

	if ( str2num( ent ) != 0 ) {
		hex = num2str( int( ( base * str2num( ent ) ) - 1 ) );
	}

	return hex;
}
