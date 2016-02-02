//   *** CoinMoney_why_private.cpp ***

// This version of the CoinMoney class illustrates how using public reader and writer 
// functions allows one to hide a very different internal implementation.  
// Instead of calculating the total value of the coins every time it is needed, 
// this class saves the total value, keeps track of whether the number of coins 
// has been changed, and calculates a new total only when necessary - "lazy evaluation."

// But all this is completely invisible to the user of the class!
// Also, the user cannot accidently mess it up, because the internal data is private.

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
		cached_value = 0.;				// initialize the cached_value information
		value_is_good = true;
	}

	// Constructor with arguments
	CoinMoney(int n, int d, int q)
	{
		nickels = n;
		dimes = d;
		quarters = q;
		cached_value = compute_value(); // initialize the cached_value information
		value_is_good = true;
	}
	
	// reader functions
	// The "const" means this function does not change the data in this object
	int get_nickels() const {return nickels;}
	int get_dimes() const {return dimes;}
	int get_quarters() const {return quarters;}

	// writer functions
	// changing one of the values means the cached value is now invalid.
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


	// This member function get_value() returns the total value of this object.  
	// If the cached_value is good, it is returned immediately.
	// Otherwise the value is updated and returned.
	// A private "helper" function is used for the actual value calculation.
	// This function changes this object's data, but not as far as outsiders
	// are concerned - the change is strictly private. "mutable" allows it to be const
	
	double get_value() const
	{
		if (value_is_good)
			return cached_value;
		else {
			cout << "*** updating cached_value ***" << endl; // output for demo only	
			cached_value = compute_value(); 
			value_is_good = true;
			return cached_value;
			}
	}

	// This member function prints out the contents and value of this object.
	// It can't be const because it uses value() which is not const
	void print() const
	{
	cout << nickels << " nickels, " 
		 << dimes << " dimes, " 
		 << quarters << " quarters totaling "
		 << get_value() << endl;
	}

private:
	int nickels;
	int dimes;
	int quarters;
	// mutable is a new keyword - it allows a const member function to modify the value
	mutable double cached_value;	// the last total value of the object
	mutable bool value_is_good;		// true if the last total value is good

	// a private member function - a "helper" function for use only inside this class
	double compute_value() const
	{return (5 * nickels + 10 * dimes + 25 * quarters) / 100.;}

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

	// Code using CoinMoney is not aware of different implementation
	CoinMoney m1 (1, 2, 3);
		
	cout << "\nabout to get m1's value" << endl; // output for demo only	
	cout << "m1's value is " << m1.get_value() << endl;	
	
	cout << "changing m1" << endl; // output for demo only	
	m1.set_dimes(5);

	cout << "\nabout to get m1's value" << endl;	
	cout << "m1's value is " << m1.get_value() << endl;	
	cout << "changing all three fields of m1" << endl;
	m1.set_nickels(3);
	m1.set_dimes(1);
	m1.set_quarters(2);
		
	cout << "\nabout to get m1's value" << endl;
	cout << "m1's value is " << m1.get_value() << endl;	

//	m1.dimes = 23; // error! private! would screw up value caching scheme!
	
	cout << "\nabout to get m1's value" << endl;
	cout << "m1's value is still " << m1.get_value() << endl;	

}

/* OUTPUT:
about to get m1's value
m1's value is 1
changing m1

about to get m1's value
*** updating cached_value ***
m1's value is 1.3
changing all three fields of m1

about to get m1's value
*** updating cached_value ***
m1's value is 0.75

about to get m1's value
m1's value is still 0.75
*/
