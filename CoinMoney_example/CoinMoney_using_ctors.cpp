//    *** CoinMoney_using_ctors ***

/*

This example assumes CoinMoney_class.cpp or CoinMoney_why_private.cpp.
It illustrates three different ways to implement the add function by
using the CoinMoney class constructor and the reader/writer functions.

Notice - if you compile this example by itself you will get a variety of errors.
*/


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

	
// Instead of creating an object and setting its members, 
// we can use a constructor to set the values during initialization.

CoinMoney add(CoinMoney m1, CoinMoney m2)
{
 	// Create a CoinMoney object initialized with the sums.

	CoinMoney sum (
		m1.get_nickels() + m2.get_nickels(), 
		m1.get_dimes() + m2.get_dimes(),
		m1.get_quarters() + m2.get_quarters()
		);

	return sum;
}

// A shorter version - can declare, initialize, and return a temporary unnamed object.
CoinMoney add(CoinMoney m1, CoinMoney m2)
{
	return CoinMoney (
		m1.get_nickels() + m2.get_nickels(), 
		m1.get_dimes() + m2.get_dimes(),
		m1.get_quarters() + m2.get_quarters()
		);

}
