/* Demo showing use of lower_bound and binary_search on an ordered sequence container.

binary_search just gives a bool result of whether the probe is in the container.

lower_bound returns an iterator pointing to the first item that is not less-than the probe;
it the probe value is in the container, the iterator will be pointing to the first item == probe;
if the probe is greater than all items in the container, the returned iterator will be == end();

The returned iterator can be used directly to insert a new item in the container, 
but it is ambiguous whether the item is already present in the container. You disambiguate
by checking first for end(), then checking the value at the iterator.
Note that if the iterator == end(), dereferencing it is undefined!
So:
The probe item IS NOT present if 
	iterator == end() || *iterator != probe value.
	(note that *iterator is evaluated only if iterator == end() is false)
Alternatively, the probe value IS present if
	iterator != end() && *iterator == the probe value.
	(note that *iterator is evaluated only if iterator != end() is true)

*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// print an int followed by a space
void printit(int t)
{ 
	cout << t << ' ';
}

// print out the contents of the vector
void printem(const vector<int>& v)
{
	for_each(v.begin(), v.end(), printit);
	cout << endl;
}

// use lower bound to find where to insert an int into the vector in order 
void  insertit(vector<int>& v, int i)
{
	vector<int>::iterator it = lower_bound(v.begin(), v.end(), i);
	v.insert(it, i);	// insert at the iterator
}
	

int main()
{

	vector<int> v;
	
	// insert 3, 7, and 4 into the vector so that they are in order by value
	insertit(v, 3);
	printem(v);
	insertit(v, 7);
	printem(v);
	insertit(v, 4);
	printem(v);
	
	
	int probe;

	// find  out whether a value is present using binary search
	cout << "Enter an int value to binary_search, non-numeric character to stop:";
	while (cin >> probe) {
		if(binary_search(v.begin(), v.end(), probe))
			cout << probe << " is present" << endl;
		else
			cout << probe << " is not present" << endl;
		cout << "Enter next value:";
		}
	
	cin.clear();			// reset error state
	while(cin.get() != '\n');	// flush rest of line

	// find  out whether a value is present using lower_bound
	cout << "Enter an int value to lower_bound search, non-numeric character to stop:";
	while (cin >> probe) {
		vector<int>::iterator it = lower_bound(v.begin(), v.end(), probe);
		// iterator points to the item if present, where to put it if not present
		// is the pointed to item not at end() and equal to the probe? If so, that value is already there
		if(it != v.end() && *it == probe)
			cout << probe << " is present" << endl;
		else {		
			cout << probe << " is not present - do you want to put it in?\nType 'y' to put it in, anything else if not:";
			char c;
			cin >> c;
			if(c == 'y') {
				// put it in at the right place
				v.insert(it, probe);
				cout << "Contents updated:" << endl;
				printem(v);
				}
			}
		cout << "Enter next value:";
		}
	
	cout << "Done" << endl;
}

/* sample output
3 
3 7 
3 4 7 
Enter an int value to binary_search, non-numeric character to stop:3
3 is present
Enter next value:5
5 is not present
Enter next value:x
Enter an int value to lower_bound search, non-numeric character to stop:4
4 is present
Enter next value:8
8 is not present - do you want to put it in?
Type 'y' to put it in, anything else if not:y
Contents updated:
3 4 7 8 
Enter next value:5
5 is not present - do you want to put it in?
Type 'y' to put it in, anything else if not:n
Enter next value:1
1 is not present - do you want to put it in?
Type 'y' to put it in, anything else if not:y
Contents updated:
1 3 4 7 8 
Enter next value:x
Done
*/