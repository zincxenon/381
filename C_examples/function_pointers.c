/* Demonstration of function pointers in a trival context. */

#include <stdio.h>

/* the function pointer type */
typedef int (*int_getter_t)(int *);

/* function prototypes */
void do_the_work(int_getter_t);
int get_odd_int(int *);
int get_even_int(int *);


/* main asks the user which function to use, sets a pointer correspondingly,
and then hands it to the do_the_work function to use.
*/
int main(void)
{
	int_getter_t fp;	/* the function pointer */
	char c;
	
	while(1) {
		printf("Do you like odd numbers? Enter y, n, or anything else to quit: ");
		/* the whitespace in the format string says to skip leading whitespace and then read a character */
		scanf(" %c", &c);	

		if(c == 'y') {
	/*		fp = get_odd_int;  		one syntax */
			fp = &get_odd_int; /*	an equivalent syntax */
			}
		else if(c == 'n') {
	/*		fp = get_even_int; */
			fp = &get_even_int;
			}
		else
			break;
			
		/* call using the function pointer as an argument */
		do_the_work(fp);
		}
	
	printf("Done!\n");
	return 0;
}

/* this function "does the work" using a function passed as a parameter */
void do_the_work(int_getter_t fp)
{
	int i, result;

	/* call the function using the pointer */
/*	result = fp(&i);		one syntax */
	result = (*fp)(&i);	/*	an equivalent syntax */

	printf("You entered %d\n", i);
	if (result) {
		printf("You chose wisely!\n");
		}
	else {
		printf("You are inconsistent!\n");
		}
	return;
}

/* these functions ask the user to supply an integer;
they return the integer value using the pointer parameter,
and then return either 1 (true) or 0 (false) depending on
whether the number is odd or even versus even or odd.
*/

int get_odd_int(int * ip)
{
	printf("Enter an integer: ");
	scanf("%d", ip);
	if (*ip % 2)
		return 1;	/* true if odd */
	return 0;
}

int get_even_int(int * ip)
{
	printf("Enter an integer: ");
	scanf("%d", ip);
	if (*ip % 2)
		return 0;
	return 1;	/* true if even */
}
