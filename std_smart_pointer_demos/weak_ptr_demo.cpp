/* 
Demonstration of shared_ptr and weak_ptr, showing how cycle problems can be solved.
*/
#include <iostream>
#include <memory>

using namespace std;

/* A Thing has a pointer to another Thing. The following code creates two Things that
point to each other. If the internal pointers are weak_ptrs, then when main discards 
its shared_ptrs, the objects get deleted properly.  
*/

class Thing {
public:
	// give each Thing a unique number so we can easily tell them apart
	Thing() : i(++count) {}
	// verify the destruction
	~Thing () {cout << "Thing " << i << " destruction" << endl;}
	int get_i() const {return i;}
	// make this Thing point to another one
	void set_ptr(shared_ptr<Thing> p) 
		{ptr = p;}
	// display who this Thing is now pointing to, if anybody
	void print_pointing_to() const
	{
		if(ptr.expired())	// see if the pointed-to object is there
			cout << "Thing " << i << " is pointing at nothing" << endl;
		else {
			// create a temporary shared pointer, making sure the other Thing stays around
			// long enough to look at it
			shared_ptr<Thing> p = ptr.lock();
			if(p)	// redundant in this code, but another way to test for expiration
				cout <<  "Thing " << i << " is pointing to Thing " << p->get_i() << endl;
			} 
	}
private:
	weak_ptr<Thing> ptr;	// points to the other Thing, but doesn't affect lifetime
	int i;
	static int count;
};

int Thing::count = 0;

int main()
{
	/* Always create objects like this, in single stand-alone statement that does nothing 
	more than create the new object in a shared_ptr constructor, to minimize any possibility 
	of having a stray ordinary pointer involved, or other wierd effects.
	*/

	shared_ptr<Thing> p1(new Thing);
	shared_ptr<Thing> p2(new Thing);
	
	// display what each object is pointing to:
	p1->print_pointing_to();
	p2->print_pointing_to();

	// create the cycle with two set_ptr calls:
	p1->set_ptr(p2);
	p2->set_ptr(p1);
	
	// display what each object is pointing to:
	p1->print_pointing_to();
	p2->print_pointing_to();

/*	A.
	// reset with no arguments is how you discard the pointed-to object;
	// it zeroes-out the internal pointer to the shared object; 
	p1.reset();
	// display what Thing 2 is pointing to
	p2->print_pointing_to();
*/
	
	cout << "Exiting main function" << endl;
// when p1 and p2 go out of scope, they will free the pointed-to objects if they are the 
// last pointers referring to them.
}

/* Sample output with the cycle created and the reset/print statements in A commented out.
Both objects are deleted on exit in spite of the cycle. 
--------
Thing 1 is pointing at nothing
Thing 2 is pointing at nothing
Thing 1 is pointing to Thing 2
Thing 2 is pointing to Thing 1
Exiting main function
Thing 2 destruction
Thing 1 destruction
*/

/* Sample output with the cycle created and the statements in A executed.
Thing 1 gets destructed by the reset, and now Thing 2 knows that it is not 
pointing at anything any more. Exiting then destroys Thing 2 also.
--------
Thing 1 is pointing at nothing
Thing 2 is pointing at nothing
Thing 1 is pointing to Thing 2
Thing 2 is pointing to Thing 1
Thing 1 destruction
Thing 2 is pointing at nothing
Exiting main function
Thing 2 destruction
*/

