/*
Demonstration of using shared_ptr with a class hierarchy,
showing conversion to base type possibilities
and static and dynamic casts.
*/

#include <iostream>
#include <memory>
using namespace std;


class Base {
public:
	Base() : i(++count) {}
    // Because shared_ptr stores the original pointer type,
    // derived class objects will still get correctly destroyed
    // through shared_ptr<Base> even if ~Base() is not declared virtual.
    // But declaring ~Base() as virtual should still be done to avoid confusion.
    virtual ~Base() {cout << "Base " << i << " destruction" << endl;}
	int get() const {return i;}
	virtual void print() const
	{cout << "Base " << i << endl;}
private:
	int i;
	static int count;
};

int Base::count = 0;

class Base2 {
public:
	Base2() : i(++count) {}
	virtual ~Base2() {cout << "Base2 " << i << " destruction" << endl;}
	int get() const {return i;}
	virtual void print() const
	{cout << "Base2 " << i << endl;}
private:
	int i;
	static int count;
};

int Base2::count = 0;

class Derived1 : public Base {
public:
	Derived1(int j_) : j(j_) {}
	~Derived1() {cout << "Derived1 " << j << " destruction" << endl;}
	virtual void print() const {cout << "Derived1 " << get() << ':' << j << endl;}
private:
	int j;
};

class Derived2 : public Base {
public:
	Derived2(int j_) : j(j_) {}
	~Derived2() {cout << "Derived2 " << j << " destruction" << endl;}
	virtual void print() const {cout << "Derived2 " << get() << ':' << j << endl;}
private:
	int j;
};

class Derived3 : public Base, public Base2 {
public:
	Derived3(int j_) : j(j_) {}
	~Derived3() {cout << "Derived3 " << j << " destruction" << endl;}
	virtual void print() const {cout << "Derived3 " << Base::get() << ':' << Base2::get() << ':' << j << endl;}
private:
	int j;
};


int main()
{
	shared_ptr<Derived1> dp1(new Derived1(10));
	dp1->print();
	shared_ptr<Base> bp1 = dp1;	// assignment to Base pointer type
	bp1->print();				// virtual function call
	
	shared_ptr<Derived1> dp2 = static_pointer_cast<Derived1>(bp1);	// downcast - legal, but might be invalid
	dp2->print();

	shared_ptr<Base> bp2(dp1); // construction of Base from Derived shared_ptr type
	bp2->print();
	
	shared_ptr<Base> bp3(new Derived1(20)); // construction of Base from Derived * type
	bp3->print();

	shared_ptr<Derived1> dp3 = dynamic_pointer_cast<Derived1>(bp3); // downcast to valid type
	if(dp3)
		dp3->print();
	else
		cout << "dynamic cast failed" << endl;
	
	shared_ptr<Base> bp4(new Derived2(30));
	bp4->print();
    cout << typeid(*bp4.get()).name() << " is typeid of get" << endl;
    
	shared_ptr<Derived1> dp4 = dynamic_pointer_cast<Derived1>(bp4);  // downcast to invalid type
	if(dp4)
		dp4->print();
	else
		cout << "dynamic cast failed" << endl;

	shared_ptr<Base> bp5(new Derived3(40));
	bp5->print();
	shared_ptr<Base2> b2p1(new Derived3(41));
	b2p1->print();
	shared_ptr<Base> bp6(new Base);
	bp6->print();
    
//    shared_ptr<Base2> b2p2(bp5); // error no matching constructor
//    shared_ptr<Base2> b2p2(bp5.get()); // error no matching constructor
}

/* output
Derived1 1:10
Derived1 1:10
Derived1 1:10
Derived1 1:10
Derived1 2:20
Derived1 2:20
Derived2 3:30
8Derived2 is typeid of get
dynamic cast failed
Derived3 4:1:40
Derived3 5:2:41
Base 6
Base 6 destruction
Derived3 41 destruction
Base2 2 destruction
Base 5 destruction
Derived3 40 destruction
Base2 1 destruction
Base 4 destruction
Derived2 30 destruction
Base 3 destruction
Derived1 20 destruction
Base 2 destruction
Derived1 10 destruction
Base 1 destruction
*/


