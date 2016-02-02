/* 
Demonstration of Smart_Pointer template.
*/
#include <iostream>
#include "Smart_Pointer.h"

using namespace std;

/* A Thing has a pointer to another Thing and inherits from the Reference_Counted_Object
class defined in Smart_Pointer.h. 

The following code creates two Things that point to each other, and hands a 
Smart_Pointer to "this" to another function. Because the reference count is kept
in "this" object, no special arrangements need to be made to create a Smart_Pointer
to "this".
*/

class Thing;
void print_Thing(Smart_Pointer<Thing> ptr);	// declare this function here, define later

// Thing inherits from a class that provides the reference counting functionality
class Thing : public Reference_Counted_Object {
public:
	// give each Thing a unique number so we can easily tell them apart
	Thing() : i(++count) {}
	// verify the destruction
	~Thing () {cout << "Thing " << i << " destruction" << endl;}
	int get_i() const {return i;}
	// make this Thing point to another one
	void set_ptr(Smart_Pointer<Thing> p) 
		{ptr = p;}
	// display who this Thing is now pointing to, if anybody
	void print_pointing_to() const
	{
		if(ptr)
			cout <<  "Thing " << i << " is pointing to Thing " << ptr->get_i() << endl;
		else
			cout <<  "Thing " << i << " is pointing to nobody" << endl;
	}
	
	// demonstrates handing a Smart_Pointer to another function
	void print_from_this()
	{
		// get a Smart_Pointer that shares owenership with other Smart_Pointers
		Smart_Pointer<Thing> p(this);
		print_Thing(p);
		// shorter:
		//print_Thing(Smart_Pointer<Thing>(this));
		// even shorter:
		//print_Thing(this);
	}
	
	void reset_pointer()	// call to reset the internal pointer
	{
		ptr.reset();
	}

private:
	Smart_Pointer<Thing> ptr;	// keeps other Thing in existence as long as this Thing exists
	int i;
	static int count;
};

int Thing::count = 0;

// a function that takes a Smart_Pointer and calls the print_pointing_to function
void print_Thing(Smart_Pointer<Thing> ptr)
{
	cout << "in print_Thing: ";
	ptr->print_pointing_to();
}

int main()
{
	Smart_Pointer<Thing> p1(new Thing);
	Smart_Pointer<Thing> p2(new Thing);
		
	// create a cycle with two set_ptr calls:
	p1->set_ptr(p2);
	p2->set_ptr(p1);
	
	// display what each object is pointing to:
	p1->print_pointing_to();
	p2->print_pointing_to();
	
	// invoke a function that passes a pointer to the object to another function.
	p1->print_from_this();
	p2->print_from_this();

	// break the cycle by calling the pointer reset function for one of the objects
	// to discard its pointer. Without this, the two Things will not get destroyed.
	p1->reset_pointer();	
	p2.reset();	// this assignment will immediately destroy the second Thing.
	
	cout << "Exiting main function" << endl;
	// The first Thing will be destroyed when p1 goes out of scope
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
