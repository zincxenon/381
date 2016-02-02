#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;

/* 
This example shows how one might go about defining function objects that integrate with 
the adapters used with the algorithms.
*/

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


// inherit from std::binary_function which contains typedefs 
// that are required by adapters like bind2nd
struct Thing_int_printer : public std::binary_function<Thing, int, void> {
	void operator() (Thing t, int i) const
		{ cout << "Thing value: " << t.get_value() << ": int: " << i << endl;}
};

struct odd_Thing_pred : public std::unary_function<Thing, bool> {
	bool operator() (Thing t) const
		{ return t.get_value() % 2;}
};



int main()
{
	Thing t1(1), t2(2), t3(3);	
	list<Thing> obj_list;
	obj_list.push_back(t1);
	obj_list.push_back(t2);
	obj_list.push_back(t3);
	
	cout << "Output using print member function" << endl;
	for_each(obj_list.begin(), obj_list.end(), mem_fun_ref(&Thing::print) );
	
	int int_value = 5;
	cout << "\nOutput using an adapter on my adaptable binary function object" << endl;
	
	for_each(obj_list.begin(), obj_list.end(), bind2nd(Thing_int_printer(), int_value));
	

	cout << "\nOutput using my adaptable unary predicate function object" << endl;
	list<Thing>::iterator it1 = find_if(obj_list.begin(), obj_list.end(), odd_Thing_pred());
	cout << *it1 << endl;

	cout << "Output using an adapter on my unary predicate function object" << endl;
	list<Thing>::iterator it2 = find_if(obj_list.begin(), obj_list.end(), not1(odd_Thing_pred()));
	cout << *it2 << endl;
	
	
	cout << "Done!" << endl;
}
