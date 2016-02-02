#include <iostream>
#include <set>

using namespace std;

int main()
{
	set<int> int_set;
	
	cout << "input integers, enter an alphabetic when done" << endl;
	
	int i;
	int count = 0;
	while(cin >> i) {
		int_set.insert(i);
		count++;
		}
	cin.clear(); 	// just to be neat

	cout << count << " ints were entered" <<  endl;
	
	cout << int_set.size() << " different numbers were present, as follows:" << endl;
	
	for(set<int>::iterator it = int_set.begin(); it != int_set.end(); ++it)
		cout << *it << endl;
		
	cout << "Done" << endl;
}