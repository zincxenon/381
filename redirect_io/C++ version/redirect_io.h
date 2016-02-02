
#ifndef REDIRECT_IO_H
#define REDIRECT_IO_H

/*  *** redirect_io header file ***

Multiple-source-file version of the redirect_io facility.

This function prompts the user for file names and then redirects input and output accordingly. 
It uses an obscure function in the C stdio library, freopen, and takes advantage of the fact
that "cin" is identified with the stdio stream named "stdin" and "cout" with the stdio stream named
"stdout".   This function requires including <stdio.h> and <stdlib.h> 
Filenames are assumed to be less than 100 characters long. 

To use this facility, put in your main source code a #include of this file, 
add redirect_io.cpp to your project, and then put the following function call 
in main(), near the beginning, BEFORE any i/o to cin/cout:

	redirect_io();
	
Note that once i/o is redirected to a file, the keyboard and/or the display will no longer
be connected to the program.  You will have to let the program finish running and start it
again before you can do normal keyboard/screen i/o.

*/

void redirect_io();

#endif
