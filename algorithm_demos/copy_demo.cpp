
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print(int i)
{
	cout << i << endl;
}

int main()
{
	vector<int> vi;
	int ai[10];
	
	for(int i = 0; i < 10; i++) {
		vi.push_back(10 * (i+1));
		ai[i] = i+1;
		}
	for_each(ai, ai+10, print);
	for_each(vi.begin(), vi.end(), print);
	
	// copy vi into ai - there is space for it
	copy(vi.begin(), vi.begin() + 4, ai);

	for_each(ai, ai+10, print);
	for_each(vi.begin(), vi.end(), print);

}

	