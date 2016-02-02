/* demo of what's legal when converting to/from void pointers. Try this with your C compiler */

#include <stdio.h>

int main(void)
{
	struct S1 {
		char c;
		int i;
		int j;
		} s1;
		
	struct S2 {
		char c;
		double d;
		} s2;
	
	void * void_ptr = 0;
	
	struct S1 * S1_ptr = &s1;
	struct S2 * S2_ptr = &s2;

	int i = 3;
	int * int_ptr = &i;
	double d = 3.14;
	double * double_ptr = &d;
	char c = 'x';
	char * char_ptr = &c;
	
/* Start without pointers. The compiler will let you copy one kind of object into 
another if they have a known and well defined relationship - like numeric types. 
So the following are legal "implicit" conversions. */

	i = s2.d;
	s2.d = i;
	i = c;
	s2.d = s1.c;	/* chars are actually just a one-byte int in C */
		
	
/* But the compiler doesn't know the meanings of user-defined (struct) types, 
so how could it meaningfully convert one into the other? Even the cast doesn't
make sense, so it is disallowed; the following are all illegal. */

	s1 = s2;
	
	s1 = (struct S1) s2;
	
	i = (int) s1;

	
/* The following are illegal for much of the same reason - 
pointers are not interchangable if they point to different kinds of objects. */

	S1_ptr = S2_ptr;
	
	S1_ptr = int_ptr;
	
	int_ptr = S1_ptr;
	
/* Even when the pointed-to objects have legal "implicit" conversions, this doesn't
mean that the pointers are implicitly convertible. Among other issues, note 
that a double might have to reside at a certain set of addresses
due to alignment issues, that int's don't necessarily share. So all of the following 
are illegal in Standard C. */
	
	int_ptr = double_ptr;
	double_ptr = int_ptr;
	int_ptr = char_ptr;


/* Likewise, integers and address are different kinds of things, so even though 
addresses are integral values, the following are all illegal. */
	
	int_ptr = 360;
	
	i = int_ptr;
	
	void_ptr = 360;
	
/* HOWEVER, you can coerce the compiler to convert the pointer type with a cast, but that doesn't
mean that the result is meaningful - you are telling the compiler that you know that the pointed-to
data come be meaningfully interpreted as the other kind of object.  The following are all legal, but
it is up to you whether they are actually meaningful or correct. */

	int_ptr = (int *) 360;
	
	S1_ptr = (struct S1 *)S2_ptr;
	
	S1_ptr = (struct S1 *)int_ptr;

	void_ptr = (void *) 360;
		
	
/* void pointers in C are special because you can freely assign other pointers to and from
without the use of a cast  - but again, you better be right! */
	
	void_ptr = int_ptr;
	
	S1_ptr = void_ptr;
	
	void_ptr = S1_ptr;
	
	int_ptr = void_ptr;
	
	return 0;
}