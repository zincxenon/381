// This class holds an integer array of any size,
// detects illegal subscripts and throws an exception,
// and implements the rule of 5 by providing copy construction,
// copy assignment, move construction, and move assignment.
// These functions output messages to demonstrate their operation;
// such messages would not usually be included in real classes for
// performance reasons.
// Each object holds a serial number which is output in the messages to
// make it easier to track construction, destruction, copy, and move operations.
// Operator+ is overloaded to sum two Array objects of the same size.

#include <iostream>
using namespace std;

class Array_Exception {
public:
    Array_Exception (int v, const char * msg) :
        value (v), msg_ptr(msg) {}

    int value;
    const char * msg_ptr;
};

class Array {
public:
    // default constructor creates an empty smart array.
    Array() : size(0), ptr(nullptr), serial_number(++counter) {
        cout << "Array " << serial_number << " default constructed" << endl;
        }
    
    // one-argument constructor - argument is desired size of the array
    // constructor allocates memory for the array
    Array(int size_) : size(size_), serial_number(++counter) {
        if(size <= 0)
            throw Array_Exception(size, "size must be greater than 0");
        ptr = new int[size];
        cout << "Array " << serial_number << " constructed" << endl;
        }

    // copy constructor - initialize this object from another one
    Array(const Array& original) : size(original.size), ptr(new int[size]), serial_number(++counter) {
        for (int i = 0; i < size; i++)
            ptr[i] = original.ptr[i];
        cout << "Array " << serial_number << " constructed from " << original.serial_number << endl;
        }
    
    // move constructor - take the guts from the original and leave it in a safely destructable state
    Array(Array&& original) : size(original.size), ptr(original.ptr), serial_number(++counter) {
        original.size = 0;
        original.ptr = nullptr;
        cout << "Array " << serial_number << " move constructed from " << original.serial_number << endl;
        }
    
    // copy the data from rhs into lhs object using copy-swap
    Array& operator= (const Array& rhs) {
        Array temp(rhs);
        swap(temp);
        cout << "Array " << serial_number << " assigned from " << rhs.serial_number << endl;
        return *this;
        }
    
    // move assignment just swaps rhs with this.
    Array& operator= (Array&& rhs) {
        swap(rhs);
        cout << "Array " << serial_number << " move assigned from " << rhs.serial_number << endl; 
        return *this;
        }

    // swap the member variable values of this object with the other (serial_numbers are NOT swapped)
    void swap(Array& other) {
        int t_size = size;  // could use std::swap
        size = other.size;
        other.size = t_size;
        int * t_ptr = ptr;
        ptr = other.ptr;
        other.ptr = t_ptr;
        }       
        
    ~Array() {
        delete[] ptr; 
        cout << "Array " << serial_number << " destroyed" << endl;
        }   
    
    int get_size() const {return size;}
    
    // overloaded plus operator returns an Array containing the sum of the two
    Array operator+ (const Array& rhs) { // "this" object is lhs
        // must have the same size
        if(size != rhs.get_size())
            throw Array_Exception(size, "LHS and RHS must have the same size for +");
        Array result(size);
        for(int i = 0; i < size; i++)
            result[i] = ptr[i]+rhs[i];
        return result;
        }

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
    int serial_number;
    static int counter; 
};

int Array::counter = 0;

void print(const char * msg, const Array& a);
Array reverse_contents(Array a); // call and return by value
Array increment_cells(Array a); // call and return by value

