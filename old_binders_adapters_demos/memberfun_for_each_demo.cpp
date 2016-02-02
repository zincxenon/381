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
ostream& operator<< (ostream& os, const Thing &t)
{
	os << "Thing " << t.get_value() << endl;
	return os;
}

// a little class with a member function that will print a Thing
class Gizmo {
public:
	void print_Thing(Thing * p)
		{p->print();}
};

int main()
{
	
	Thing t1(1), t2(2), t3(3);
	list<Thing *> ptr_list;
	ptr_list.push_back(&t1);
	ptr_list.push_back(&t2);
	ptr_list.push_back(&t3);
	
	cout << "Output using ptr_list" << endl;
	for_each(ptr_list.begin(), ptr_list.end(), mem_fun(&Thing::print) );
	
	cout << "Output using Gizmo to print each Thing in ptr_list" << endl;
	Gizmo gizmo;
	Gizmo * gizmo_ptr = &gizmo;
	// demonstrate bind1st used to make a member function of another class callable with the
	// dereferenced iterator as the argument
	for_each(ptr_list.begin(), ptr_list.end(), bind1st(mem_fun(&Gizmo::print_Thing), gizmo_ptr));
	
	list<Thing> obj_list;
	obj_list.push_back(t1);	// a copy
	obj_list.push_back(t2);
	obj_list.push_back(t3);
	
	// in below, 
	// for obj_list, the derefenced iterator from for_each is a Thing object
	// for ptr_list, the derefenced iterator from for_each is a Thing pointer

	cout << "Output using obj_list" << endl;
	for_each(obj_list.begin(), obj_list.end(), mem_fun_ref(&Thing::print) );
	
	// try updating the objects
	for_each(ptr_list.begin(), ptr_list.end(), mem_fun(&Thing::update) );
	
	cout << "Output after update using ptr_list" << endl;
	for_each(ptr_list.begin(), ptr_list.end(), mem_fun(&Thing::print) );
	
	// try updating the objects
	for_each(obj_list.begin(), obj_list.end(), mem_fun_ref(&Thing::update) );
	
	cout << "Output after update using obj_list" << endl;
	for_each(obj_list.begin(), obj_list.end(), mem_fun_ref(&Thing::print) );
	
	// try setting the value using an adapterto pass an argument for the pointer list
	int new_value = 21;
	cout << "Set the value with an adapter on the pointer list" << endl;
	for_each(ptr_list.begin(), ptr_list.end(), bind2nd(mem_fun(&Thing::set_value), new_value) );
	cout << "Output after setting value using ptr_list" << endl;
	for_each(ptr_list.begin(), ptr_list.end(), mem_fun(&Thing::print) );
	
	
	// try setting the value using an adapterto pass an argument for the object list
	new_value = 42;
	cout << "Set the value with an adapter on the object list" << endl;
	// Comeau's compiler objects to the line below
	for_each(obj_list.begin(), obj_list.end(), bind2nd(mem_fun_ref(&Thing::set_value), new_value) );
	cout << "Output from using the print member function on obj_list" << endl;
	for_each(obj_list.begin(), obj_list.end(), mem_fun_ref(&Thing::print) );	

	
	cout << "done!" << endl;
}