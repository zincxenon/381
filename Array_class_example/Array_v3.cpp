// This class holds an integer array of any size, and detects illegal subscripts.
// This version implements copy construction and copy assignment

#include <iostream>
#include <cstdlib> // for exit function
using namespace std;

// version 3 - suitable for actual use, but clunky error handling
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

void printem(const Array& a); // copy ctor not called, read-only
double averagem(Array a); // copy ctor called
void zeroem(Array& a);	// copy ctor not called
Array squarem(const Array& a);

// demonstrate use of Array Class, version 3
int main()
{	

	Array a(5);
	for (int i = 0; i < 5; i++)
		a[i] = i;	// 0, 1, 2, 3, 4

	// demonstrate call by const reference
	cout << "\nContents of a in main:" << endl;
	printem(a);

	// demonstrate initialization from copy ctor
	Array b(a);
	cout << "Contents of b after Array b(a);" << endl;
	printem(b);
				
	// demonstrate call by value
	cout << "\nAbout to call averagem(a)" << endl;
	double avg = averagem(a);
	cout << "Average is " << avg << endl;
	cout << "Contents of a after double avg = averagem(a);" << endl;
	printem(a);
	
	// demonstrate modification through call by reference
	cout << "\nAbout to call zeroem(a);" << endl;
	zeroem(a);
	cout << "Contents of a after zeroem(a);" << endl;
	printem(a);
	
	// demonstrate assignment
	cout << "\nAbout to execute a = b;" << endl;
	a = b;
	cout << "Contents of a after a = b;" << endl;
	printem(a);
	
	// demonstrate return value assignment
	cout << "\nAbout to execute a = squarem(b);" << endl;
	a = squarem(b);
	cout << "Contents of a after a = squarem(b);" << endl;
	printem(a);
	
	cout << "\nDone!" << endl;
	
}


void printem(const Array& a) // copy ctor not called
{
	for (int i = 0; i < a.get_size(); i++)
		cout << '[' << i << "]:" << a[i] << endl;;
}

double averagem(Array a) // copy ctor called
{
	double sum = 0;
	
	for (int i = 0; i < a.get_size(); i++) {
		sum += a[i];
		a[i] = 0;	// demo only
		}
	cout << "Contents of a in averagem:" << endl;
	printem(a);
	return sum/a.get_size();
}

void zeroem(Array& a)
{	
	for (int i = 0; i < a.get_size(); i++) 
		a[i] = 0;
}



// return a new smart array object
Array squarem(const Array& a)
{
	Array b(a.get_size());
	
	for (int i = 0; i < a.get_size(); i++)
		b[i] = a[i] * a[i];
		
	return b;
}

/*
Array of size 5 constructed.

Contents of a in main:
[0]:0
[1]:1
[2]:2
[3]:3
[4]:4
Array of size 5 constructed from another one
Contents of b after Array b(a);
[0]:0
[1]:1
[2]:2
[3]:3
[4]:4

About to call averagem(a)
Array of size 5 constructed from another one
Contents of a in averagem:
[0]:0
[1]:0
[2]:0
[3]:0
[4]:0
Array of size 5 destructed.
Average is 2
Contents of a after double avg = averagem(a);
[0]:0
[1]:1
[2]:2
[3]:3
[4]:4

About to call zeroem(a);
Contents of a after zeroem(a);
[0]:0
[1]:0
[2]:0
[3]:0
[4]:0

About to execute a = b;
Array of size 5 assigned from another one
Contents of a after a = b;
[0]:0
[1]:1
[2]:2
[3]:3
[4]:4

About to execute a = squarem(b);
Array of size 5 constructed.
Array of size 5 constructed from another one
Array of size 5 destructed.
Array of size 5 assigned from another one
Array of size 5 destructed.
Contents of a after a = squarem(b);
[0]:0
[1]:1
[2]:4
[3]:9
[4]:16

Done!
Array of size 5 destructed.
Array of size 5 destructed.

*/
