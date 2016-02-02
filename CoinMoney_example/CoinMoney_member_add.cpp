//    *** CoinMoney_member_add ***

/*

This example assumes CoinMoney_why_private.cpp.
Instead of friend functions, make them member functions if possible - cleaner, simpler


Notice - if you compile this example by itself you will get a variety of errors.
*/


// for brevity a lot of this has been left out in this example - see previous
// examples for the rest of the declaration
class CoinMoney {

public:	

	// constructors, readers, writers, get_value(), print() omitted to save space 


// member function to add this CoinMoney object to a supplied one
// member function automatically has access to private data
// The "const" means this function does not change the data in this object

CoinMoney add(CoinMoney m2) const
{
	return CoinMoney (
		nickels + m2.nickels, // this object's nickels plus m2's nickels
		dimes + m2.dimes,
		quarters + m2.quarters
		);

}

// Overloaded operator+ function to this CoinMoney object to a supplied one
// The "const" means this function does not change the data in this object

CoinMoney operator+ (CoinMoney m2) const
{
	return CoinMoney (
		nickels + m2.nickels, // this object's nickels plus m2's nickels
		dimes + m2.dimes,
		quarters + m2.quarters
		);

}

private:

	// member variables, private member functions omitted to save space 

};


