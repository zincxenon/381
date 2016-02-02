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
	void output(ostream& os) const
		{os << "Thing " << i << endl;}
	void update()
		{i++;}
	void set_value(int in_i)
		{i = in_i;}
	int get_value() const
		{return i;}
private:
	int i;
};

// a custom function object class that stores a stream reference
// and calls the member function that takes it as an argument
class Outputter {
public:
	Outputter(ostream& os_) : os(os_) {}
	// call the output member function with a stream parameter for the supplied Thing
	void operator() (const Thing& t) const 
		{t.output(os);}
	// an overload for use with a pointer
	void operator() (const Thing* t) const 
		{t->output(os);}
private:
	ostream& os;	// a reference-type member variable
};


int main()
{
	
	Thing t1(1), t2(2), t3(3);
	list<Thing *> ptr_list;
	ptr_list.push_back(&t1);
	ptr_list.push_back(&t2);
	ptr_list.push_back(&t3);
	
	// for ptr_list, the derefenced iterator from for_each is a Thing pointer
	cout << "Output using ptr_list" << endl;
	for_each(ptr_list.begin(), ptr_list.end(), mem_fun(&Thing::print) );
		
	list<Thing> obj_list;
	obj_list.push_back(t1);	// a copy
	obj_list.push_back(t2);
	obj_list.push_back(t3);
	
	// for obj_list, the derefenced iterator from for_each is a Thing object
	cout << "Output from using the print member function on obj_list" << endl;
	for_each(obj_list.begin(), obj_list.end(), mem_fun_ref(&Thing::print) );	

	// try to use the member function that takes a stream argument
	// below causes compile error - from g++
//	cout << "Output from using the output member function on obj_list" << endl;
//	for_each(obj_list.begin(), obj_list.end(), bind2nd(mem_fun_ref(&Thing::output), cout));	
// /usr/include/c++/4.0.0/bits/stl_function.h: In instantiation of ‘std::binder2nd<std::const_mem_fun1_ref_t<void, Thing, std::ostream&> >’:
// memberfun_for_each_stream_demo.cpp:72:   instantiated from here
// /usr/include/c++/4.0.0/bits/stl_function.h:435: error: forming reference to reference type ‘std::ostream&’
// /usr/include/c++/4.0.0/bits/stl_function.h: In function ‘std::binder2nd<_Operation> std::bind2nd(const _Operation&, const _Tp&) [with _Operation = std::const_mem_fun1_ref_t<void, Thing, std::ostream&>, _Tp = std::ostream]’:
	
	cout << "Output from using the print member function using ptr_list" << endl;
	for_each(ptr_list.begin(), ptr_list.end(), mem_fun(&Thing::print) );
	// below causes compile error like above
//	cout << "Output from using the output member function on ptr_list" << endl;
//	for_each(ptr_list.begin(), ptr_list.end(), bind2nd(mem_fun(&Thing::output), cout) );
	
	// use our custom function object class instead
	cout << "Output from using a function object that calls the output function for each Thing pointer in ptr_list" << endl;
	for_each(ptr_list.begin(), ptr_list.end(), Outputter(cout) );	
	cout << "Output from using a function object that calls the output function for each Thing in obj_list" << endl;
	for_each(obj_list.begin(), obj_list.end(), Outputter(cout) );	


	
	cout << "done!" << endl;
}