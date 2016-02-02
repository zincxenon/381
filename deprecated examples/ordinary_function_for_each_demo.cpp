#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;

class Thing {
public:
	Thing(int in_i) : i(in_i) {}
	void print() const
		{cout << "Thing " << i << endl;}
	void update()
		{i++;}
	void set_value(int in_i)
		{i = in_i;}
	int get_value() const
		{return i;}
private:
	int i;
};

// write it a line by itself
ostream& operator<< (ostream& os, const Thing& t)
{
	os << "Thing " << t.get_value() << endl;
	return os;
}


/* The functions below do not take reference type parameters because the adapters
and binders end up creating "references to references" (& &) which are currently illegal in the
language, which turns out to be an extreme inconvenience that hopefully will be fixed in the
next Standard (which is being worked on right now). The fix will be that a reference to a reference
is simply a reference. Some compilers (like my current favorite) are ahead of the others in already
doing this, but it is not in fact standard. */

void print_Thing(Thing t)
{
	t.print();
}

void print_int_Thing(int i, Thing t)
{
	cout << i << ": " << t;
}

void print_Thing_int(Thing t, int i)
{
	cout << i << ": " << t;
}

void print_x_Thing(int i, Thing t)
{
	cout << i << ": " << t;
}

void print_x_Thing(string s, Thing t)
{
	cout << s << ": " << t;
}

int main()
{
	Thing t1(1), t2(2), t3(3);
	list<Thing> obj_list;
	obj_list.push_back(t1);	// a copy
	obj_list.push_back(t2);
	obj_list.push_back(t3);
	
	// try setting the value using an adapter to pass an argument
	
	cout << "Output from applying an ordinary function using obj_list" << endl;
	for_each(obj_list.begin(), obj_list.end(), print_Thing);
 
	cout << "Output from applying an ordinary function with ptr_fun using obj_list" << endl;
	for_each(obj_list.begin(), obj_list.end(), ptr_fun(print_Thing));
	
	// using binders with ordinary functions
	int new_value = 42;
	cout << "Output from applying a bind2nd adapter on an ordinary function" << endl;
	for_each(obj_list.begin(), obj_list.end(), bind2nd(ptr_fun(print_Thing_int), new_value));
	cout << "Output from applying a bind1st adapter on an ordinary function" << endl;
	for_each(obj_list.begin(), obj_list.end(), bind1st(ptr_fun(print_int_Thing), new_value));
	
	// using overloaded functions requires a cast to select the right function
	cout << "Output from applying a bind1st adapter on an overloaded function" << endl;
	for_each(obj_list.begin(), obj_list.end(), bind1st(ptr_fun((void (*)(int, Thing))print_x_Thing), new_value));
	cout << "Output from applying a bind1st adapter on another overloaded function" << endl;
	for_each(obj_list.begin(), obj_list.end(), bind1st(ptr_fun((void (*)(string, Thing))print_x_Thing), string("Hello")));

	/* following is illegal under current Standard because the ostream has to be passed in by reference */
	// for_each(obj_list.begin(), obj_list.end(), bind1st(ptr_fun((ostream& (*)(ostream&, const Thing&))operator<< ), cout));

	
	cout << "done!" << endl;
}