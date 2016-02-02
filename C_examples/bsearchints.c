/*
Example of using bsearch to search an array of int's for matching int value.

The bsearch function is somewhat cryptic, because in order to be generic, it has to refer
to all of the data via void pointers; the sizeof parameter is used internally to figure out 
where each cell of the array is located. 
Correspondingly, the comparison function is not handed the values in the array cells, 
but rather void pointers to the array cells. To perform the comparison,
these void pointers have to be cast to the right pointer type, and then in this example, 
dereferenced to ints to get the actual values to compare. The bsearch routine returns
a void pointer to the array cell where the matching value was found, or NULL if no
match was found. To access the value in the cell, the void pointer has to be cast
to the right pointer type (int *) in this case, and then dereferenced to get the 
integer.
*/
#include <stdio.h>
#include <stdlib.h>

int compfunc (const void * p1, const void * p2)
{
  /* verbose for clarity - cast to the right pointer type, 
  then dereference  and compare */
  int * ip1 = (int *)p1;
  int * ip2 = (int *)p2;
  int i1 = *ip1;
  int i2 = *ip2;
  return i1 - i2;
  /* compact */
  /* return  *(int*)p1 - *(int*)p2; */
}

#define ARRAYSIZE 6

int main ()
{
	/* The array consists of integer-sized cells containing integer values,
	initialized into ascending order. */
	int array[ARRAYSIZE] = {10, 20, 30, 40, 50, 60};
	
	void * result;
	int key;
  
  while(1) {
	printf("Enter an int, 99 to stop:");
	scanf("%d", &key);
	if(key == 99)
		return 0;
	/* verbose for clarity*/
	/* hand in a void pointer to the searched-for value, and a void pointer to the base of the array */
	result = bsearch ((void *)&key, (void *)array, ARRAYSIZE, sizeof(int), compfunc);
	if (result) {
		/* result is a void * pointer to the array cell that was found.
		cast as a pointer to an int, and then dereference it. */
		int * found_item_ptr = (int *)result;
		printf ("Found %d in the array.\n", *found_item_ptr);
		}
	else
		printf ("Not found!\n");
	}
}