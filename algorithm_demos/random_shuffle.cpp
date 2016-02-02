#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;


int main()
{
	while(true) {
		cout << "Enter numbers for size, number of shuffles, non-numbers to quit: ";
		int n_size, n_shuffles;
		cin >> n_size >> n_shuffles;
		if(cin.fail())
			return 0;
		
		vector<int> v(n_size);
	
		for(int i = 0; i < n_size; i++)
			v[i] = i + 1;
			
		// shuffle and output
		for(int i = 0; i < n_shuffles; i++) {
			random_shuffle(v.begin(), v.end());
			copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
			cout << endl;
			}
		
	}
}

/* Example output
Enter numbers for size, number of shuffles, non-numbers to quit: 10 5
8 4 2 10 6 3 7 1 9 5 
7 10 3 4 8 6 2 9 1 5 
9 3 7 6 8 4 1 2 10 5 
1 9 4 5 7 8 3 6 10 2 
10 6 9 5 4 2 1 8 3 7 
Enter numbers for size, number of shuffles, non-numbers to quit: 20 10
15 8 12 19 20 17 3 16 6 5 1 7 4 11 14 9 18 2 13 10 
17 9 16 3 12 4 14 11 8 10 5 15 13 6 18 2 20 19 1 7 
19 2 11 13 17 20 6 1 5 8 15 14 10 3 9 18 16 7 4 12 
12 20 11 3 2 14 1 17 7 8 16 13 4 5 18 10 19 9 6 15 
14 15 8 16 4 19 6 18 5 17 11 7 3 10 12 20 9 2 1 13 
18 6 4 10 5 13 14 2 9 12 1 19 15 3 20 16 7 8 11 17 
7 18 16 15 12 1 9 4 3 6 19 10 5 11 2 13 8 14 20 17 
5 15 17 20 7 12 19 13 2 9 8 4 3 16 11 14 6 10 18 1 
20 19 3 14 6 16 2 7 10 8 15 1 5 4 17 11 13 12 9 18 
10 17 9 7 19 2 14 15 11 3 4 8 13 1 12 18 16 5 20 6 
Enter numbers for size, number of shuffles, non-numbers to quit: x x
*/
