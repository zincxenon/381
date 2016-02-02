#include "redirect_io.h"

#include <stdio.h>  
#include <stdlib.h>

/*  *** redirect_io implementation file - C version ***
This function prompts the user for file names and then redirects input and output accordingly. 
It uses an obscure function in the C stdio library, freopen.   
This function requires including <stdio.h> and <stdlib.h> 
Filenames are assumed to be less than 100 characters long. 
*/


void redirect_io(void)
{
	char c;
	char infilename[100];
	char outfilename[100];

	printf("Do you want to redirect I/O? Enter y or n: ");
	scanf(" %c", &c);
	if (c != 'y') /* redirect only if 'y', forget it otherwise */
		return;
	printf("Enter 'i', 'o', or 'b' to redirect input, output, or both: ");
	scanf(" %c", &c);
	
	if(c == 'i' || c == 'b') {
		printf("Enter input file name: ");
		scanf("%99s", infilename);
		}	

	if(c == 'o' || c == 'b') {
		printf("Enter output file name: ");
		scanf("%99s", outfilename);
		}

	if(c == 'i' || c == 'b') {
		printf("Redirecting stdin to come from %s\n", infilename);
		printf("Keyboard input will no longer be processed during program execution.\n");
		if(!freopen(infilename, "r", stdin)) {
			printf("Could not open input file. Terminating program.\n");
			exit(EXIT_FAILURE);
			}
		}
		
	if(c == 'o' || c == 'b') {
		printf("Redirecting stdout to go to %s\n", outfilename);
		printf("Program output will no longer be displayed during program execution.\n");
		if(!freopen(outfilename, "w", stdout)) {
			printf("Could not open output file.  Terminating program.\n");
			exit(EXIT_FAILURE);
			}
		}
}


