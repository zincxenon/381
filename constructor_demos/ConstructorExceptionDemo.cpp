//
//  ConstructorExceptionDemo.cpp
//  Cpp11Test
//
//  Created by David Kieras on 2/5/13.
//  Copyright (c) 2013 David Kieras. All rights reserved.
//

#include <iostream>
using namespace std;

// a simple exception class
struct Error {
	Error(const char * msg_) : msg(msg_) {}
	const char * msg;
};


// A class with instrumented constructor and destructor
// Its constructor throws an Error if the initialization
// parameter value is 42. Notice how if so, it never gets
// destructed because it never existed.
class Thing {
public:
	Thing(int i_ = 0) : i(i_)
		{
			if(i == 42)
				throw Error("Thing hates 42");
				
			cout << "Thing " << i << " constructed" << endl;
		}
	~Thing()
		{cout << "Thing " << i << " destructed" << endl;}
private:
	int i;
};

// global flag that controls whether the Gizmo
// class constructor throws an exception
bool throw_during_Gizmo_constructor = true;

/*
This class has a Thing member variable object initialized with 1.
This Thing is always created when Gizmo is created, and always get
destroyed when Gizmo gets destroyed or fails to complete its constructor,

Gizmo alwo allocates two Thing objects with new. 

If the first new Thing constructor throws an exception,
the new is canceled, and the the member variable Thing is destroyed because
the construction of the Gizmo has been canceled by the throw. All is good 
even if we don't catch the exception thrown by Thing. Here we catch and rethrow,
so that you can see that the first pointer is still null - there is nothing
to deallocate.

If the first new'd Thing constructs sucessfully, and the second new'd Thing throws, 
the situation is more complex. The first Thing now exists, but the second doesn't.
We have to catch the exception thrown by the second Thing's failed constructor,
and delete the first new'd Thing - see how its pointer is non-null. But the 
second new'd Thing never came into existence, so it doesn't have to be deleted.

Finally, if we decide to throw from Gizmo's constructor after newing the two Things,
it is our responsibility to clean them up before doing the throw. This is because
Gizmo's destructor will not be called if Gizmo threw during construction -
the Gizmo object never came into existence, so there is nothing to be destroyed.

Capsule summary:
If a class constructor executes on a single new operation (which might throw) and
does not do anything else that would throw an exception, then the constructor does
not need to take into account the throw during new. THe compiler will ensure that
everything is canceled or rolled-back. The class object never came into existence.

But if the class constructor does more than one new operation (which might throw).
or does a throw after those news for some reason, then the constructor needs to
be written to delete any of the new allocations that succeeded before leaving the constructor.
It will need to catch any exceptions thrown during the new allocates to do the deletes,
and also do the deletes before throwing. See the example below. 

These deletes are easy to do if the pointers have been initialized to null beforehand 
- delete of nullptr does nothing by definition, so there is no need 
to test the pointers before doing delete.

Trying playing with this code to see what happens. See the sample outputs below.
*/

class Gizmo {
public:
	Gizmo() : the_member_Thing(1), p1(nullptr), p2(nullptr)  // initialize both pointers
		{
			try {
			/* Possibilities for whether allocation to p1 and/or p2 succeed or throws 
			Comment out each of the following, one at a time, and see what happens. */			
			
/*			// Case both good: both Things exist, pointed to by p1 & p2, nothing thrown
			p1 = new Thing(76);
			p2 = new Thing(6);
			
			// Case first new throws: neither p1 nor p2 point to anything.
			// The failed construction of the first new Thing cancels its memory allocation.
			// Actually there is no need to catch this situation because nothing needs deallocation.
			// The second thing never gets allocated or constructed. Both pointers are still null.
			p1 = new Thing(42);
			p2 = new Thing(6);

			// The following is the same situation as previous case - first throws, second not tried.
			// both pointers will still be null.
			p1 = new Thing(42);
			p2 = new Thing(42);
*/			
			// Case second new throws:
			// The first new Thing exists, pointed to by p1.
			// Construction of the second throws, so p2 points to nothing, no memory allocated.
			// But we have to catch and deallocate the p1 object, otherwise we get a leak!
			// See how p1 has an address in it, while p2 is null
			p1 = new Thing(76);
			p2 = new Thing(42);

			}
			catch(...)
			{
				cout << "exception caught in Gizmo constructor" << endl;
				cout << "p1= " << p1 << endl;
				delete p1;
				cout << "p2= " << p2 << endl;
				delete p2;
				throw;	// continue with exception handling
			}
			// continue with construction - if Thing constructor fails
			// then we will never get here.
			
			if(throw_during_Gizmo_constructor) {
				cout << "Gizmo constructor is about to throw" << endl;
				// If we throw before Gizmo construction is complete,
				// the member variable Thing will be destroyed automatically,
				// but the two new'ed Things will not be - we have to take
				// care of that ourselves. Try commenting the below deletes
				// out and see that how the Things don't get destructed.
				cout << "p1= " << p1 << endl;
				delete p1;
				cout << "p2= " << p2 << endl;
				delete p2;
				
				throw Error("Gizmo construction failed!");
				}
			// here only if nothing thrown
			cout << "Gizmo constructed" << endl;
		}
	~Gizmo()
		{
			delete p1;
			delete p2;
			cout << "Gizmo destructed" << endl;
		}
private:
	Thing the_member_Thing;	// created and destroyed along with Gizmo
	Thing* p1;
	Thing* p2;

};


int main()
{
	try {
	cout << "About to declare Gizmo object" << endl;
	Gizmo g;
	cout << "About to leave main's try-block" << endl;
	}
	catch(Error& error)
	{
		cout << "catch of Error: " << error.msg << endl;
	}
	cout << "About to return from main()" << endl;

}

/* Output
// when throw_during_Gizmo_constructor is false:
// Case both good: 
About to declare Gizmo object
Thing 1 constructed
Thing 76 constructed
Thing 6 constructed
Gizmo constructed
About to leave main's try-block
Thing 76 destructed
Thing 6 destructed
Gizmo destructed
Thing 1 destructed
About to return from main()

// Case first new throws: 
About to declare Gizmo object
Thing 1 constructed
exception caught in Gizmo constructor
p1= 0x0
p2= 0x0
Thing 1 destructed
catch of Error: Thing hates 42
About to return from main()

// Case second new throws:
About to declare Gizmo object
Thing 1 constructed
Thing 76 constructed
exception caught in Gizmo constructor
p1= 0x1001000e0
Thing 76 destructed
p2= 0x0
Thing 1 destructed
catch of Error: Thing hates 42
About to return from main()

// when throw_during_Gizmo_constructor is true:
// Case both good: 
About to declare Gizmo object
Thing 1 constructed
Thing 76 constructed
Thing 6 constructed
Gizmo constructor is about to throw
p1= 0x1001000e0
Thing 76 destructed
p2= 0x100103b60
Thing 6 destructed
Thing 1 destructed
catch of Error: Gizmo construction failed!
About to return from main()

// Case second new throws:
About to declare Gizmo object
Thing 1 constructed
Thing 76 constructed
exception caught in Gizmo constructor
p1= 0x1001000e0
Thing 76 destructed
p2= 0x0
Thing 1 destructed
catch of Error: Thing hates 42
About to return from main()

*/
