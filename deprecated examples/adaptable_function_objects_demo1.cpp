#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

/* 
This example shows how one might go about defining function objects that integrate with 
the adapters used with the algorithms.
*/

// a function object class that simply compares two integers for equality
// inherit from std::binary_function which contains typedefs 
// that are required by adapters like bind2nd
struct Match_value : public binary_function<int, int, bool> {
	bool operator() (int x, int y) const // const required here for template instantiation
		{return x == y;}
};


int main()
{
	cout << "Enter a bunch of values, 0 when done:" << endl;	
	vector<int> data;
	int i;
	while(cin >> i && i != 0)
		data.push_back(i);
	
	int v;
	cout << "Enter a match value:";
	cin >> v;

	// use the match_value function object with the bind2nd adapter to pass in the match value
	// as the second parameter
	vector<int>::iterator it = find_if(data.begin(), data.end(), bind2nd(Match_value(), v));

	// use one of the predefined function object class templates that does the same thing
	// vector<int>::iterator it = find_if(data.begin(), data.end(), bind2nd(equal_to<int>(), v));
	
	if(it == data.end())
		cout << "not found" << endl;
	else
		cout << "found" << endl;
}

