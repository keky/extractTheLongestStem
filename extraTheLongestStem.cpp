#include <map>
#include <vector>
#include <iterator>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "string_op.h"

using namespace std;

	/* to save the origional position for every site */
typedef struct {
	int max_len; //the length of the stem
	int orig_posit_5; //the origional posit for prefix
	int orig_posit_3; //the origional posit for suffix
	string prefix;
	string suffix;
} rna_one;

int main( int argc, char ** argv )
{
	char * file_input = argv[1];
	if( argc < 2 ){
		cout << "Usage:" <<	argv[0] << " file" << endl;
		exit( -1 );
	}

	vector<int> real_posit;
	string seq_id; //the id of the rna sequence
	string seq; //sequence
	string seq_sec; //the secondary structure of the seq

	/*=========THE FILE FORMATE========
	 *1 >sequence_id
	 *2 sequence
	 *3 secondary struct 
	 * */
	ifstream fin( file_input );
	while( fin >> seq_id ){ //read from the file
		fin >> seq;	
		fin >> seq_sec;	
		
		cout << seq_id << endl;
		if( real_posit.size() > 0 )  //initial the vector
			real_posit.erase( real_posit.begin(), real_posit.end() );
		for( int i = 0; i < seq.length(); i ++ )	
			real_posit.push_back( i );
		rna_one stem = { 0, 0, 0, "", "" };

		/*extract all stem from the sequence*/
		while( seq_sec.find_first_of( ")" ) != string::npos )
		{ 
//			cout << "HERE" << endl;
//			cout << seq_sec << endl;
//			for( int i = 0; i < real_posit.size(); i++ )
//				cout << " " << real_posit[i];
//			cout << endl;
			int pos3_start = seq_sec.find_first_of( ")" );
			int pos5_end = seq_sec.find_last_of( "(", pos3_start );
			string substr_3_tmp = "";
			string substr_5_tmp = "";
			substr_3_tmp += seq_sec[pos3_start];
			substr_5_tmp += seq_sec[pos5_end];
			int j = pos5_end - 1;
			int flag;
			for( int i = pos3_start + 1; i < seq_sec.length(); i++ ){

				flag = 0; //indicate that if there is '(' existed
				if( seq_sec[i] == '(' ) //This stem is at the end
					break;
				else if( seq_sec[i] == '.' ) {
					substr_3_tmp += seq_sec[i];	
					continue;
				}
				else {
					while( j >= 0 && real_posit[j] == real_posit[j+1] - 1 ){ 
						// Search a '(' to consist the pair of ()
						if( seq_sec[j] == '(' ) { //They should be nearby at the origional seq
							substr_5_tmp = seq_sec[j] + substr_5_tmp;	
							substr_3_tmp += seq_sec[i];	
							flag = 1;
							j--;
							break;	
						}
						substr_5_tmp = seq_sec[j] + substr_5_tmp;	
						j--;
					}
					/* Do not find a pair of '()' */
					if( flag == 0 ) break;
				}
			}

			/* Ensure there were no unmatch charactors BEFORE | AFTER the stem*/
			get_rid_of_dot_suffix( &substr_3_tmp );

			int len_tmp = substr_3_tmp.length() > substr_5_tmp.length() ?
						  substr_3_tmp.length() : substr_5_tmp.length();
			/* Modify the max_len if the stem is longer */
			if( stem.max_len < len_tmp ){
				stem.max_len = len_tmp;
				stem.prefix = substr_5_tmp;
				stem.suffix = substr_3_tmp;
				stem.orig_posit_5 = real_posit[ pos5_end - substr_5_tmp.length() + 1 ]; 
				stem.orig_posit_3 = real_posit[ pos3_start ]; 
			}

			int pos_del_start = pos5_end - substr_5_tmp.length() + 1;
			int pos_del_end = pos3_start + substr_3_tmp.length() - 1;

			/* Delete the sub_seq from the origional sequence */ 
			vector<int>::iterator pos = real_posit.begin();
			real_posit.erase( pos + pos_del_start, pos + pos_del_end + 1 );
			seq = seq.substr( 0, pos_del_start ) + seq.substr( pos_del_end + 1 );
			seq_sec = seq_sec.substr( 0, pos_del_start ) + seq_sec.substr( pos_del_end + 1 );
		}
		cout << stem.max_len << endl;
		cout << stem.prefix << endl;
		cout << stem.suffix << endl;
		cout << stem.orig_posit_5 << endl;
		cout << stem.orig_posit_3 << endl;
	}
	return 0;
}
