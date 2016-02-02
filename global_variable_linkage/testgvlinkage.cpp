/*
 *  testgvlinkage.c/.cpp
 
 Compile and link this with A.c/.cpp to experiment with different linkage of gv
 */


#include <stdio.h>

#include "A.h"

/* a global */

/* int gv = 1; */

int main(void)
{
	printf("in main, start: gv = %d\n", gv);
	foo(2);
	printf("in main, finish: gv = %d\n", gv);
	return 0;
}


/*
compile as C, (change to .c), gcc 4.2, -std=c89 -pedantic 
main module			A.h				A.c				Result
1. int gv;			---				int gv;			Build, run, initial value = 0
2. int gv;			---				int gv = 2;		Build, run, initial value = 2
3. int gv = 1;		---				int gv;			Build, run, initial value = 1
4. int gv = 1;		---				int gv = 2;		Link error, duplicate symbol
5. int gv = 2;		---				int gv = 2;		Link error, duplicate symbol
6. int gv = 0;		---				int gv = 0;		Link error, duplicate symbol

7. int gv = 1;		extern int gv;	int gv = 2;		Link error, duplicate symbol
8. int gv;			extern int gv;	int gv = 2;		Build, run, initial value = 2
9. ---				extern int gv;	int gv = 2;		Build, run, initial value = 2 ***

compile as C++, (change to .cpp), gcc 4.2, -ansi -pedantic
1. int gv;			---				int gv;			Link error, duplicate symbol
2. int gv;			---				int gv = 1;		Link error, duplicate symbol
3. int gv = 1;		---				int gv;			Link error, duplicate symbol
4. int gv = 1;		---				int gv = 2;		Link error, duplicate symbol

5. int gv = 1;		extern int gv;	int gv = 2;		Link error, duplicate symbol
6. int gv;			extern int gv;	int gv = 2;		Link error, duplicate symbol
7. ---				extern int gv;	int gv = 2;		Build, run, initial value = 2 ***

Results:
C essentially arranges for the linker to merge all declarations of a global variable
into a single global variable, as long as there is no more than one "defining declaration" 
- a declaration that includes an initialization, which means it is also the point of definition.
Note that static-lifetime variables are default initialized to zero, as in case 1 above,
but initializing both gv's to even the same value, even zero, still causes a link error, 
as in cases 4, 5, 6. This means that the initialized global variables of the same name
are viewed as duplicated symbols, but uninitialized global variables are viewed as referring to 
the same object. If there is only one initialized declaration of gv, it becomes the "real" gv, 
and the other declarations get linked to it. The extern declaration can replace an uninitialized declaration, as shown in case 9.
The C rules is rather subtle and not altogether conceptually clear.

In contrast, C++ is much more clear and stringent. C++ arranges for the linker to report 
an error if there is more than one declaration of a name present, regardless of whether 
it is initialized or not, so the global variable can be declared only once in the whole program. 
The extern declaration then allows other modules to link to it.

Conclusion:
As stated in the Header File Guidelines, set up global variable linkage 
as shown in the *** lines above. This is required in C++, and also works in C,
and is the easiest to keep consistent in C because there are no repeated
declarations.

*/
