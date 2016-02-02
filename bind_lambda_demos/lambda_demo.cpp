#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <iterator> // for back_inserter
//#include <functional>

// using namespace std;
using std::cout; using std::endl; using std::cin;
using std::list;
using std::back_inserter; using std::ostream_iterator;
using std::ofstream;
using std::ostream;
using std::for_each;

void demo_basics();
void demo_returned_value();
void demo_capture();
void demo_with_algorithms();
void demo_member_variable_capture();


int main()
{
	demo_basics();
	demo_returned_value();
    demo_capture();
	demo_with_algorithms();
    demo_member_variable_capture();
	cout << "Done" << endl;
	return 0;
}

int gv = 1001; // a global variable

void demo_basics()
{
	cout << "\n\nLambda basics demo" << endl;

	int i = 42;
	int j = 6;
	
	// A lambda experession creates a function object whose type can be deduced with auto, and this can be called.
	// Required parts: the square bracket bit, a parameter list, a function body in curly braces.
    // It can be called like a function by appending the function call syntax after the lambda
    [] () {cout << "Hello from trivial lambda!" << endl;}();
    
    // A lambda expression is like a function pointer or function object; we can save it in a variable,
    // using "auto" to avoid having to figure out what the actual type is.
	auto func1 = [] () {cout << "Hello from trivial lambda!" << endl;};
	func1();	// call it
	
	// we can pass in parameters in the parameter list, just like with a regular function; these become the parameters
	// in the function call operator of the created function object.
    [] (int x) {cout << "This lambda got a parameter value of " << x << endl;}(42);
    
	auto func2 = [] (int x) {cout << "This lambda got a parameter value of " << x << endl;};
	func2(i);
	func2(12);
	
	// Now the special lambda part. The created function object can store information about the local context; this
	// information about the context can be "captured" in the square bracket, meaning that you can get information
	// into the function body without going through the parameter list.  For example, we can capture the value of i
	// and use it in the function body. A copy of this value is actually stored in the function object.
	auto func3 = [i] () {cout << "This lambda captures the value of i: " << i << endl;};
	func3();
	
	// You can use both capture and parameters.
	auto func4 = [i] (int x) {cout << "This lambda captured i of " << i << " and got a parameter of " << x << endl;};
	func4(13);
	
	// You can specify a capture by reference, which means the lambda can modify a variable in the context;
	// it does this by storing a reference in the function object.
	auto func5 = [&j] () {cout << "This lambda is modifying j by adding 5" << endl; j += 5;};
	cout << "j is " << j << endl;
	func5();
	cout << "j is " << j << endl;
	
	// You can capture more than one variable, with a mixture of by-value and by-reference.
	auto func6 = [i, &j] () {cout << "This lambda sets j to the value in i" << endl; j = i;};
	cout << "j is " << j << endl;
	func6();
	cout << "j is " << j << endl;
	
	// You can capture all of the current context by value - making everything currently in scope available.
	// This is done with [=] as the capture; you can also do [&] to capture everything by reference.
	auto func7 = [=] () {
		cout << "This lambda has a copy of everything! i is " << i << ", j is " << j
		<< "\nand we also have copies of the previous lambdas!" << endl;
		func1();
		func5(); // has a reference to j
		};
		
	func7();
	cout << "j is " << j << endl;
    
    // The default is that the function call operator of the created function object is a const member function.
    // so if you need to modify a variable captured by value, you have to say that the lambda is mutable.
    auto func8 = [i, j]() mutable {i++; j++; cout << "This lambda modifies its captured variables:  now i is " << i << ", j is " << j << endl; };
    func8();
    
    // You can only capture variables that are in the local block scope - not globals and not statics
//    auto bad_func = [gv]() {cout << "This lambda tries to capture a global variable by copy whose value = " << gv << endl;};
//    auto bad_func = [&gv]() {cout << "This lambda tries to capture a global variable by reference whose value = " << gv << endl;};
    static int my_local_static = 1001;
//  local statics are also not allowed
//    auto bad_func = [my_local_static]() {cout << "This lambda tries to capture a global variable whose value = " << gv << endl;};
//    auto bad_func = [&my_local_static]() {cout << "This lambda tries to capture a global variable whose value = " << gv << endl;};

}

