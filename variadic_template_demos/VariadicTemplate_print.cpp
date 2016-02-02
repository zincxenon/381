/* Demonstrate a simple use of variadic templates to implement
a simple function accepts any number and and type of arguments, using
a "recursive" template instantiation. It is a type-safe implementation
of a printf-like function that outputs all of its arguments which can be
any number and type. 

Also shown is a simple wrapper that calls the
same function given any number and type of arguments.
*/

#include <iostream>
using namespace std;

// For a recursive operation, you need to specify the "last" thing to be done.

// an no-parameter "last" version of print in the "recursive" instantiation
void print()
{
	cout << endl;
}

// a parameter-taking "last" version which prints a '$' before its output
// to show when it gets called.
// if present, this one is called in preference to the no-parameter version
// so comment this one out to see the no-parameter version at work.
template <typename T>
void print(const T& arg)
{
    cout << '$' << arg << endl;
}


// the "recursive" version of print outputs the first argument
// then "calls" itself to print the rest of the parameter pack.
// it prints the size of the args list between < and > as part of the output
template <typename T, typename... Ts>
void print(const T& firstArg, const Ts&... args)
{
 //  cout << '<' << sizeof...(args) << '>' << firstArg;
    cout << firstArg << ' ';
    print(args...);
}

// a demonstration of a wrapper for a variadic template
// this simple passes the parameter pack on to the print template function.
template<typename... Args>
void zap(Args... args)
{
    print(args...);

}

int main()
{
    print(7.5, "hello", 42);
    zap("hello", 42, 7.5, "zap");
}

/* output with no-parameter version of "last" print:
7.5 hello 42
hello 42 7.5 zap
*/

/* output with no-parameter version of "last" print,
with the sizeof... output present in the "recursive" version
notice how the sizeof... is zero at the end

<2>7.5<1>hello<0>42
<3>hello<2>42<1>7.5<0>zap
*/


/* output with parameter version of "last" print,
with the sizeof... output present in the "recursive" version
showing '$' followed by last element:

<3>7.5<2>hello<1>42$
<4>hello<3>42<2>7.5<1>zap$
*/
