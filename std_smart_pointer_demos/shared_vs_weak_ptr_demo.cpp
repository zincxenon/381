/* Comparison of shared_ptr and weak_ptr as
returned values from functions. Also, demo
of testing for expired object.
*/

#include <iostream>
#include <memory>

using namespace std;


class Thing {
public:
	Thing() : i (++count) {cout << "Thing " << i << " creation" << endl;}
	~Thing () {cout << "Thing " << i << " destruction" << endl;}
	int get() const {return i;}
private:
	int i;
	static int count;
};

int Thing::count = 0;

// create a Thing, but return a weak_ptr to it - gets destructed
weak_ptr<Thing> return_weak()
{
	shared_ptr<Thing> p (new Thing);
	
	cout << "in return_weak: Thing " << p->get() << endl;

	weak_ptr<Thing> wp = p;
	return wp;
}

// create a Thing, but return a shared_ptr to it
shared_ptr<Thing> return_shared()
{
	shared_ptr<Thing> p (new Thing);
	
	cout << "in return_shared: Thing " << p->get() << endl;

	return p;
}

// check the weak_ptr to see if the Thing is still there,
// in two different ways
void is_it_there(weak_ptr<Thing> wp)
{
	if (wp.expired())
		cout << "it is expired" << endl;
	else
		cout << "it is not expired" << endl;

	shared_ptr<Thing> p = wp.lock();
	if(!p)
		cout << "it is gone!" << endl;
	else
		cout <<  "it is Thing " << p->get() << endl;	
}	

int main()
{
	shared_ptr<Thing> p (new Thing);
	
	cout << "in main: Thing " << p->get() << endl;
	
	weak_ptr<Thing> wp1 = return_weak();
	is_it_there(wp1);
	
	p = return_shared();
	weak_ptr<Thing> wp2 = p ;
	is_it_there(wp2);
	
	
	return 0;
}

/* output:
Thing 1 creation
in main: Thing 1
Thing 2 creation
in return_weak: Thing 2
Thing 2 destruction
it is expired
it is gone!
Thing 3 creation
in return_shared: Thing 3
Thing 1 destruction
it is not expired
it is Thing 3
Thing 3 destruction
*/

