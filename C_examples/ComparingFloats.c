/*
Demonstration that you can't compare floating-point (float or double) values and expect them
to be equal, even if they are equal mathematically.
*/
#include <stdio.h>


int main(void)
{
	float x = 1. / 1000.;	// approximately one-thousandth
	float y = x * 1000000.; // should be one thousand, right?
	
	if(y == 1000)
		printf("y == 1000\n");
	else
		printf("y != 1000\n");
	
	printf("y = %15.12lf\n", y);
	
	return 0;
}

/* example output - will depend on compiler, library, and machine

y != 1000
y = 1000.000061035156

*/