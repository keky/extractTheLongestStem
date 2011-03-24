#include<map>
#include<vector>
#include<iterator>
#include<string>
#include<fstream>
#include<iostream>
#include<algorithm>
#include "string_op.h"
using namespace std;

int main()
{
//	vector<int> h;
//	for( int i = 0; i < 10; i++ )
//		h.push_back( i );
//	vector<int>::iterator pos = h.begin();
//	h.erase( pos + 1, pos + 9 );
//	cout << h.size() << endl;
//	for( int i = 0; i < h.size(); i++ )
//		cout << h[i] << endl;
	string str = "))))))))..).....";
	cout << str << endl;
	get_rid_of_dot_suffix( &str );
	cout << str << endl;
	return 0;
}

