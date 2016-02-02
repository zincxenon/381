 /*
Example of using bsearch to search an array of char *'s for matching string.

The bsearch function is somewhat cryptic, because in order to be generic, it has to refer
to all of the data via void pointers; the sizeof parameter is used internally to figure out 
where each cell of the array is located.
 
Correspondingly, the comparison function is not handed the values in the array cells, 
but rather void pointers to the array cells. To perform the comparison,
these void pointers have to be cast to the right pointer type, and then in this example, 
dereferenced to char * to get the actual values to compare. The bsearch routine returns
a void pointer to the array cell where the matching value was found, or NULL if no
match was found. To access the value in the cell, the void pointer has to be cast
to the right pointer type (char **) in this case, and then dereferenced to get the 
desired char * pointer to the found string.

The qsort function is similarly specified, and so can use the same function as bsearch
for putting the items in order.

This example works with an array containing pointers to C-strings.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* The comparison function gets void pointers to cells that contain a char *
and so the void pointers are actually char ** type.
- verbose version for clarity
*/
int mystrcmp(const void * p1, const void * p2)
{
	char ** ps1 = (char **)p1;
	char * s1 = *ps1;
	char ** ps2 = (char **)p2;
	char * s2 = *ps2;
	return strcmp(s1, s2);
}
/* compact version - rely on implicit conversion from void* arguments */
int mystrcmp2(const char ** p1, const char ** p2)
{
	return strcmp(*p1, *p2);
}

#define ARRAYSIZE 4
int main ()
{
	char * array[ARRAYSIZE];
	/* fill an array out of order of pointers to string literals */
	array[0] = "ccc";
	array[1] = "aaa";
	array[2] = "bbb";
	array[3] = "ddd";
	/* output the unsorted array */
	{int i=0; 
		for(; i<4; i++) 
			printf("%s\n", array[i]); 
	}

	/* sort elements in the array using the comparison function; 
	Pass in a void pointer to the array base
	The function pointer cast is optional if the function takes const void* parameters. 
	*/
	qsort ((void *)array, ARRAYSIZE, sizeof(char *), (int(*)(const void *,const void *)) mystrcmp2);
	/* output the now-sorted array */
	{int i=0; 
		for(; i<4; i++) 
			printf("%s\n", array[i]); 
	}

	while(1) {
		void * result;
		/* a buffer for the searched-for string */
		char buffer[10];
		/* 
		key_ptr is a char * pointing to the key string, so &key_ptr is a char** for the search string,
		which thus match up with the pointers to the array cells as expected by the comparison function.
		*/
		char* key_ptr = buffer; 
	
		printf("Enter a string less than 9 charactes long, \"stop\" to stop:");
		scanf("%9s", buffer);
		if(strcmp(buffer, "stop") == 0)
			return 0;
		/* verbose for clarity*/
		/* Hand in a void pointer to the pointer to the char * for the search string, and a void pointer to the base of the array.
		The function pointer cast is optional if the function takes const void* parameters. 
		The result is NULL or a void pointer to the cell containing the matching char * 
		*/ 
		result = bsearch ((void *)&key_ptr,(void *) array, ARRAYSIZE, sizeof(char *), (int(*)(const void *,const void *)) mystrcmp2);
		if (result) {
			/* result is a void * pointer to the array cell that was found.
			cast as a pointer to an char *, and then dereference it. */
			char ** found_item_ptr = (char **)result;
			printf ("Found %s in the array.\n", *found_item_ptr);
			}
		else
			printf ("Not found!\n");
		}
}

