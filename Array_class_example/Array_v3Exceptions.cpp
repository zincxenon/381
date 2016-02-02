// This class holds an integer array of any size, and detects illegal subscripts.
// subscript errors throw an exception instead of just halting


#include <iostream>
using namespace std;

// An exception object with a message and data value
class Array_Exception {
public:
	Array_Exception (int v, const char * msg) :
    value (v), msg_ptr(msg) {}
    
	int value;
	const char * msg_ptr;
};


// version 3 with exceptions - suitable for actual use, and good error handling
class Array {
public:
	// constructor - argument is desired size of the array
	// constructor allocates memory for the array
	Array(int size_) : size(size_) {
		ptr = new int[size];
		cout << "Array of size " << size << " constructed." << endl;  // demo only
		}

	// copy constructor - initialize this object from another one
	Array(const Array& original) : size(original.size) {
		ptr = new int[size];			// allocate new space of that size
		for (int i = 0; i < size; i++)	// copy the data over
			ptr[i] = original.ptr[i];
		cout << "Array of size " << size << " constructed from another one" << endl;  // demo only
		}
	
/*	// Traditional assignment operator overload - copy the data from rhs into lhs object
	// return a reference to this object to allow normal cascaded assignments
	Array& operator= (const Array& rhs) {
		// check that different objects are involved - do nothing if the same
		if (this != &rhs) {
			// deallocate this object's data - going to be replaced
			delete[] ptr;
			// allocate a new data array and copy rhs's data into it.
			// note: duplicated code can be placed in a private helper function
			size = rhs.size;				// copy the size over
			ptr = new int[size];			// allocate new space of that size
			for (int i = 0; i < size; i++)	// copy the data over
				ptr[i] = rhs.ptr[i];
			}
		cout << "Array of size " << size << " assigned from another one" << endl;  // demo only
		// return reference to this object as value of the assignment expression
		return *this;
		}
*/
		
	// copy-swap idiom assignment operator overload - copy the data from rhs into lhs object
	// return a reference to this object to allow cascaded assignments
	Array& operator= (const Array& rhs) {
		// create a temp copy of rhs (right-hand side)
		Array temp(rhs);
		// swap the guts of this object with the temp;
		swap(temp);
		// return reference to this object as value of the assignment expression
		cout << "Array of size " << size << " assigned from another one" << endl;
		return *this;
		// destructor deallocates memory of temp that used to belong to this object
		}	

	// swap the member variable values of this object with the other
    // could use std::swap function template here
	void swap(Array& other) {
		int t_size = size;
		size = other.size;
		other.size = t_size;
		int * t_ptr = ptr;
		ptr = other.ptr;
		other.ptr = t_ptr;
		}		
	
	
	// destructor is responsible for freeing memory when array object is deallocated
	~Array() {
		delete[] ptr;
		cout << "Array of size " << size << " destroyed." << endl;  // demo only
		}	
	
	// public access function for private data
	int get_size() const {return size;}

	// overload the subscripting operator for this class - const version
    // this will throw an error if the index is out of range (including size == 0 case)
	const int& operator[] (int index) const {
		if ( index < 0 || index > size - 1) {
			// throw a bad-subscript exception
			throw Array_Exception(index, "Index out of range");
        }
		return ptr[index];
    }
    
	// overload the subscripting operator for this class - nonconst version
    // this will throw an error if the index is out of range (including size == 0 case)
	int& operator[] (int index) {
		if ( index < 0 || index > size - 1) {
			// throw a bad-subscript exception
			throw Array_Exception(index, "Index out of range");
        }
		return ptr[index];
    }
    

private:
	int size;
	int* ptr;	
};

void get_range (const Array& a);
void print_range(const Array& a, int min, int max);

// demonstrate use of Array Class, version 3 with exceptions
int main()
{	

	Array a(5);
	for (int i = 0; i < 5; i++)
		a[i] = i;	// 0, 1, 2, 3, 4

    for (int count = 0; count < 3; count++) {
		
		// let's try getting and printing a range
		try {
			get_range(a);
        }
        
		catch (Array_Exception& x) {
            cout << x.msg_ptr << ' ' << x.value << endl;
        }
        
		cout << "Shall we try again?" << endl;
        
	}
	
	cout << "\nDone!" << endl;
	
}


void get_range (const Array& a)
{
	int min, max;
	cout << "Enter min, max range:";
	cin >> min >> max;
	print_range(a, min, max);
}


void print_range(const Array& a, int min, int max)
{
	for (int i = min; i <= max; i++)
		cout << '[' << i << "]:" << a[i] << endl;;
}

/* OUTPUT
 Array of size 5 constructed.
 Enter min, max range:2 4
 [2]:2
 [3]:3
 [4]:4
 Shall we try again?
 Enter min, max range:2 8
 [2]:2
 [3]:3
 [4]:4
 [5]:Index out of range 5
 Shall we try again?
 Enter min, max range:-1 +1
 [-1]:Index out of range -1
 Shall we try again?
 
 Done!
 Array of size 5 destroyed.
 */

/* OUTPUT IF TRY-CATCH IS COMMENTED OUT
 Array of size 5 constructed.
 Enter min, max range:2 4
 [2]:2
 [3]:3
 [4]:4
 Shall we try again?
 Enter min, max range:2 8
 [2]:2
 [3]:3
 [4]:4
 */

