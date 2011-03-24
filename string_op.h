#ifndef STRING_OP_H
#define STRING_OP_H

#include<string>
#include<iostream>
using namespace std;

void get_rid_of_dot_suffix( string * );
void get_rid_of_dot_suffix( string * str_pt )
{
	//etc: ))))))))..)..).............
	//                   ------------- [this area should be remove]
	string str = * str_pt;	
	int last_index = str.find_last_of( ')' );
	* str_pt = str.substr( 0, last_index + 1 );
}

#endif
