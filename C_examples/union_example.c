/* demonstration of the difference between an union and a struct */

#include <stdio.h>

int main(void)
{
	struct S {
		char c;
		int i;
		double d;
		} s;

	union U {
		char c;
		int i;
		double d;
		} u;

		
	/* The union is a lot smaller, even though the same number
	and types of members are declared. */
	printf("struct S has size %d\n", sizeof(struct S));
	printf("union U has size %d\n", sizeof(union U));
	

	s.c = 'x';
	s.i = 123;
	s.d = 3.14159265;
	/* all three values of the struct are stored separately */
	printf("s contains: %c, %d, %f\n", s.c, s.i, s.d);
	
	/* demo that only the last value stored in the union is well-defined */
	u.c = 'x';
	u.i = 123;
	u.d = 3.14159265;
	/* only the d value makes sense */
	printf("u contains: %c, %d, %f\n", u.c, u.i, u.d);
	
	u.d = 3.14159265;
	u.c = 'x';
	u.i = 123;
	/* only the i value makes sense */
	printf("u contains: %c, %d, %f\n", u.c, u.i, u.d);
	
	u.i = 123;
	u.d = 3.14159265;
	u.c = 'x';
	/* only the c value makes sense */
	printf("u contains: %c, %d, %f\n", u.c, u.i, u.d);
	
		
	return 0;
}