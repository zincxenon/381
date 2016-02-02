/*
Demo showing how reverse iterators allow you to move through a container in reverse order
using the same code structure (or template code) as would be used to go in normal order.
*/

#include <iostream>
#include <vector>

using namespace std;

// a function template for printing the contents of a container given by two iterators
template <typename Iter>
void printit(Iter start, Iter stop)
{
	for(Iter it = start; it != stop; ++it)
		cout << *it << ' ';
	cout << endl;
}


int main()
{
	vector<int> v;
	v.push_back(1); v.push_back(2); v.push_back(3); v.push_back(4); v.push_back(5);
	
	// explicit forward iterators
	for(vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		cout << *it << ' ';
	cout << endl;

	// explicit reverse iterators
	for(vector<int>::reverse_iterator rit = v.rbegin(); rit != v.rend(); ++rit)
		cout << *rit << ' ';
	cout << endl;
	
	// invoke a template with either kind
	printit(v.begin(), v.end());
	printit(v.rbegin(), v.rend());

}

/* output:
1 2 3 4 5
5 4 3 2 1
1 2 3 4 5
5 4 3 2 1
*/
