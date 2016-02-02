#include <iostream>
using namespace std;

class Base {
public:
	void zap() {
		cout << "Start zapping!" << endl;
		defrangulate();
		degauss();
		transmogrify();
		cout << "Done zapping!" << endl;
		}
protected:
	virtual void degauss()
		{cout << "Base degauss" << endl;}
private:
	virtual void defrangulate()
		{cout << "Base defrangulate" << endl;}
	virtual void transmogrify()
		{cout << "Base transmogrify" << endl;}

};

class Derived0 : public Base {
private:
};

class Derived1 : public Base {
private:
	void defrangulate() override
		{cout << "Derived1 defrangulate" << endl;}
};

class Derived2 : public Base {
private:
	void degauss() override
		{cout << "Derived2 degauss" << endl;
		Base::degauss();	// do Base's version also
		}
	void defrangulate() override
		{cout << "Derived2 defrangulate" << endl;}
	void transmogrify() override
		{cout << "Derived2 transmogrify" << endl;}
};


int main()
{
	Derived0 d0; Derived1 d1; Derived2 d2;
	
	cout << "use Derived0" << endl;
	(&d0)->zap();
	cout << "\nuse Derived1" << endl;
	(&d1)->zap();
	cout << "\nuse Derived2" << endl;
	(&d2)->zap();
}

/* Output
Start zapping!
Base defrangulate
Base deguass
Base transmogrify
Done zapping!
Start zapping!
Derived1 defrangulate
Base deguass
Base transmogrify
Done zapping!
Start zapping!
Base defrangulate
Derived2 deguass
Base deguass
Derived2 transmogrify
Done zapping!
*/