class Thing {
public:
	// various public member functions
	void save(ostream& os) const; // write our data to the provided output stream
private:
	// member variables
};

// a custom function object class 
class Savem {
public:
	Savem(ostream& output_stream_) : output_stream(output_stream_) {}
	void operator() (Thing * ptr) const
	{
		ptr->save(output_stream);
	}
private:
	ostream& output_stream;
};


void demo_savem()
{
    ofstream out_file("output.txt"); // open a file for output
    list<Thing *> thing_ptrs;

    // tell each thing to save its data to the out_file stream
    for_each(thing_ptrs.begin(), thing_ptrs.end(), Savem(out_file));

    // using a lambda
    for_each(thing_ptrs.begin(), thing_ptrs.end(),
        [&out_file](Thing * ptr){ptr->save(out_file);} );
}

void demo_returned_value()
{
	cout << "\n\nLambda returned value demo" << endl;
	// A lambda can supply a returned value; often the function body consists of just a return statement;
	// the compiler deduces the returned type of the lambda from the type being returned.
	// If there is no return statement, a return type of void is assumed.
	
	// return type of void
	auto func1 = [] () {cout << "Hello from trivial lambda!" << endl;};
	// this is legal
	func1();
	// following is illegal - there is no return value to output
	// cout << "Can we output func1()'s return value? " << func1() << endl;

	// return type of bool
	// a lambda to determine if the second integer is exactly double the first integer
	auto func2 = [](int i, int j) {return j == 2*i;};
	if(func2(12, 24))
		cout << "It's true!" << endl;
	else
		cout << "It's false!" << endl;
		
	// What if you have more than one return statement, or you need to change the return type?
	// Use the wacky new bit of syntax:  -> type after the parameter list
	// Prevent any ambiguity with what type is going to be returned by specifying it explicitly.
	auto func3 = [] (int x, int y) -> int {
		if(x > 5)
			return x + y;
		else if (y < 2)
			return x - y;
		else
			return x * y;
		};
	cout << "func3 returns " << func3(4, 3) << endl;

	// The return type needs to be an int, even though the return statement provides a double
	auto func4 = [](double x, double y) -> int {return x + y;};
	cout << "func4 returns " << func4(3.14, 2.7) << endl;

}

void demo_capture()
{
	cout << "\n\nDemo of capture - when it happens" << endl;
    int int_var = 42;
    cout << "Create a lambda at function scope that captures a variable at function scope" << endl;
	auto func3 = [int_var] () {cout << "This lambda has a copy of int_var when created: " << int_var << endl;};
	func3();

    for(int i = 0; i < 3; i++) {
        int_var++;
        // int_var changes before every call of func3, but it uses a copy of the original value when created
        func3();
        }

    cout << "Create a lambda inside a for-loop that captures a variable at function scope" << endl;
    for(int i = 0; i < 3; i++) {
        int_var++;
        // func4 uses a copy of int_var everytime it is created
        auto func4 = [int_var] () {cout << "This lambda has a copy of int_var when created: " << int_var << endl;};
        func4();
        }

    cout << "Create a lambda at function scope that captures a variable at function scope by reference" << endl;
	auto func5 = [&int_var] () {cout << "This lambda captures int_var by reference: " << int_var << endl;};
    for(int i = 0; i < 3; i++) {
        // the lambda now refers to int_var, and so gets its current value every time it is called
        int_var++;
        func5();
        }



}

