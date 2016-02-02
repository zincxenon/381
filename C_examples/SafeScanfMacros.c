/* demonstration of using macros in C to create a "safe" formatting string for
reading characters into a C-string. */

#include <stdio.h>
#define INPUTLENGTH 7
#define ARRAYLENGTH INPUTLENGTH + 1
/* We need two function-style macros to deal with how macro "expansion" works. 
STRINGIFYHELPER uses the preprocessor "stringify" operator to turn the supplied argument 
into a string literal. 
When the preprocessor sees STRINGIFY with an argument that is also preprocessor symbol,
it replaces the argument symbol first and then expands the STRINGIFYHELPER macro, which
thus gets the "value" of STRINGIFY's argument instead of its "name".
*/
#define STRINGIFYHELPER(x) #x
#define STRINGIFY(x) STRINGIFYHELPER(x)

/* These allow us to define two different versions of a higher-level macro that
expand into scanf calls with a format string containing the maximum input length.
The first is given only the array name, and applies the INPUTLENGTH symbol.
The second accepts a symbol for the input length and uses its "value" in the format string.

The trick these rely on is that a Standard C compiler will concatenate a series of string
literals into a single string literal automatically. E.g. "a" "b" "c" => "abc"
So the scanf format string is "assembled" from a series of literals, one of which is the
stringified value of the maximum length symbol. 

See the sample outputs below for examples of how this works:
*/
#define SAFESCANF(array_name) scanf("%" STRINGIFY(INPUTLENGTH) "s", array_name)
#define SAFESCANF2(array_name, length) scanf("%" STRINGIFYHELPER(length) "s", array_name)

int main (void) {
	/* use our symbol to declare the correct array size */
	char str[ARRAYLENGTH];
	
	/* Examples of stringification - constructing a "%Ns" string where N is what we want */
	/* concatenate "%" with "DOG" with "s" */
	printf("%s\n", "%" STRINGIFYHELPER(DOG) "s");
	/* concatenate "%" with "7" with "s" - what we want, but
	we don't want to have to write the "magic number" here! That's the whole point! */
	printf("%s\n", "%" STRINGIFYHELPER(7) "s");
	/* produces "%INPUTLENGTHs" - not what we want!*/
	printf("%s\n", "%" STRINGIFYHELPER(INPUTLENGTH) "s");
	/* OK, CAT gets stringified - same result as with DOG above */
	printf("%s\n", "%" STRINGIFY(CAT) "s");
	/* INPUTLENGTH gets rewritten to 7, and this gets stringified - what we want! */
	printf("%s\n", "%" STRINGIFY(INPUTLENGTH) "s");
	
	/* use our constructed format string! */
	printf("\nenter a string:");
	scanf("%" STRINGIFY(INPUTLENGTH) "s", str);
	printf("%s", str);
	while(getchar() != '\n');	/* skip rest of line */
	
	/* Use the higher-level macros instead. These will only be "safe" 
	if we are consistent - making sure the array has the size assumed by these macros! */
	printf("\nenter a string:");
	SAFESCANF(str);
	printf("%s", str);
	while(getchar() != '\n');	/* skip rest of line */
	
	printf("\nenter a string:");
	SAFESCANF2(str, INPUTLENGTH);
	printf("%s", str);
	while(getchar() != '\n');	/* skip rest of line */
	
    return 0;
}
/* Output with a sample input:
%DOGs
%7s
%INPUTLENGTHs
%CATs
%7s

enter a string:0123456789
0123456
enter a string:0123456789
0123456
enter a string:0123456789
0123456
*/

/* The preprocessor output for the above - omitting the results of the #includes of the Library headers: 
int main (void) {

 char str[7 + 1];



 printf("%s\n", "%" "DOG" "s");


 printf("%s\n", "%" "7" "s");

 printf("%s\n", "%" "INPUTLENGTH" "s");

 printf("%s\n", "%" "CAT" "s");

 printf("%s\n", "%" "7" "s");


 printf("\nenter a string:");
 scanf("%" "7" "s", str);
 printf("%s", str);
 while(getchar() != '\n');



 printf("\nenter a string:");
 scanf("%" "7" "s", str);
 printf("%s", str);
 while(getchar() != '\n');

 printf("\nenter a string:");
 scanf("%" "7" "s", str);
 printf("%s", str);
 while(getchar() != '\n');

    return 0;
}
*/
