//
//  FunctionTemplateFunctionParameters.cpp
//

#include <iostream>
using namespace std;


// this template takes a function and a parameter and does the call
// analogous to the function slot in for_each.
template <typename F, typename T>
void call_func(F f, T t)
{
    f(t);
}

// some function to use with the call_func template
void foo(int i)
{
    cout << "foo(int) called with " << i << endl;
}

void foo(double d)
{
    cout << "foo(double) called with " << d << endl;
}

void goo(int i)
{
    cout << "goo(int) called with " << i << endl;
}

void goo(int i, double d)
{
    cout << "goo(int, double) called with " << i << ' ' << d << endl;
}

// another function template - 
template <typename T>
void hoo(T t)
{
    cout << "hoo template called with " << t << endl;
}



int main()
{
    int i{42};
    double d{3.14};
	// following has compile error - can't resolve the overloaded function name
	// - ambiguous because there is more than one foo in scope
    // call_func(foo, i);

	// all of the following work
	// the casts tell the compiler what the type of foo is
	call_func(static_cast<void (*)(int)>(foo), i);
    call_func(static_cast<void (*)(double)>(foo), i);
    call_func(static_cast<void (*)(int)>(foo), d);
    call_func(static_cast<void (*)(double)>(foo), d);

	// we can tell the compiler what the template parameter type is
    call_func<void (*)(int)>(foo, i);
    
	// even though only one goo could be called here, compiler can't infer it
	// because there are two functions named "goo"
	// call_func(goo, i);
	// we can specify the type of F to use
    call_func<void (*)(int)>(goo, i);
    
    hoo(d);
	// hoo is the name of a template, but the compiler doesn't know its type
	// just from the name of the template, so this fails to compile:
    // call_func(hoo, d);
	
	// it works if specify the type of hoo by supplying its type parameter
    call_func(hoo<int>, i);
    
}
