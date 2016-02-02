/* A nano musical composer data base using a map container. The container holds pairs of strings
that consist of the name of a musical period (e.g. "Classical") and a composer of that period.
This example uses the insert member function to add pairs to the map - note the use of the 
make_pair function and the pair template directly.

Exercise: modify this so that multiple composers of the same period can be stored -
use a multimap. 
*/

#include <map>
#include <string>  
#include <iostream>
#include <algorithm>
using namespace std;

// declare the container using the string's less-than operator
typedef map<string, string, less<string> > items_t;

void print_item(const items_t::value_type& item);

int main(void)
{ 
	string a ("Baroque"), b ("Classical"), c ("Romantic");
	string aa ("Bach"), bb ("Mozart"), cc ("Chopin");

	items_t items;

	items.insert(make_pair(a, aa)); 
	items.insert(pair<const string, string>(c, cc));
	items.insert(make_pair(b, bb));

	for_each(items.begin(), items.end(), print_item);

	// test lookup function
	
	string probe_string;
	cout << "enter a period: " << endl;
	cin >> probe_string;
	// if the probe is there, the iterator points to the pair
	items_t::iterator it = items.find(probe_string);
	if (it == items.end())
		cout << "period not found" << endl;
	else
		print_item(*it); 	
	
	cout << "done" << endl;

}

void print_item(const items_t::value_type& item)
{
	cout << item.first << " had " << item.second << endl;
}