void demo_with_algorithms()
{
	cout << "\n\nDemo of using lambda to replace custom function object classes in algorithms" << endl;

	// In C++98, we often had to define custom one-use-only function object classes in order to use the STL
	// algorithms usefully. This was often clumsy and tedious. The super-terse lambda notation and the capture
	// facility works much better than function object classes when you only need the functionality once.

#ifndef _MSC_VER 
	// create a list of ints, brace initialized (C++11)
	list<int> int_list = {1, 2, 3, 4, 5};
#else
	list<int> int_list;
	int_list.push_back(1);
	int_list.push_back(2);
	int_list.push_back(3);
	int_list.push_back(4);
	int_list.push_back(5);
#endif


	// A simple case with a really simple custom function object to do something a bit unusual
	struct Printit {
		void operator() (int i) {cout << ":" << i << ":";}
		};
		
	for_each(int_list.begin(), int_list.end(), Printit());
	cout << endl;
	
	// Now with a lambda - why declare a function object class if this is all you need?
	for_each(int_list.begin(), int_list.end(), [](int i) {cout << ":" << i << ":";});
	cout << endl;

	

	// A more complicated case, using a local-scope function object class that returns true
	// if it gets a value equal to a stored value supplied when the actual function object is constructed.
	// In C++98 this class would have to be declared outside this function to be used as in an algorithm,
	// which tended to clutter the larger scope with one-use-only function object class declarations.
	// In C++11 it can be declared in function scope to be used in an algorithm, which is narrower and thus better.
	class Is_it_equal_to {
		public:
			Is_it_equal_to (int saved_value_) : saved_value(saved_value_) {}
			bool operator() (int i)
				{return i == saved_value;}
		private:
			int saved_value;
		};
	
	cout << "What do you want to find? Enter an int: ";
	int query;
	cin >> query;
	
	auto it = find_if(int_list.begin(), int_list.end(), Is_it_equal_to(query));
	if(it == int_list.end())
		cout << "Not found, using lots of code" << endl;
	else
		cout << "Found, using lots of code" << endl;

	
	// Now, the same thing using a lambda, with a capture of a local variable
	cout << "What do you want to find? Enter an int: ";
	cin >> query;

	it = find_if(int_list.begin(), int_list.end(), [query](int i) {return i == query;});
	if(it == int_list.end())
		cout << "Not found, using only a bit of code" << endl;
	else
		cout << "Found, using only a bit of code" << endl;
        
    ofstream out_file("output.txt");
	for_each(int_list.begin(), int_list.end(),
        [&out_file](int i) {out_file << i << endl;});
        
    cout << "\nDemonstrate lambda with transform alogorithm and inserter and stream iterator" << endl;
     // a more complicated situation - using a lambda to specify a transformation, copy and stream iterator
    // for output
    copy(int_list.begin(), int_list.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    list<int> result;
    transform(int_list.begin(), int_list.end(), back_inserter(result), [](int i){return i * i;} );
    copy(result.begin(), result.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

}

class Gizmo {
public:
    Gizmo() : ints{1,3,5,7,9,11,13,15,18,20}, criterion{10}, count{0} {}
	// returns the number of ints greater than criterion
	int get_count_over_criterion()
    {
	count = 0;
	for_each(ints.begin(), ints.end(), 
		[this](int i) {if (i > criterion) count++;} );
	return count;
    }

private:
	std::list<int> ints;
	int criterion;
	int count;
};

void demo_member_variable_capture()
{
	cout << "\n\nDemo of using a lambda in a member function to operate on member variables" << endl;

    Gizmo gizmo;
    
    cout << gizmo.get_count_over_criterion() << endl;
}



/* Sample output using Xcode 4.4.1 LLVM 4.0, c++11, libc++
Lambda basics demo
Hello from trivial lambda!
This lambda got a parameter value of 42
This lambda got a parameter value of 12
This lambda captures the value of i: 42
This lambda captured i of 42 and got a parameter of 13
j is 6
This lambda is modifying j by adding 5
j is 11
j is 11
This lambda sets j to the value in i
j is 42
This lambda has a copy of everything! i is 42 j is 42
and we also have copies of the previous lambdas!
Hello from trivial lambda!
This lambda is modifying j by adding 5
j is 47
This lambda modifies its captured variables:  now i is 43, j is 48


Lambda returned value demo
Hello from trivial lambda!
It's true!
func3 returns 12
func4 returns 5


Demo of using lambda to replace custom function object classes in algorithms
:1::2::3::4::5:
:1::2::3::4::5:
What do you want to find? Enter an int: 3
Found, using lots of code
What do you want to find? Enter an int: 7
Not found, using only a bit of code

Demonstrate lambda with transform alogorithm and inserter and stream iterator
1 2 3 4 5 
1 4 9 16 25 


Demo of using a lambda in a member function to operate on member variables
5
Done
*/

