// This class holds an integer array of any size, and detects illegal subscripts.
// This version forbids copy and assignment, and so is safe,
// but you can't use it like a built-in variable.

#include <iostream>
#include <cstdlib>
using namespace std;

// version 2 - safe for actual use, but limited
class Array {
public:
    // constructor - argument is desired size of the array
    // constructor allocates memory for the array
    Array(int size_) : size(size_) {
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
    // C++11 style for forbidding copy and assignment
    Array(const Array& source) = delete;
    Array& operator= (const Array& source) = delete;
    
private:
    // C++98 (or C++03) style for forbidding copy and assignment
    //  Array(const Array& source); // forbid use of copy constructor
    //  Array& operator= (const Array& source); // forbid use of assignment operator
    int size;
    int* ptr;
};

void printem(const Array& a); // copy ctor not called, read-only
double averagem(Array a); // copy ctor called
void zeroem(Array& a);  // copy ctor not called
Array squarem(const Array& a);

// demonstrate use of Array Class, version 2
int main()
{
    //  Array x;    // error - no default constructor
    
    Array a(5);
    for (int i = 0; i < 5; i++)
        a[i] = i;   // 0, 1, 2, 3, 4
    
    // demonstrate call by const reference
    cout << "\nContents of a in main:" << endl;
    printem(a);
    
    /*  // demonstrate initialization from copy ctor
     // error - call to deleted constructor (C++11) / illegal access to private member (C++ 98)
     Array b(a);
     cout << "Contents of b after Array b(a);" << endl;
     printem(b);
     */
    /*  // demonstrate call by value
     cout << "\nAbout to call averagem(a)" << endl;
     // error - call to deleted constructor (C++11) / illegal access to private member (C++ 98)
     double avg = averagem(a);
     cout << "Average is " << avg << endl;
     cout << "Contents of a after double avg = averagem(a);" << endl;
     printem(a);
     */
    // demonstrate modification through call by reference
    cout << "\nAbout to call zeroem(a);" << endl;
    zeroem(a);
    cout << "Contents of a after zeroem(a);" << endl;
    printem(a);
    
    Array x(5);
    /*  // demonstrate assignment
     cout << "\nAbout to execute x = a;" << endl;
     // error - call to deleted operator= (C++11) / illegal access to private member (C++ 98)
     x = a;
     cout << "Contents of a after a = b;" << endl;
     printem(a);
     */
    /*  // demonstrate return value assignment
     cout << "\nAbout to execute a = squarem(b);" << endl;
     // error - call to deleted operator= (C++11) / illegal access to private member (C++ 98)
     x = squarem(a);    // error - illegal access to private member
     cout << "Contents of a after a = squarem(b);" << endl;
     printem(a);
     */
    cout << "\nDone!" << endl;
    
}


void printem(const Array& a) // copy ctor not called
{
    for (int i = 0; i < a.get_size(); i++)
        cout << '[' << i << "]:" << a[i] << endl;;
}

double averagem(Array a) // copy ctor called in client code
{
    double sum = 0;
    
    for (int i = 0; i < a.get_size(); i++) {
        sum += a[i];
        a[i] = 0;   // demo only
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


/*
 // return a new smart array object
 Array squarem(const Array& a)
 {
 Array b(a.get_size());
 
 for (int i = 0; i < a.get_size(); i++)
 b[i] = a[i] * a[i];
 // error - call to deleted constructor (C++11) / illegal access to private member (C++ 98)
 return b;  // error - illegal access to private member
 }
 */