// demonstrate use of Array Class
int main()
{   
    cout << "Initialize a" << endl;
    Array a(5);
    for (int i = 0; i < 5; i++)
        a[i] = i;   // 0, 1, 2, 3, 4
    print("a has", a);
        
    try {
        cout << "\nCopy construct" << endl;
        Array b(a);
        print("b has copy of a", b);
        
        cout << "\nDefault construct and assign from another Array" << endl;
        Array c;
        print("c has", c);
        c = a;
        print("c has copy of a", c);

        cout << "\nConstruct from rvalue expression" << endl;
        Array d(a + c);
        print("d has copy of a + c", d);

        cout << "\nDefault construct and assign from rvalue expression" << endl;
        Array e;
        print("e has", e);
        e = a + c;
        print("e has sum of a + c", e);

        cout << "\nConstruct from function return value" << endl;
        Array f(reverse_contents(a));
        print("f has returned reverse of a", f);

        cout << "\nCall by value and assign from returned value:" << endl;
        print("e has", e);
        b = reverse_contents(e);
        print("b has reversed copy of e", b);
            
        cout << "\nAssign from function which returns its parameter variable" << endl;
        f = increment_cells(a);
        print("f has returned increment of a", e);
        
        cout << "\nDone with demo" << endl;
       }
            
    catch (Array_Exception& x) {
        cout << x.msg_ptr << ' ' << x.value << endl;
        }
            
    cout << "\nReturning from main" << endl;
    return 0;
}

void print(const char * msg, const Array& a)
{
    cout << msg << ": ";
    for(int i= 0; i < a.get_size(); i++)
        cout << a[i] << ' ';
    cout << endl;
}

// call and return by value
Array reverse_contents(Array a)
{
    int n = a.get_size();
    Array result(n);
    
    for(int i = 0; i < n; i++) {
        result[i] = a[n-i-1];
        }
    return result;
    
}

// return the same variable as the call by value parameter
// compiler cannot elide copy/move construction of returned
// value because parameter and result can't be in the same place!
Array increment_cells(Array a) // call and return by value
{
    int n = a.get_size();
    for(int i = 0; i < n; i++) {
        a[i] = a[i] + 1;
        }
    return a;
}


/*
 Output using gcc 4.7.0 with
 g++ -std=c++11 *.cpp -fno-elide-constructors
 
 Array 1 constructed
 Array 2 constructed
 Array 3 constructed
 
 call by value and assign from returned value:
 a has: 0 1 2 3 4
 Array 4 constructed from 1
 Array 5 constructed
 Array 6 move constructed from 5
 Array 5 destroyed
 Array 2 move assigned from 6
 Array 6 destroyed
 Array 4 destroyed
 b has reversed: 4 3 2 1 0
 
 assign from rvalue expression
 Array 7 constructed
 Array 8 move constructed from 7
 Array 7 destroyed
 Array 3 move assigned from 8
 Array 8 destroyed
 c has sum: 4 4 4 4 4
 
 construct from rvalue expression
 Array 9 constructed
 Array 10 move constructed from 9
 Array 9 destroyed
 Array 11 move constructed from 10
 Array 10 destroyed
 e has copy of a + c: 4 5 6 7 8
 
 construct from function return value
 Array 12 constructed from 1
 Array 13 constructed
 Array 14 move constructed from 13
 Array 13 destroyed
 Array 15 move constructed from 14
 Array 14 destroyed
 Array 12 destroyed
 d has returned reverse of a: 4 3 2 1 0
 Array 15 destroyed
 Array 11 destroyed
 
 Done!
 Array 3 destroyed
 Array 2 destroyed
 Array 1 destroyed
 
*/

/*
Output when constructor elision is allowed with:
 g++ -std=c++11 *.cpp
 Array 1 constructed
 Array 2 constructed
 Array 3 constructed
 
 call by value and assign from returned value:
 a has: 0 1 2 3 4
 Array 4 constructed from 1
 Array 5 constructed
 Array 2 move assigned from 5
 Array 5 destroyed
 Array 4 destroyed
 b has reversed: 4 3 2 1 0
 
 assign from rvalue expression
 Array 6 constructed
 Array 3 move assigned from 6
 Array 6 destroyed
 c has sum: 4 4 4 4 4
 
 construct from rvalue expression
 Array 7 constructed
 e has copy of a + c: 4 5 6 7 8
 
 construct from function return value
 Array 8 constructed from 1
 Array 9 constructed
 Array 8 destroyed
 d has returned reverse of a: 4 3 2 1 0
 Array 9 destroyed
 Array 7 destroyed
 
 Done!
 Array 3 destroyed
 Array 2 destroyed
 Array 1 destroyed
*/