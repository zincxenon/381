/* 
Demonstration of shared_ptr's shared_from_this facility.
*/

#include <iostream>
#include <memory>

using namespace std;

/* A Thing has a pointer to another Thing. The following code creates two Things that
point to each other. 
*/

// shared_ptr works with an incomplete type!
class Thing;
void print_Thing(shared_ptr<Thing> ptr);	// declare this function here, define later


// Thing inherits from template class std::tr1::enaable_shared_from_this<>
class Thing : public enable_shared_from_this<Thing> {
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
	
	// demonstrates use of shared_from_this()
	void print_from_this()
	{
		// get a shared_ptr that shares owenership with other shared_ptrs
		shared_ptr<Thing> p = shared_from_this();
		print_Thing(p);
		// shorter:
		//print_Thing(shared_from_this());
	}
	
	void reset_pointer()	// call to reset the internal pointer
	{
		ptr.reset();
	}

private:
	shared_ptr<Thing> ptr;	// keeps other Thing in existence as long as this Thing exists
	int i;
	static int count;
};

int Thing::count = 0;

// a function that takes a shared_ptr and calls the print_pointing_to function
void print_Thing(shared_ptr<Thing> ptr)
{
	cout << "in print_Thing: ";
	ptr->print_pointing_to();
}

int main()
{
	/* Always create objects like this, in single stand-alone statement that does nothing 
	more than create the new object in a shared_ptr constructor. This will help prevent 
	accidentally assigning more than one shared_ptr family to the same object.
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
		
	// create a cycle with two set_ptr calls:
	p1->set_ptr(p2);
	p2->set_ptr(p1);
	
	// display what each object is pointing to:
	p1->print_pointing_to();
	p2->print_pointing_to();
	
	// invoke a function that uses shared_from_this to pass a pointer to the object
	// to another function.
	p1->print_from_this();
	p2->print_from_this();

	// reset with no arguments is how you discard the pointed-to object;
	// break the cycle by calling the pointer reset function for one of the objects
	// to discard its pointer
	p1->reset_pointer();	
	p2.reset();
	
	cout << "Exiting main function" << endl;	
}


/* Output
Thing 1 is pointing to Thing 2
Thing 2 is pointing to Thing 1
in print_Thing: Thing 1 is pointing to Thing 2
in print_Thing: Thing 2 is pointing to Thing 1
Thing 2 destruction
Exiting main function
Thing 1 destruction
*/
