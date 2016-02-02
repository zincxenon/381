//    *** CoinMoney_friend_add ***

/*
This example assumes CoinMoney_why_private.cpp.
It shows how code can be simplified if a class has friends.

Notice - if you compile this example by itself you will get a variety of errors.
*/


// for brevity a lot of this has been left out in this example - see previous
// examples for the rest of the declaration
class CoinMoney {

public:	

	// constructors, readers, writers, get_value(), print() omitted to save space 

	// declare add function to be a friend - grant access to private members
	friend CoinMoney add(CoinMoney m1, CoinMoney m2);
	
	// can also declare operator+ to be a friend
	friend CoinMoney operator+ (CoinMoney m1, CoinMoney m2);

private:

	// member variables, private member functions omitted to save space 

	// friend declaration could be in private section also - 
	// it doesn't matter where it appears in the class declaration
};


// Friend versions now have direct access to private data in parameter objects
// Be careful! Bad friends can do a lot of damage!

// We still use constructors to make sure initializations are correct!
// We don't want to twiddle the implementation's bits directly - too tricky!

// Ordinary function to add two CoinMoney objects
CoinMoney add(CoinMoney m1, CoinMoney m2)
{
	return CoinMoney (
		m1.nickels + m2.nickels, 
		m1.dimes + m2.dimes,
		m1.quarters + m2.quarters
		);

}

// Overloaded operator+ function to add two CoinMoney objects
CoinMoney operator+ (CoinMoney m1, CoinMoney m2)
{
	return CoinMoney (
		m1.nickels + m2.nickels, 
		m1.dimes + m2.dimes,
		m1.quarters + m2.quarters
		);

}
