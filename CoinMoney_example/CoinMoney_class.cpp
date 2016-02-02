//    *** CoinMoney_class.cpp

// This C++ program defines a class for coin money objects, following the normal customs
// of making data members private, and including reader and writer functions.
// Constructors are defined to handle the automatic initialization of objects.
// The get_value() and print() functions are member functions; they have the priviledge
// of having access to the private data members

#include <iostream>
using namespace std;

class CoinMoney 
{
// It is customary to describe the public members of a class first.
public:		// Class members are private by default, so have to specify public

	// Default constructor - no arguments - called by default 
	// to initialize this CoinMoney object when it is created (allocated)
	CoinMoney() 
	{
		nickels = 0;
		dimes = 0;
		quarters = 0;
	}

	// Constructor with arguments - used to specify initial values during creation.
	CoinMoney(int n, int d, int q)
	{
		nickels = n;
		dimes = d;
		quarters = q;
	}
	
	// reader functions
	// The "const" means this function does not change the data in this object
	int get_nickels() const {return nickels;}
	int get_dimes() const {return dimes;}
	int get_quarters() const {return quarters;}

	// writer functions
	void set_nickels(int x) {nickels = x;}
	void set_dimes(int x) {dimes = x;}
	void set_quarters(int x) {quarters = x;}
		
	// This member function returns the total value of this object.
	// Because it is a member function, it has access to private members.
	// The "const" means this function does not change the data in this object
	double get_value() const
	{
		return (5 * nickels + 10 * dimes + 25 * quarters) / 100.;
	}

	// This member function prints out the contents and value of this object.
	// The "const" means this function does not change the data in the object
	void print() const
	{
	cout << nickels << " nickels, " 
		 << dimes << " dimes, " 
		 << quarters << " quarters totaling $" 
		 << get_value() << endl;
	}

private:
	int nickels; 	// private data members can't be accessed outside the class members
	int dimes;
	int quarters;

};

// This function is not a member function, so it can not access private members
CoinMoney add(CoinMoney m1, CoinMoney m2)
{
 	// Create a CoinMoney object and set its members to the sum.
	CoinMoney sum;
		
	// sum.nickels = m1.nickels + m2.nickels;	// error! Can't access private members!
	// must use public reader & writer functions
	sum.set_nickels(m1.get_nickels() + m2.get_nickels());
	sum.set_dimes(m1.get_dimes() + m2.get_dimes());
	sum.set_quarters(m1.get_quarters() + m2.get_quarters());

	return sum;
}


int main (void)
{

	CoinMoney m1 (1, 2, 3);		// initialized by constructor with arguments
	CoinMoney m2, m3;			// automagically initialized by default constructor
		
	cout << "m1 = ";
	m1.print();					// print values using member function
	
	cout << "m2 = ";			// m2 is initialized correctly
	m2.print();

//	m2.nickels = 3;				// error! private members!
	m2.set_nickels(1);
	m2.set_dimes(2);
	m2.set_quarters(3);
		
	cout << "m1's value is " << m1.get_value() << endl;	
		
	m2 = m1;					// can assign, like C struct
	
	cout << "m2 = ";
	m2.print();
		
	m3 = add(m1, m2);			// use add function to add members
	
	cout << "m3 = ";
	m3.print();
}

/* OUTPUT:

m1 = 1 nickels, 2 dimes, 3 quarters, totaling $1
m2 = 0 nickels, 0 dimes, 0 quarters, totaling $0
m1's value is 1
m2 = 1 nickels, 2 dimes, 3 quarters, totaling $1
m3 = 2 nickels, 4 dimes, 6 quarters, totaling $2

*/
