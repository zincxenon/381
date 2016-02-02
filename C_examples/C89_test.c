/* 
If you have compiler options set for C89 or C90 Standard plus recommended -Wmissing-prototypes
"safety" option, this program should not compile for three reasons commented below.
Note that gcc 3.3 defaults to gnu89, which incorporates some C99 features but is not safer. 

Our gcc settings are -ansi -pedantic -Wmissing-prototypes -Wall
This does not ensure perfect enforcement of C89 or C90 Standard, but comes close.
Try removing the problems one at a time to see effect of each with our gcc settings.
*/

#include <stdio.h>

/* We use a "safety" option -Wmissing-prototypes because prior declaration of a function 
with a prototype is not required, often resulting in dangerous call mismatches. */
/* void foo(void); */


int main(void)
{
	printf("Hello, there!\n");
	/* Can't have declarations mixed with executable code in C89/90 
	These need to be moved to the start of the block. */
	int i =2;
	int j = i + 3;
	printf("j is %d\n", j);
	/* function called but no prototype has appeared - legal but dangerous in C89/90
	use -Wmissing-prototypes to catch it, and the above prototype to prevent it. */
	foo();
	/* C++ style comment is not legal in C89/90 */
	// this is a C++ style comment
	return 0;
}

void foo(void)
{
	printf("I am foo!\n");
}

