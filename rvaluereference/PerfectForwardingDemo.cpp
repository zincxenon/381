/* starting with example from http://stackoverflow.com/questions/4327474/does-perfect-forwarding-in-c0x-make-reference-wrapper-deprecated?lq=1
*/
#include <iostream>
#include <functional>

using namespace std;

/* Suppose we want to write a function template that has two type parameters:
The type of a function (F)
The type of a parameter (P) to be supplied to the function.

The "forwarding problem" is that we can't write a function template that can
pass (or "forward") the argument to the function in a way that will work correctly
no matter what the supplied function takes as a parameter, and no matter what 
type of argument is supplied. There was no solution to this problem in C++98,
so some powerful facilities like bind had to use some tricks, and 
still would not work for certain combinations of functions and arguments.

The addition of rvalue references in C++11 made it possible to solve the problem.

This file has a set of simple function templates, and a family of simple functions
that will be supplied to the template, and called with different argument types.
First will be illustrated what does and doesn't work for C++98 style templates,
then will be shown what can be done with a "perfect forwarding" template that 
always does the right thing.
*/

// These templates call a supplied function with a parameter
// specified in various ways.  In some cases, the code won't compile
// depending on the type of parameter used in the function. 
template<class F, class P>
void call_by_value(F f, P t)
	{ f(t); }

template<class F, class P>
void call_with_reference(F f, P& t)
	{ f(t); }

// additional overload for const types, needed for rvalues
template<class F, class P>
void call_with_reference(F f, const P& t)
	{ f(t); }


// the following forwards a parameter specified with an rvalue reference
// and will work where the above versions won't.
template<class F, class P>
void call_with_forward(F f, P&& t)
	{ f(forward<P>(t)); }

// These functions modify their parameter.
// If it takes the parameter by reference,
// we expect to see appropriate behavior!

void f_by_value(int r)
{
    cout << "f_by_value gets " << r << endl;
    r++;
}

void g_by_reference(int& r)
{
    cout << "g_by_reference gets " << r << endl;
    r++;
}
void h_by_const_reference(const int& r)
{
    cout << "h_by_const_reference gets " << r << endl;
    // r++;  // can't change it - its by const reference
}

// this function gives us an rvalue to play with
int f_returns_int()
{
    static int i = 0;
    i++;
    cout << "f_returns_int returning " << i << endl;
    return i;
}



