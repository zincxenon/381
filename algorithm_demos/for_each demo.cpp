// illustrate how algorithms apply to both containers and built-in arrays

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print(int i)
{
	cout << i << endl;
}

// algorithms use only template magic - here is a for_each implementation
template <typename Iter, typename Func>
Func my_for_each(Iter start, Iter stop, Func f)
{
	for(Iter it = start; it != stop; ++it)
		f(*it);
	return f;
}

int main()
{
	vector<int> vi;
	int ai[10];
	
	for(int i = 0; i < 10; i++) {
		vi.push_back(i+1);
		ai[i] = i+1;
		}

	for_each(vi.begin(), vi.end(), print);
	
	
	for_each(ai, ai+10, print);
	
	my_for_each(vi.begin(), vi.end(), print);
	
	
	my_for_each(ai, ai+10, print);
}

	