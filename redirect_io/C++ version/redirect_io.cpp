#include "redirect_io.h"

#include <cstdio>  // needed for i/o redirection routine
#include <cstdlib>
#include <iostream>
using namespace std;

/*  *** redirect_io implementation file ***
This function prompts the user for file names and then redirects input and output accordingly. 
It uses an obscure function in the C stdio library, freopen, and takes advantage of the fact
that "cin" is identified with the stdio stream named "stdin" and "cout" with the stdio stream named
"stdout".   This function requires including <cstdio> and <cstdlib> 
Filenames are assumed to be less than 100 characters long. 
*/

void redirect_io()
{
	cout << "Do you want to redirect I/O? Enter y or n: ";
	char c;
	cin >> c;
	if (c != 'y') // redirect only if 'y', forget it otherwise
		return;
	char infilename[100];
	char outfilename[100];
	cout << "Enter 'i', 'o', or 'b' to redirect input, output, or both: ";
	cin >> c;
	
	if(c == 'i' || c == 'b') {
		cout << "Enter input file name: ";
		cin >> infilename;
		}	

	if(c == 'o' || c == 'b') {
		cout << "Enter output file name: ";
		cin >> outfilename;
		}

	if(c == 'i' || c == 'b') {
		cout << "Redirecting cin to come from " << infilename << endl;
		cout << "Keyboard input will no longer be processed during program execution." << endl;
		if(!freopen(infilename, "r", stdin)) {
			cout << "Could not open input file. Terminating program." << endl;
			exit(EXIT_FAILURE);
			}
		}
		
	if(c == 'o' || c == 'b') {
		cout << "Redirecting cout to go to " << outfilename << endl;
		cout << "Program output will no longer be displayed during program execution." << endl;
		if(!freopen(outfilename, "w", stdout)) {
			cout << "Could not open output file.  Terminating program." << endl;
			exit(EXIT_FAILURE);
			}
		}
}


