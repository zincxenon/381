/* demonstration of how you can disorder a set of objects by bypassing the fact that they
are treated as const objects by the set container and its iterators */

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

ostream& operator<< (ostream& os, const Thing& t)
{
	os << "Thing " << t.get();
	return os;
}

int main()
{
	// note how set is a set of Thing - not declared as set<const Thing>
	set<Thing> thing_set;
	
	cout << "input integers, enter an alphabetic when done" << endl;
	
	int i;
	while(cin >> i) {
		thing_set.insert(Thing(i));
		}
	cin.clear(); 	// just to be neat
	
	cout << thing_set.size() << " different Things were present, as follows:" << endl;
	
	for(set<Thing>::iterator it = thing_set.begin(); it != thing_set.end(); ++it)
		cout << *it << endl;
		
	// set an iterator to one of the Things
	Thing probe(5);
	set<Thing>::iterator find_it = thing_set.find(probe);
	if(find_it == thing_set.end()) {
		cout << probe << " not found" << endl;
		return 0;
		}
	else
		cout << probe << " found " << *find_it << endl;
		
	// does the iterator point to const or not?
	cout << find_it->get() << " get through iterator" << endl;
	
	// try to change the thing at the iterator
	// following two statements are compiler errors because set is set<const Thing> 
	// or iterator* returns const Thing&
//	*find_it = Thing(17);	// error
//	find_it->set(15);		// error

//	cast the constness away
	Thing& r_t = const_cast<Thing &>(*find_it);
	r_t.set(15);
	
	// the object has been changed in place
	cout << *find_it << " changed through casting away const for iterator" << endl;
	
	cout << "container now has in it a disordered set:" << endl;
	for(set<Thing>::iterator it = thing_set.begin(); it != thing_set.end(); ++it)
		cout << *it << endl;
		
		
	cout << "Done" << endl;
}