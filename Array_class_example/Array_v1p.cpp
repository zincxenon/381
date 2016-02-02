// This class holds an integer array of any size, and detects illegal subscripts.

// WARNING - ELEMENTARY EXAMPLE ONLY! THIS VERSION IS NOT SUITABLE FOR ACTUAL USE! 


#include <iostream>
#include <cstdlib>
using namespace std;

// version 1 - not suitable for actual use
class Array {
public:
	// constructor - argument is desired size of the array
	// constructor allocates memory for the array
	Array(int in_size) {
		size = in_size;
		ptr = new int[size];
		cout << "Array of size " << size << " constructed." << endl;  // demo only
		}

	// destructor is responsible for freeing memory when array object is deallocated
	~Array() {
		delete[] ptr;
		cout << "Array of size " << size << " destroyed." << endl;  // demo only
		}	
	
	// public access function for private data
	int get_size() const {return size;}

	// overload the subscripting operator for this class - const version
	const int& operator[] (int index) const {
		if ( index < 0 || index > size - 1) {
			// this is simple, but there are better actions possible
			cerr << "Attempt to access Array with illegal index = " << index << endl;
			cerr << "Terminating program" << endl;
			exit(EXIT_FAILURE);
			}
		return ptr[index];
		}

	// overload the subscripting operator for this class - nonconst version
	int& operator[] (int index) {
		if ( index < 0 || index > size - 1) {
			// this is simple, but there are better actions possible
			cerr << "Attempt to access Array with illegal index = " << index << endl;
			cerr << "Terminating program" << endl;
			exit(EXIT_FAILURE);
			}
		return ptr[index];
		}

private:
	int size;
	int* ptr;	
};

// demonstrate use of Array Class, version 1
int main()
{	

	cout << "Enter desired size:";
	int n;
	cin >> n;
	
	Array *  my_ints_ptr= new Array(n);
	
	cout << "Enter " << n << " values:" << endl;
	// size is available from the Array object
	for (int i = 0; i < my_ints_ptr->get_size(); i++) {
		cout << i << ':';
		int x;
		cin >> x;
		(*my_ints_ptr)[i] = x;	// use subscript operator on left hand size of assignment
		// cin >> my_ints[i]; 	// can also use as input operator variable
		}
		
	for (int i = 0; i < 5; i++) {
		cout << "Enter an index of number to see, 0 through " << n -1 << " is legal:";
		int index;
		cin >> index;
		int result = (*my_ints_ptr)[index]; // use subscript operator on right hand size of assignment
		cout << "Value at index " << index << " is " << result << endl;
	}	
	
	delete my_ints_ptr;
	cout << "Done!" << endl;
	
}

/*
Enter desired size:5
Array of size 5 constructed.
Enter 5 values:
0:0
1:10
2:20
3:30
4:40
Enter an index of number to see, 0 through 4 is legal:4
Value at index 4 is 40
Enter an index of number to see, 0 through 4 is legal:3
Value at index 3 is 30
Enter an index of number to see, 0 through 4 is legal:2
Value at index 2 is 20
Enter an index of number to see, 0 through 4 is legal:1
Value at index 1 is 10
Enter an index of number to see, 0 through 4 is legal:0
Value at index 0 is 0
Array of size 5 destructed.
Done!
*/

/*
Enter desired size:3
Array of size 3 constructed.
Enter 3 values:
0:0
1:10
2:20
Enter an index of number to see, 0 through 2 is legal:1
Value at index 1 is 10
Enter an index of number to see, 0 through 2 is legal:2
Value at index 2 is 20
Enter an index of number to see, 0 through 2 is legal:-5
Attempt to access Array with illegal index = -5
Terminating program
*/
