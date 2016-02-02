//    *** CoinMoney_overloaded-ops.cpp ***

// This version includes a set of overloaded operators that illustrate how to define 
// CoinMoney objects so that they can be used like a regular built-in numeric type.
// The operator overload functions are defined both as friends and members for illustration.
// "Obsolete" functions for adding and printing have been eliminated.
// All of the class members are included, because this is getting to be a "complete" class,
// like one you would actually want to use.

#include <iostream>
using namespace std;

class CoinMoney {
public:	

	// Default constructor
	CoinMoney() 
	{
		nickels = 0;
		dimes = 0;
		quarters = 0;
		cached_value = 0.;
		value_is_good = true;
	}

	// Constructor with arguments
	CoinMoney(int n, int d, int q)
	{
		nickels = n;
		dimes = d;
		quarters = q;
		cached_value = compute_value(); 
		value_is_good = true;
	}
	
	// reader functions
	// The "const" means this function does not change the data in this object
	int get_nickels() const
		{return nickels;}
	int get_dimes() const
		{return dimes;}
	int get_quarters() const
		{return quarters;}

	// writer functions
	// changing one of the values means the cached value is invalid.
	void set_nickels(int x) 
		{
			nickels = x;
			value_is_good = false;
		}
	void set_dimes(int x) 
		{
			dimes = x;
			value_is_good = false;
		}
	void set_quarters(int x) 
		{
			quarters = x;
			value_is_good = false;
		}


	// This member function returns the total value of the object.  
	// If the cached_value is good, it is returned immediately.
	// Otherwise the value is updated.
	// A private "helper" function is used for the actual value calculation.
	// This function changes this object's data, but not as far as outsiders
	// are concerned - the change is strictly private. "mutable" allows it to be const
	
	double get_value() const
	{
		if (value_is_good)
			return cached_value;
		else {
			cached_value = compute_value(); 
			value_is_good = true;
			return cached_value;
			}
	}

	// Overloaded + operator as a member function, - operator as a friend function.

	// This object is the implicit first parameter for the member operator functions.	

	CoinMoney operator+ (CoinMoney m2) const
	{
		return CoinMoney(nickels + m2.nickels, dimes + m2.dimes, quarters + m2.quarters);
	}

	// declare that the non-member definition of operator- is a friend	
	
	friend CoinMoney operator- (CoinMoney m1, CoinMoney m2);

	// Overloaded == and != operators as member functions
	// Two CoinMoney objects are equal if they have the same number of each type of coin
	
	bool operator== (CoinMoney m2) const
	{
		return (
			(nickels == m2.nickels) && 
			(dimes == m2.dimes) &&
			(quarters == m2.quarters));
	}
	
	// Two CoinMoney objects are unequal if they differ in the number of any type of coin
	
	bool operator!= (CoinMoney m2) const
	{
		return (
			(nickels != m2.nickels) || 
			(dimes != m2.dimes) ||
			(quarters != m2.quarters)
			);
	}
	
	// Since data members are private, we have to grant the overloaded << operator
	// "friend" status if we want it to be able to access the data members directly.
	// If this declaration is left out, then the << operator definition must use the public
	// access functions instead.
	
	friend ostream& operator<< (ostream& os, CoinMoney m);
	

private:
	int nickels;
	int dimes;
	int quarters;
	// mutable is a new keyword - it allows a const member function to modify the value
	mutable double cached_value;	// the last total value of the object
	mutable bool value_is_good;		// true if the last total value is good

	double compute_value() const
	{
		return (5 * nickels + 10 * dimes + 25 * quarters) / 100.;
	}

};

// non member definition of overloaded operator- 
CoinMoney operator- (CoinMoney m1, CoinMoney m2)
{
	return CoinMoney(m1.nickels - m2.nickels, m1.dimes - m2.dimes, 
		m1.quarters - m2.quarters);
}

// Overloaded << operator must be a non-member function!
// The first parameter must be a stream object, not a CoinMoney object!
// The reference-type  parameter and return value for ostream is required!

ostream& operator<< (ostream& os, CoinMoney m)
{
	os << m.nickels << " nickels, " << m.dimes << " dimes, " 
		<< m.quarters << " quarters, totaling $" << m.get_value();
	return os;
}

// We can now output, compare, and do arithmetic with CoinMoney objects
// just like built-in types!
int main (void)
{
	CoinMoney m1(2, 0, 1), m2, m3;
	cout << "m1 = " << m1 << endl;		
	m2 = m1;
	cout << "m2 = " << m2 << endl;			
	if (m1 == m2)
		cout << "m1 and m2 are equal" << endl;	
	m2.set_dimes(3);
	cout << "m2 is now " << m2 << endl;		
	if (m1 != m2)
		cout << "m1 and m2 are not equal" << endl;	
	m3 = m1 + m2;
	cout << "m3 = " << m3 << endl;
	m3 = (m2 + m3) - m1;
	cout << "m3 = " << m3 << endl;		
}

/* OUTPUT:
m1 = 2 nickels, 0 dimes, 1 quarters, totaling $0.35
m2 = 2 nickels, 0 dimes, 1 quarters, totaling $0.35
m1 and m2 are equal
m2 is now 2 nickels, 3 dimes, 1 quarters, totaling $0.65
m1 and m2 are not equal
m3 = 4 nickels, 3 dimes, 2 quarters, totaling $1
m3 = 4 nickels, 6 dimes, 2 quarters, totaling $1.3
*/
