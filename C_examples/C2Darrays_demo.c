/*
This demonstrates some of the facts, both reasonable and kinky, about 2-dimensional arrays in C (also applies to built-in arrays in C++). 
We use sizeof() to show what the compiler knows about the array declaration currently in scope. For example, this demonstrates how the 2D array is laid out in memory as a contiguous block that you in fact can access as a 1D array if you want, using a pointer to the first cell.

In addition, if you use a 2D array as a function argument, what is actually handed into the function is still a pointer to the first cell. If the function needs to treat this as a two-dimensional array with subscripting, you have to specify the size of each row (the number of columns) so that the compiler can generate subscripting code that divides up the block of memory into the correct rows and columns. The syntax requires that you do with with an array declaration for the function parameter. This doesn't change how the array is passed in (it is still a pointer - see the sizeof() results).  To make the point, we hand a 3X5 array into a function that assumes its parameter is a 3X3 array; the result is confused.

If you want to explore multidimensional arrays in C, download this code, build it, and play with it - try adding a 3D array.
*/

#include <stdio.h>

#define NROWS 3
#define NCOLS 5

/* functions that take array arguments */
void print1darray(int* x, int n); /* specify number of cells to print */
void print2darray(int x[][NCOLS]);
void bad_print2darray(int x[][3]);


int main(void)
{
    int a[NROWS][NCOLS];
    
    /* output sizes known in the scope of this declaration */
    /* %ld is for a long int to represent sizeof value on this machine */
    printf("sizeof(int) = %ld\n", sizeof(int));
    printf("sizeof(int*) = %ld\n", sizeof(int*));
    printf("size of whole array: sizeof(a) = %ld\n", sizeof(a));
    printf("size of first row or subarray: sizeof(a[0]) = %ld\n", sizeof(a[0]));
    printf("size of a single cell: sizeof(a[0][0]) = %ld\n", sizeof(a[0][0]));

    /* fill with values showing row and column */
    {
        int irow, icol;
        for(irow = 0; irow < NROWS; irow++)
            for(icol = 0; icol < NCOLS; icol++)
                a[irow][icol] = irow*10 + icol; /* first digit is row, second is column */
        /* echo print the result in row/column layout */
        printf("\nRow and Column contents of a:\n");
        for(irow = 0; irow < NROWS; irow++) {
            for(icol = 0; icol < NCOLS; icol++) {
                printf("%3d", a[irow][icol]);
                }
            printf("\n");
            }

    }
    
    /* demostrate that the 2D array is a single continguous bloch of memory */
    {
        int* p;
        int i;
        /* output the NROWS*NCOLS integers starting at that address */
        printf("\nOutput contents of a assuming a single block of memory:\n");
        /* point to first cell with an int* */
        p = &a[0][0];
        for(i = 0; i < NROWS*NCOLS; i++) {
            printf(" %d", *p);
            p++;
            }
        printf("\n");
       /* do the same thing only with subscripts */
       /* point to first cell with an int* */
        p = &a[0][0];
        printf("\nOutput contents of a as if it was a 1D array:\n");
        for(i = 0; i < NROWS*NCOLS; i++) {
            printf(" %d", p[i]);
            }
        printf("\n");
    }
    
    /* Demonstrate that we can use a row of a as a 1d array parameter.
    This unique (and somewhat useful) ability to specify subarrays is due to C's "array of arrays" concept. */
    printf("\nCall print1darray(a[1], NCOLS);\n");
    print1darray(a[1], NCOLS);
 
    /* demonstrate that we can use the 2d array as a 1d array parameter, since the 2d array name
    decays to an int* just like a 1d array would. */
    printf("\nCall print1darray(a, NROWS*NCOLS);\n");
    print1darray(a, NROWS*NCOLS);

    
    /* give a to a function that is expecting a 2d array of same row size. */
    printf("\nCall print2darray(a);\n");
    print2darray(a);
    
    /* demonstrate that since a goes in as a pointer to first cell, we can call a function that assumes
    a 2d array of the wrong size. This gives a warning in in Xcode 4.5.2 with Clang and c89 */
    printf("\nCall bad_print2darray(a);\n");
    bad_print2darray(a);

    return 0;
}
/* Because the array is passed in a pointer to the first cell, this is an equivalent declaration:
void print1darray(int* x, int n) */
void print1darray(int x[], int n) /* specify number of cells to print */
{
    int i;
    printf("in print1darray\n");
    /* output sizes known in the scope of this declaration */
    /* %ld is for a long int to represent sizeof value on this machine */
    printf("sizeof(int) = %ld\n", sizeof(int));
    printf("sizeof(int*) = %ld\n", sizeof(int*));
    /* The array is just a pointer! */
    printf("size of whole array: sizeof(x) = %ld\n", sizeof(x));
    printf("size of a single cell: sizeof(x[0]) = %ld\n", sizeof(x[0]));
    printf("%d cells of x treated as 1d array:\n", n);
    for(i=0; i < n; i++)
        printf(" %d", x[i]);
    printf("\n");
}

