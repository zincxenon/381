//    *** CoinMoney_overloaded_add ***

/*

This example assumes CoinMoney_class.cpp or CoinMoney_why_private.cpp.
It shows how the add function can be replaced by a definition of operator+

Notice - if you compile this example by itself you will get a variety of errors.
*/


// Ordinary function to add two CoinMoney objects
CoinMoney add(CoinMoney m1, CoinMoney m2)
{
	return CoinMoney (
		m1.get_nickels() + m2.get_nickels(), 
		m1.get_dimes() + m2.get_dimes(),
		m1.get_quarters() + m2.get_quarters()
		);

}

// Overloaded operator+ function to add two CoinMoney objects
CoinMoney operator+ (CoinMoney m1, CoinMoney m2)
{
	return CoinMoney (
		m1.get_nickels() + m2.get_nickels(), 
		m1.get_dimes() + m2.get_dimes(),
		m1.get_quarters() + m2.get_quarters()
		);

}

/*

Instead of 

	m3 = CoinMoney_add(m1, m2);		// add m1 & m2, store in m3

now we can write

	m3 = m1 + m2;
	
*/
