/* This demonstration shows how a member function of a class can use an algorithm
that calls another member function of the same class. The trick is that you have
to identify the other function as a member function, and specify that "this" pointer
is the first argument of this function.  Then the template instantiations will work.
*/

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>
#include <iomanip>

using namespace std;

typedef list<int> int_list_t;


// an ordinary function object that works with no problem.
struct Print_int_FO {
void operator() (int i)
	{
		cout << "Print_int_FO: " << i << endl;	
	}
};

// This function object's operator() uses an algorithm that uses
// both another function object, and also a member function of this same class.
class Lister {
public:
void operator() (int_list_t thelist) const
	{
		// use the sure-fire function object
		for_each(thelist.begin(), thelist.end(), Print_int_FO());
		// call a member function of this same class
		for_each(thelist.begin(), thelist.end(), bind1st(mem_fun(&Lister::print_int_mf), this));
	}

void print_int_mf(int i) const	// a member function of the same class
	{
		cout << "print_int_mf: " << i << endl;
	}

};


int main()
{
	// create a vector of lists of ints, fill with some values 
	// that make it easy to identify which comes from where
	vector<int_list_t> vl(3);
	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 4; ++j) {
			vl[i].push_back(i * 10 + j);
			}
	// output with explicit loops
	for(vector<int_list_t>::iterator vit = vl.begin(); vit != vl.end(); ++vit) {
		for(int_list_t::iterator lit = vit->begin(); lit != vit->end(); ++lit)
			cout << setw(3) << *lit;
		cout << endl;
		}

	// output with an algorithm that calls Lister's operator() on each list<int>
	for_each(vl.begin(), vl.end(), Lister());

}