/* The declaration of x here does not change how x is passed in as a pointer to the first cell.
However, it does tell the compiler how big each row is, so it can compute subscripts correctly. */
void print2darray(int x[][NCOLS])
{
    int irow, icol;
    printf("in print2darray\n");
    /* output sizes known in the scope of this declaration */
    /* %ld is for a long int to represent sizeof value on this machine */
    printf("sizeof(int) = %ld\n", sizeof(int));
    printf("sizeof(int*) = %ld\n", sizeof(int*));
    /* The array is just a pointer! */
    printf("size of whole array: sizeof(x) = %ld\n", sizeof(x));
    /* But we have told the compiler how big each row is! */
    printf("size of first row or subarray: sizeof(x[0]) = %ld\n", sizeof(x[0]));
    printf("size of a single cell: sizeof(x[0][0]) = %ld\n", sizeof(x[0][0]));
    printf("Row and Column contents of x:\n");
    for(irow = 0; irow < NROWS; irow++) {
        for(icol = 0; icol < NCOLS; icol++)
            printf("%3d", x[irow][icol]);
        printf("\n");
        }
}

/* This declaration of x causes the compiler to generate incorrect subscripting code
if the supplied array is actually a different row size. */
void bad_print2darray(int x[][3])
{
    int irow, icol;
    printf("in bad_print2darray\n");
    /* output sizes known in the scope of this declaration */
    /* %ld is for a long int to represent sizeof value on this machine */
    printf("sizeof(int) = %ld\n", sizeof(int));
    printf("sizeof(int*) = %ld\n", sizeof(int*));
    /* The array is just a pointer! */
    printf("size of whole array: sizeof(x) = %ld\n", sizeof(x));
    /* But we have told the compiler how big each row is! */
    printf("size of first row or subarray: sizeof(x[0]) = %ld\n", sizeof(x[0]));
    printf("size of a single cell: sizeof(x[0][0]) = %ld\n", sizeof(x[0][0]));
    printf("Row and Column contents of x:\n");
    for(irow = 0; irow < NROWS; irow++) {
        for(icol = 0; icol < 3; icol++) /* print out the declared number of columns */
            printf("%3d", x[irow][icol]);
        printf("\n");
        }
}

/* Output using Xcode 4.5.2 with Clang and c89; Mac OS X 10.8.2; built as 64-bit.

sizeof(int) = 4
sizeof(int*) = 8
size of whole array: sizeof(a) = 60
size of first row or subarray: sizeof(a[0]) = 20
size of a single cell: sizeof(a[0][0]) = 4

Row and Column contents of a:
  0  1  2  3  4
 10 11 12 13 14
 20 21 22 23 24

Output contents of a assuming a single block of memory:
 0 1 2 3 4 10 11 12 13 14 20 21 22 23 24

Output contents of a as if it was a 1D array:
 0 1 2 3 4 10 11 12 13 14 20 21 22 23 24

Call print1darray(a[1], NCOLS);
in print1darray
sizeof(int) = 4
sizeof(int*) = 8
size of whole array: sizeof(x) = 8
size of a single cell: sizeof(x[0]) = 4
5 cells of x treated as 1d array:
 10 11 12 13 14

Call print1darray(a, NROWS*NCOLS);
in print1darray
sizeof(int) = 4
sizeof(int*) = 8
size of whole array: sizeof(x) = 8
size of a single cell: sizeof(x[0]) = 4
15 cells of x treated as 1d array:
 0 1 2 3 4 10 11 12 13 14 20 21 22 23 24

Call print2darray(a);
in print2darray
sizeof(int) = 4
sizeof(int*) = 8
size of whole array: sizeof(x) = 8
size of first row or subarray: sizeof(x[0]) = 20
size of a single cell: sizeof(x[0][0]) = 4
Row and Column contents of x:
  0  1  2  3  4
 10 11 12 13 14
 20 21 22 23 24

Call bad_print2darray(a);
in bad_print2darray
sizeof(int) = 4
sizeof(int*) = 8
size of whole array: sizeof(x) = 8
size of first row or subarray: sizeof(x[0]) = 12
size of a single cell: sizeof(x[0][0]) = 4
Row and Column contents of x:
  0  1  2
  3  4 10
 11 12 13
*/
