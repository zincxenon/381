#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;


int main()
{
	while(true) {
		cout << "Enter a number for size, non-number to stop: ";
		int n;
		cin >> n;
		if(cin.fail())
			return 0;
		
		vector<int> v(n);
	
		for(int i = 0; i < n; i++)
			v[i] = i + 1;
		
		// v is in sorted order; use sort alogorithm aotherwise
		// output each permutation, one per line
		do {
			copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
			cout << endl;
			}
		while(next_permutation(v.begin(), v.end()));
	}
}

/* Example output
Enter a number for size, non-number to stop: 3
1 2 3 
1 3 2 
2 1 3 
2 3 1 
3 1 2 
3 2 1 
Enter a number for size, non-number to stop: 5
1 2 3 4 5 
1 2 3 5 4 
1 2 4 3 5 
1 2 4 5 3 
1 2 5 3 4 
1 2 5 4 3 
1 3 2 4 5 
1 3 2 5 4 
1 3 4 2 5 
1 3 4 5 2 
1 3 5 2 4 
1 3 5 4 2 
1 4 2 3 5 
1 4 2 5 3 
1 4 3 2 5 
1 4 3 5 2 
1 4 5 2 3 
1 4 5 3 2 
1 5 2 3 4 
1 5 2 4 3 
1 5 3 2 4 
1 5 3 4 2 
1 5 4 2 3 
1 5 4 3 2 
2 1 3 4 5 
2 1 3 5 4 
2 1 4 3 5 
2 1 4 5 3 
2 1 5 3 4 
2 1 5 4 3 
2 3 1 4 5 
2 3 1 5 4 
2 3 4 1 5 
2 3 4 5 1 
2 3 5 1 4 
2 3 5 4 1 
2 4 1 3 5 
2 4 1 5 3 
2 4 3 1 5 
2 4 3 5 1 
2 4 5 1 3 
2 4 5 3 1 
2 5 1 3 4 
2 5 1 4 3 
2 5 3 1 4 
2 5 3 4 1 
2 5 4 1 3 
2 5 4 3 1 
3 1 2 4 5 
3 1 2 5 4 
3 1 4 2 5 
3 1 4 5 2 
3 1 5 2 4 
3 1 5 4 2 
3 2 1 4 5 
3 2 1 5 4 
3 2 4 1 5 
3 2 4 5 1 
3 2 5 1 4 
3 2 5 4 1 
3 4 1 2 5 
3 4 1 5 2 
3 4 2 1 5 
3 4 2 5 1 
3 4 5 1 2 
3 4 5 2 1 
3 5 1 2 4 
3 5 1 4 2 
3 5 2 1 4 
3 5 2 4 1 
3 5 4 1 2 
3 5 4 2 1 
4 1 2 3 5 
4 1 2 5 3 
4 1 3 2 5 
4 1 3 5 2 
4 1 5 2 3 
4 1 5 3 2 
4 2 1 3 5 
4 2 1 5 3 
4 2 3 1 5 
4 2 3 5 1 
4 2 5 1 3 
4 2 5 3 1 
4 3 1 2 5 
4 3 1 5 2 
4 3 2 1 5 
4 3 2 5 1 
4 3 5 1 2 
4 3 5 2 1 
4 5 1 2 3 
4 5 1 3 2 
4 5 2 1 3 
4 5 2 3 1 
4 5 3 1 2 
4 5 3 2 1 
5 1 2 3 4 
5 1 2 4 3 
5 1 3 2 4 
5 1 3 4 2 
5 1 4 2 3 
5 1 4 3 2 
5 2 1 3 4 
5 2 1 4 3 
5 2 3 1 4 
5 2 3 4 1 
5 2 4 1 3 
5 2 4 3 1 
5 3 1 2 4 
5 3 1 4 2 
5 3 2 1 4 
5 3 2 4 1 
5 3 4 1 2 
5 3 4 2 1 
5 4 1 2 3 
5 4 1 3 2 
5 4 2 1 3 
5 4 2 3 1 
5 4 3 1 2 
5 4 3 2 1 
Enter a number for size, non-number to stop: x
*/
