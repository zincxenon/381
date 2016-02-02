//    *** CoinMoney_output_op ***

/*

This example assumes CoinMoney_why_private.cpp.
Illustrates overloading the output operator, which cannot be a member function
because the first parameter (left-hand-side) is an ostream class object, not 
a CoinMoney class object.

Notice - if you compile this example by itself you will get a variety of errors.
*/


// for brevity a lot of this has been left out in this example - see previous
// examples for the rest of the declaration
class CoinMoney {

public:	

	// constructors, readers, writers, get_value(), print() omitted to save space 

	// Since data members are private, we have to grant the overloaded << operator
	// "friend" status if we want it to be able to access the data members directly.
	// If this declaration is left out, then the << operator definition must use the public
	// reader/writer access functions instead.
	// Using "friend" for the output operator is customary, since
	// typically it is closely related to the class
	
	friend ostream& operator<< (ostream& os, CoinMoney m);

private:

	// member variables, private member functions omitted to save space 

};


// Overloaded << operator must be a non-member function!
// The first parameter must be a ostream object, not a CoinMoney object!
// The reference-type parameter and return type for ostream,
// and return of the ostream parameter is required!

ostream& operator<< (ostream& os, CoinMoney m)
{
	os << m.nickels << " nickels, " << m.dimes << " dimes, " 
		<< m.quarters << " quarters, totaling $" << m.get_value();
	return os;
}