int main()
{

    int i = 0;
    const int ci = 42;
	
	cout << "\n\nForwarding of lvalues" << endl;

    cout << "i is now " << i << endl;
    cout << "\nUse call_by_value" << endl;
    call_by_value(f_by_value, i);
    cout << "i is now " << i << endl;
    call_by_value(g_by_reference, i);
    cout << "i is now " << i << endl;
    call_by_value(h_by_const_reference, i);
    cout << "i is now " << i << endl;
     
    cout << "\nUse call_with_reference" << endl;
    call_with_reference(f_by_value, i);
    cout << "i is now " << i << endl;
    call_with_reference(g_by_reference, i);
    cout << "i is now " << i << endl;
    call_with_reference(h_by_const_reference, i);
    cout << "i is now " << i << endl;
     
    cout << "\nUse call_with_reference on const int" << endl;
    call_with_reference(f_by_value, ci);
    cout << "ci is now " << ci << endl;
// Below fails because you can't convert const int to int& in template instantiation
//  call_with_reference(g_by_reference, ci);
// Below fails even if const P& version of template is used
//  call_with_reference(g_by_reference, ci);  
//  cout << "ci is now " << ci << endl;
	// Below works because const promise is not broken
    call_with_reference(h_by_const_reference, ci);
    cout << "ci is now " << ci << endl;

    cout << "\nUse call_by_value with reference wrapper" << endl;
	// reference wrapper is a C++98 way to get a reference past the template instantiation
    call_by_value(f_by_value, ref(i));
    cout << "i is now " << i << endl;
    call_by_value(g_by_reference, ref(i));
    cout << "i is now " << i << endl;
    call_by_value(h_by_const_reference, ref(i));
    cout << "i is now " << i << endl;

    cout << "\nUse call_by_value with reference wrapper on const int" << endl;
    call_by_value(f_by_value, ref(ci)); 
    cout << "ci is now " << ci << endl;
	// Below fails because const mismatch (as above)
//  call_by_value(g_by_reference, ref(ci));
    cout << "ci is now " << ci << endl;
    call_by_value(h_by_const_reference, ref(ci));
    cout << "ci is now " << ci << endl;

    cout << "\nUse call_with_forward" << endl;
	// Template uses an rvalue reference parameter and forwards it
	// result is simple and elegant - 
    call_with_forward(f_by_value, i);
    cout << "i is now " << i << endl;
    call_with_forward(g_by_reference, i);
    cout << "i is now " << i << endl;
    call_with_forward(h_by_const_reference, i);
    cout << "i is now " << i << endl;

    cout << "\nUse call_with_forward on const int" << endl;
    call_with_forward(f_by_value, ci);
    cout << "ci is now " << ci << endl;
	// below fails due to const mismatch, which is what we want!
//  call_with_forward(g_by_reference, ci);
	cout << "ci is now " << ci << endl;
    call_with_forward(h_by_const_reference, ci);
    cout << "ci is now " << ci << endl;
    
    cout << "\n\nForwarding of rvalues" << endl;

    cout << "i is now " << i << endl;
    cout << "\nUse call_by_value" << endl;
    call_by_value(f_by_value, f_returns_int());
    call_by_value(g_by_reference, f_returns_int());
    call_by_value(h_by_const_reference, f_returns_int());

    cout << "\nUse call_with_reference" << endl;
	// only works with const & version of call_with_reference
    call_with_reference(f_by_value, f_returns_int());
	// fails here because can't pass an rvalue by &
//  call_with_reference(g_by_reference, f_returns_int());
	// only works with const & version of call_with_reference
    call_with_reference(h_by_const_reference, f_returns_int());
    
    cout << "\nUse call_with_forward" << endl;
    call_with_forward(f_by_value, f_returns_int());
	// Below is const mismatch - trying to modify rvalue
//  call_with_forward(g_by_reference, f_returns_int());
    call_with_forward(h_by_const_reference, f_returns_int());



    cout << "\n\nForwarding of literal ints" << endl;
    cout << "\nUse call_by_value" << endl;
    call_by_value(f_by_value, 6);
    call_by_value(g_by_reference, 6);
    call_by_value(h_by_const_reference, 6);

    cout << "\nuse call_with_reference" << endl;
	// These only work because const & version of call_with_reference is instantiated
    call_with_reference(f_by_value, 6);
	// Below fails - trying to modify literal
	// call_with_reference(g_by_reference, 6);
    call_with_reference(h_by_const_reference, 6);


    cout << "\nUse call_with_forward" << endl;
    call_with_forward(f_by_value, 6);
	// Below fails - trying to modify literal
	// call_with_forward(g_by_reference, 6);
    call_with_forward(h_by_const_reference, 6);
     
}
/* Output:
Forwarding of lvalues
i is now 0

Use call_by_value
f_by_value gets 0
i is now 0
g_by_reference gets 0
i is now 0
h_by_const_reference gets 0
i is now 0

Use call_with_reference
f_by_value gets 0
i is now 0
g_by_reference gets 0
i is now 1
h_by_const_reference gets 1
i is now 1

Use call_with_reference on const int
f_by_value gets 42
ci is now 42
h_by_const_reference gets 42
ci is now 42

Use call_by_value with reference wrapper
f_by_value gets 1
i is now 1
g_by_reference gets 1
i is now 2
h_by_const_reference gets 2
i is now 2

Use call_by_value with reference wrapper on const int
f_by_value gets 42
ci is now 42
ci is now 42
h_by_const_reference gets 42
ci is now 42

Use call_with_forward
f_by_value gets 2
i is now 2
g_by_reference gets 2
i is now 3
h_by_const_reference gets 3
i is now 3

Use call_with_forward on const int
f_by_value gets 42
ci is now 42
ci is now 42
h_by_const_reference gets 42
ci is now 42


Forwarding of rvalues
i is now 3

Use call_by_value
f_returns_int returning 1
f_by_value gets 1
f_returns_int returning 2
g_by_reference gets 2
f_returns_int returning 3
h_by_const_reference gets 3

Use call_with_reference
f_returns_int returning 4
f_by_value gets 4
f_returns_int returning 5
h_by_const_reference gets 5

Use call_with_forward
f_returns_int returning 6
f_by_value gets 6
f_returns_int returning 7
h_by_const_reference gets 7


Forwarding of literal ints

Use call_by_value
f_by_value gets 6
g_by_reference gets 6
h_by_const_reference gets 6

use call_with_reference
f_by_value gets 6
h_by_const_reference gets 6

Use call_with_forward
f_by_value gets 6
h_by_const_reference gets 6
*/

