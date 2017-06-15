//simulate_maf.cpp
//31 July 2015 - Adam D Scott - 
 
#include <iostream> //cin, cout, cerr, clog
#include <cstdio> //read\write formatted output
#include <fstream> //ifstream, ofstream, fstream
#include <cstdlib> //rand, string conversion
#include <sstream> //stringstream
#include <string> //string, C++11: stoi, stod, to_string
#include <vector> //vector, 
#include <map> //map, multimap
#include <cmath> //trig, hyperbolics, exp, log
#include "time.h" //time

#define N_HUMAN_CHROMOSOMES 24
#define X_CHROMOSOME 23
#define Y_CHROMOSOME 24
#define N_BASES 4

typedef std::string str;
typedef std::map<str,int> hash;

void help ();
void ending ();
int str2int ( const str& );
str int2str ( const int& );

str tab = "\t";
str missense = "Missense_Mutation";

int main( int argc , char** argv ) {
	if ( argc > 1 ) {
		srand( time( NULL ) );

		int argi = 1;
		str in_filename = argv[argi++];
		str out_filename = argv[argi++];
		str wantgene = argv[argi++];
		int n_rand_lines = str2int( argv[argi++] );
		str trans_header = "transcript_name";
		str hgvsp_header = "amino_acid_change";
		if ( argc >= 6 ) {
			trans_header = argv[argi++];
			if ( argc == 7 ) {
				hgvsp_header = argv[argi++];
			}
		}
	 
		std::ifstream input( in_filename.c_str() );
		std::ofstream output( out_filename.c_str() );
	 
		str gene , transcript , length; 
		hash GTL;
		while( input >> gene >> transcript >> length ) {
			if ( wantgene.compare( gene ) == 0 ) {
				GTL[transcript] = str2int( length );
			}
		}

		int longest = 1;
		str longestT = "";
		for ( hash::iterator it = GTL.begin(); it != GTL.end(); ++it ) {
			if ( it->second > longest ) {
				longest = it->second;
				longestT = it->first;
			}
			//std::cout << it->first << " => " << it->second << std::endl;
		}
		std::cout << longestT << " => " << longest << std::endl;

		std::vector<str> chromosomes;
		std::vector<str> BASES (N_BASES,"A");
		BASES[1] = "C";
		BASES[2] = "G";
		BASES[3] = "T";
		for ( int chr = 1 ; chr <= N_HUMAN_CHROMOSOMES ; chr++ ) {
			if ( chr == X_CHROMOSOME ) { chromosomes.push_back( "X" );
			} else if ( chr == Y_CHROMOSOME ) { chromosomes.push_back( "Y" );
			} else { chromosomes.push_back( int2str( chr ) );
			}
		}
		int HEAD_FIELDS = 11;
		std::vector<str> header ( HEAD_FIELDS , "Hugo_Symbol" );
		header[1] = "Chromosome";
		header[2] = "Start_Position";
		header[3] = "End_Position";
		header[4] = "Reference_Allele";
		header[5] = "Tumor_Seq_Allele1";
		header[6] = "Tumor_Seq_Allele2";
		header[7] = "Tumor_Sample_Barcode";
		header[8] = "Variant_Classification";
		header[9] = trans_header;
		header[10] = hgvsp_header;
		for ( int i = 0 ; i < header.size() ; i++ ) {
			output << header[i];
			if ( i < HEAD_FIELDS-1 ) { output << tab;
			} else { output << std::endl;
			}
		}
		int randchr , randstart , randstop , randref , randvar;
		int randbarcode , randres;
		//std::cout << chromosomes.size() << tab << BASES.size() << std::endl;
		for ( int i = 0 ; i < n_rand_lines ; i++ ) {
			randchr = rand() % N_HUMAN_CHROMOSOMES;
			randstart = rand();
			randstop = randstart;
			randref = rand() % N_BASES;
			randvar = ( randref + 1 ) % N_BASES;
			randbarcode = rand();
			randres = rand() % longest + 1;
			//std::cout << randchr << tab << randstart << tab << randstop << tab << randref << tab << randvar << tab << randbarcode << tab << randres << std::endl;
			output << wantgene << tab << chromosomes[randchr] << tab;
			output << randstart << tab << randstop << tab;
			output << BASES[randref] << tab << BASES[randvar] << tab;
			output << BASES[randvar] << tab << randbarcode << tab;
			output << missense << tab << longestT << tab;
			output << "p.K" << randres << "F";
			output << std::endl;
		}

	} else { //print usage help
		help();
	}
		
	return 0;
}

void help() {
	ending();
	std::cout << "Usage: simulate_maf <.gtl> <output> \"gene\" #n mutations# ";
	std::cout << "(\"transcript header\") (\"HGVSp_short header\")";
	ending(); ending();
	std::cout << "Default headers are from WUSTL annotator. ";
	ending();
	std::cout << tab << "transcript header = \"transcript_name\", ";
	ending();
	std::cout << tab << "HGVSp_short header = \"amino_acid_change\", ";
	ending(); ending();
	std::cout << "The <.gtl> is a tsv format file with ";
	ending();
	std::cout << tab << "the first column as a gene, ";
	ending();
	std::cout << tab << "second is a transcript ID, and ";
	ending();
	std::cout << tab << "the final column is length of transcript. ";
	ending(); ending();
}
void ending() {
	std::cout << std::endl;
}

int str2int ( const str& s ) {
	return atoi( s.c_str() );
}

str int2str ( const int& ent ) {
	std::stringstream ss;
	ss << ent;
	str s = ss.str();

	return s;
}
