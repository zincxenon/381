#include <iostream>

using namespace std;


// in clang and gcc 4.7, commenting this out sufficed to eliminate 3-way ambiguity noted below.

/*
void foo(int i)
{
    cout << "foo with call by value " << i << endl;
    i++;
    cout << "i is now " << i << endl;
}
*/

/*
void foo(int& i)
{
    cout << "foo with call by reference " << i << endl;
    i++;
    cout << "i is now " << i << endl;
}
*/

void foo(const int& i)
{
    cout << "foo with call by reference to const " << i << endl;
 //   i++;
    cout << "i is now " << i << endl;
}


void foo(int&& i)
{
    cout << "foo with call by rvalue reference " << i << endl;
    i++;
    cout << "i is now " << i << endl;
}


int return_an_int()
{
    static int i = 10;
    i++;
    return i;
}

int main()
{
    int int1 = 6;
/*
// fails to compile under clang and gcc 4.7 if foo(int i); is available due to ambiguous calls.
    foo(42);    // ambiguous - (int i), (const int& i), (int&& i)
    // paranoid: cout << "42 is now " << 42 << endl;
    foo(int1);  // ambiguous - (int i), (int& i), (const int& i)
    cout << "int1 is now " << int1 << endl;
    foo(static_cast<int&&>(int1));
    cout << "int1 is now " << int1 << endl;
    foo(return_an_int());   // ambiguous (int i), (const int& i), (int&& i)
*/

/*
// fails to compile if foo(int i); and foo(int&& i) is available due to ambiguous calls.
    foo(42);    // ambiguous - (int i), (int&& i)
    // paranoid: cout << "42 is now " << 42 << endl;
    foo(int1);  // ambiguous - (int i), (const int& i)
    cout << "int1 is now " << int1 << endl;
    foo(static_cast<int&&>(int1));
    cout << "int1 is now " << int1 << endl;
    foo(return_an_int());   // ambiguous (int i), (int&& i)
*/
/*
// fails to compile if foo(int i); foo(const& i) and foo(int&& i) is available due to ambiguous calls.
    foo(42);    // ambiguous - (int i), (const& i), (int&& i)
    // paranoid: cout << "42 is now " << 42 << endl;
    foo(int1);  // ambiguous - (int i), (const int& i)
    cout << "int1 is now " << int1 << endl;
    foo(static_cast<int&&>(int1)); // ambiguous - (int i), (const& i), (int&& i)
    cout << "int1 is now " << int1 << endl;
    foo(return_an_int());   // ambiguous int i), (const& i), (int&& i)
*/

// following compiles if only (const int& i), (int&& i) are defined
    foo(42); 
    // paranoid: cout << "42 is now " << 42 << endl;
    foo(int1);
    cout << "int1 is now " << int1 << endl;
    foo(static_cast<int&&>(int1));
    cout << "int1 is now " << int1 << endl;
    foo(return_an_int());

}
/* behavior is the same for clang and gcc 4.7
if foo(int i) is commented out, and foo(int&& i) is also commented out, then:
    foo(42);   calls foo(const int& i)
    foo(int1); calls foo(int& i)
    foo(return_an_int()); calls foo(int const& i)
    
if foo(int&& i) is present, then:
    foo(42);   calls foo(int&& i) // local i is incremented
    foo(int1); calls foo(int& i)
    foo(return_an_int()); calls foo(int&& i)

*/

