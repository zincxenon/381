/* demonstration of how you can disorder a set that holds pointers to objects 
Tested with CodeWarrior 8.3, also at http://www.comeaucomputing.com/
*/


#include <iostream>
#include <set>

using namespace std;

class Thing {
public:
	Thing(int i_ = 0) : i(i_) {}
	void set(int i_) {i = i_;}
	int get() const {return i;}
	bool operator< (const Thing& t) const {return i < t.i;}
private:
	int i;
};

struct Less_Thing_ptrs {
	bool operator() (const Thing * p1, const Thing * p2) const
		{return p1->get() < p2->get();}
};

ostream& operator<< (ostream& os, const Thing& t)
{
	os << "Thing " << t.get();
	return os;
}

int main()
{
//	typedef set<const Thing *, Less_Thing_ptrs> Thing_ptr_set_t;	// Typedef A
	typedef set<Thing *, Less_Thing_ptrs> Thing_ptr_set_t;			// Typedef B
	Thing_ptr_set_t thing_ptr_set;
	
	cout << "input integers, enter an alphabetic when done" << endl;
	
	int i;
	while(cin >> i) {
		thing_ptr_set.insert(new Thing(i));
		}
	cin.clear(); 	// just to be neat
	
	cout << thing_ptr_set.size() << " different Things were present, as follows:" << endl;
	
	for(Thing_ptr_set_t::iterator it = thing_ptr_set.begin(); it != thing_ptr_set.end(); ++it)
		cout << *(*it) << endl;
		
	// set an iterator to one of the Things
	Thing probe(5);
	Thing_ptr_set_t::iterator find_it = thing_ptr_set.find(&probe);
	if(find_it == thing_ptr_set.end()) {
		cout << probe << " not found" << endl;
		return 0;
		}
	else
		cout << probe << " found " << *(*find_it) << endl;
		
	// does the iterator point to a const pointer?
	// *find_it = new Thing(17);	// yes - this is an error
		
	// does the iterator point to const or not?
	cout << (*find_it)->get() << " get through iterator" << endl;
	
	// For typedef A, the attempt to set the object through the iterator is an error
	// For Typedef B the container does not have pointers to const Thing, only const pointers to Thing
	// so you are free to change a Thing through the iterator
	(*find_it)->set(15);

	// For typedef B, casting the const away is unnecessary, but required under typedef A
	Thing * p_t = const_cast<Thing *>(*find_it);
	p_t->set(15);
	
	
	// the object has been changed in place, in a way that invalidates the ordering
	cout << *(*find_it) << " changed through casting away const for dereferenced iterator" << endl;
	
	cout << "container now has in it a disordered set:" << endl;
	for(Thing_ptr_set_t::iterator it = thing_ptr_set.begin(); it != thing_ptr_set.end(); ++it)
		cout << *(*it) << endl;
		
		
	cout << "Done" << endl;
	return 1;
}