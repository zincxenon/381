
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
		ai[i] = i+1;
		}
	for_each(ai, ai+10, print);
	
	// copy ai into vi, making space as needed
	copy(ai, ai + 10, back_inserter(vi));

	for_each(ai, ai+10, print);
	for_each(vi.begin(), vi.end(), print);

}

	