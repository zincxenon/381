/*      *** CoinMoney_C_struct.c ***
This C program illustrates how you can define your own data type as a structure
and use it like an ordinary variable, at least to some extent.
But it is also a valid C++ program.
*/
#include <stdio.h>

// declare the structure for CoinMoney - three int members
struct CoinMoney {
	int nickels;
	int dimes;
	int quarters;
};

/* Functions for working on CoinMoney structs */
double CoinMoney_value(struct CoinMoney m)
{
	return (5 * m.nickels + 10 * m.dimes + 25 * m.quarters) / 100.;
}

struct CoinMoney CoinMoney_add(struct CoinMoney m1, struct CoinMoney m2)
{
	struct CoinMoney sum;	
	sum.nickels = m1.nickels + m2.nickels;
	sum.dimes = m1.dimes + m2.dimes;
	sum.quarters = m1.quarters + m2.quarters;
	return sum;
}

void CoinMoney_print(struct CoinMoney m)
{
	printf("%d nickels, %d dimes, %d quarters totaling $%f\n", 
		m.nickels, m.dimes, m.quarters, CoinMoney_value(m));
}

int main (void)
{
	struct CoinMoney m1, m2, m3;	// create three CoinMoney variables
	double value1;
	
	m1.nickels = 2;					// initialize m1
	m1.dimes = 0;
	m1. quarters = 1;
	printf("m1 = ");
	CoinMoney_print(m1);			// print m1
	m2 = m1;						// can assign structs to each other
	printf("m2 = ");
	CoinMoney_print(m2);			// m2 is now a copy of m1
	value1 = CoinMoney_value(m1);	// get and print m1's total value
	printf("value1 is %f\n", value1);
	m3 = CoinMoney_add(m1, m2);		// add m1 & m2, store in m3
	printf("m3 = ");				// print m3
	CoinMoney_print(m3);
}

/* OUTPUT:
m1 = 2 nickels, 0 dimes, 1 quarters totaling $0.350000
m2 = 2 nickels, 0 dimes, 1 quarters totaling $0.350000
value1 is 0.350000
m3 = 4 nickels, 0 dimes, 2 quarters totaling $0.700000
*/
