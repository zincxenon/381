/*
 *  A.c/,cpp
 */

#include "A.h"
#include <stdio.h>

/* a global */

int gv1 = 2;

void foo(int i)
{
	printf("in foo, i = %d, add to gv1\n", i);
	
	gv1 += i;
	
	return;
}
