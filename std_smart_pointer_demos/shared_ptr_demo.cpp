/* 
Demonstration of shared_ptr.
This demo shows a how shared_ptr works in various situations with and without a cycle problem.
*/

#include <iostream>
#include <memory>

using namespace std;

/* A Thing has a pointer to another Thing. The following code creates two Things that
point to each other. If the internal pointers are shared_ptrs, the resulting
cycle means that the two objects will not get deleted even though main has discarded
their pointers.
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
		if(ptr)
			cout <<  "Thing " << i << " is pointing to Thing " << ptr->get_i() << endl;
		else
			cout <<  "Thing " << i << " is pointing to nobody" << endl;
	}
private:
	shared_ptr<Thing> ptr;	// keeps other Thing in existence as long as this Thing exists
	int i;
	static int count;
};

int Thing::count = 0;

int main()
{
	/* Always create objects like this, in single stand-alone statement that does nothing 
	more than create the new object in a shared_ptr constructor.
	*/

	shared_ptr<Thing> p1(new Thing);
	shared_ptr<Thing> p2(new Thing);

/* 	// It is difficult to set a shared_ptr to an object any other way.
	// The definition of shared_ptr disallows assigning from a raw pointer!
	shared_ptr<Thing> p3;

	Thing * raw_ptr = new Thing;
	p3 = raw_ptr;	// disallowed! compile error!

	// the following works, but there is no protection against raw_ptr being used elsewhere; try to avoid
	p3.reset(raw_ptr);
*/
		
	
	// create the cycle with two set_ptr calls:
	p1->set_ptr(p2);
//	p2->set_ptr(p1);
	
	// display what each object is pointing to:
	p1->print_pointing_to();
	p2->print_pointing_to();

//	reset with no arguments is how you discard the pointed-to object;
//	it zeroes-out the internal pointer to the shared object; 
//	If there were no cycles, this will cause both Things to be deleted.
//	p1.reset();	
	p2.reset();

	
	cout << "Exiting main function" << endl;	
}


/* Sample output with both cycle-creation statements and reset statements commented out,
showing automatic destruction on return:
--------
Thing 1 is pointing to nobody
Thing 2 is pointing to nobody
Exiting main function
Thing 2 destruction
Thing 1 destruction
*/

/* Sample output with both cycle-creation statements commented out, and reset statements in,
showing destruction when both pointers are reset.
--------
Thing 1 is pointing to nobody
Thing 2 is pointing to nobody
Thing 1 destruction
Thing 2 destruction
Exiting main function
*/

/* Sample output with the only the first of the two cycle-creation statements in and executed,
and only the second pointer (p2) reset statement in and executed. 
There is only a "half cycle" because Thing 1 is pointing to Thing 2, but Thing 2 points
to nobody. Discarding our pointer to Thing 2 does not destroy Thing 2 because it is kept alive
by Thing 1 pointing to it. When p1 goes out of scope Thing 1 is destroyed, which then results
in Thing 2 being destroyed. This shows smart pointers doing their automatical destruction.
--------
Thing 1 is pointing to Thing 2
Thing 2 is pointing to nobody
Exiting main function
Thing 1 destruction
Thing 2 destruction
*/

/* Sample output with cycle-creation statements in place and executed, 
and reset statements either in or commented out (doesn't change the output).
Notice how neither object gets destroyed! They keep each other alive!
--------
Thing 1 is pointing to Thing 2
Thing 2 is pointing to Thing 1
Exiting main function
*/