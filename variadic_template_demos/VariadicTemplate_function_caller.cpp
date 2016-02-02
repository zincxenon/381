/* Demonstrate a simple use of variadic templates to implement
a template function that calls whatever function matches 
the number and types of its arguments. This approach is used
in Standard Library functions like make_shared to call the 
constructor corresponding to the supplied arguments. 
*/

#include <iostream>
using namespace std;

// a set of overloaded functions
void f(int i)
{
    cout << "f(int) called with " << i << endl;
}

void f(int i, int j)
{
    cout << "f(int, int) called with " << i << ' ' << j << endl;
}

void f(int i, double d)
{
    cout << "f(int, double) called with " << i << ' ' << d << endl;
}

void f(int i, const string& s)
{
    cout << "f(int, string) called with " << i << ' ' << s << endl;
}

void f(int i, int j, double d, const string& s)
{
    cout << "f(int, int, double, string) called with "
        << i << ' ' << j << ' ' << d << ' ' << s << endl;
}

// a function template that calls the relevant function
// named "f" that accepts the supplied arguments as a parameter pack
template<typename... Args>
void callit(Args... args)
{
    cout << "\nin callit with parameter pack of size " << sizeof... (args) << endl;
    f(args...); // the version of f that matches the parameter pack
}

int main()
{
    callit(42);
    callit(1, 2);
    callit(1, 2.2); // int double is preferred overload
    callit(1, string("Hello"));
    callit(1, "Hello"); // string literal converts to string variable
    callit(1, 2, 3.14, "Goodbye");
//  callit(1, 2, 3); // compile fails because there is no matching function
//  callit(string("Hello")); // compile fails because there is no matching function
}

/* output:

in callit with parameter pack of size 1
f(int) called with 42

in callit with parameter pack of size 2
f(int, int) called with 1 2

in callit with parameter pack of size 2
f(int, double) called with 1 2.2

in callit with parameter pack of size 2
f(int, string) called with 1 Hello

in callit with parameter pack of size 2
f(int, string) called with 1 Hello

in callit with parameter pack of size 4
f(int, int, double, string) called with 1 2 3.14 Goodbye
*/
