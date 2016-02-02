#include <set>
#include <string>  
#include <iostream>
#include <algorithm>
using namespace std;

/* A nano musical composer data base using a set container. The container holds items
that consist of the name of a musical period (e.g. "Classical") and a composer of that period.
Exercise: modify this so that multiple composers of the same period can be stored -
use a multiset. */

struct Item {
public:
	string period;
	string composer;
	Item ();
	Item (const string& in_period, const string& in_composer)
		: period(in_period), composer(in_composer)
		{}
};

// one of the ways to define a function object for a comparitor
// order the Items by period

struct less_Item
{
	bool operator() (const Item& x, const Item& y) const
	{ return  x.period < y.period;  }
};

typedef set<Item, less_Item> Items_t;

void print_item(const Items_t::value_type& item);

int main(void)
{
	Item a ("Baroque", "Bach"), b ("Classical", "Mozart"), c ("Romantic", "Chopin"),
		d("Modern", "Stravinsky"), e("Rock", "Lennon");
	
	// declare the set container to hold Items comparable with the less_Item function object
	Items_t items;
	
	items.insert(e);
	items.insert(a);
	items.insert(c);
	items.insert(b);
	items.insert(d);
	
	for_each(items.begin(), items.end(), print_item);
			
	// test lookup function
	
	string probe_string;
	cout << "enter a period: " << endl;
	cin >> probe_string;
	// construct a probe object that will compare equivalent to the desired object
	Item probe_item (probe_string, "");
	
	Items_t::iterator it = items.find(probe_item);
	if (it == items.end())
		cout << "period not found" << endl;
	else
		print_item(*it); 	
	
	cout << "done" << endl;

}

void print_item(const Items_t::value_type& item)
{
	cout << item.period << " had " << item.composer << endl;
}
