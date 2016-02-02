//
//  isspaceTemplateParameter.cpp
//

#include <cctype>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::isspace;
using std::istream;
using std::string;
using std::getline;

template<typename F>
void change_space_to_dollar(string& s, F f)
{
	for(int i = 0; i < s.length(); i++)
		if(f(s[i]))
			s[i] = '$';
}

bool isspace_wrapper(char c)
{
	return isspace(c);
}

bool isspace_locale_wrapper(char c)
{
	return std::isspace(c, std::locale("C"));
}


int main()
{
	string s;
	getline(cin, s);
	cout << s << endl;
/*
	for(int i = 0; i < s.length(); i++) 
//		if(isspace(s[i]))  // works as is, no problem
		if(isspace(s[i], std::locale("C"))) // works as is, no problem 
			s[i] = '$';
*/
//	the following fails becase the compiler can't figure out which
//  "isspace" to use to determine the template parameter type - it's ambiguous - 
//	change_space_to_dollar(s, isspace); // fails to compile

	// all of the following work - because there is no ambiguity
	
	// the wrapper functions have unique names
//	change_space_to_dollar(s, isspace_wrapper);
//	change_space_to_dollar(s, isspace_locale_wrapper);

	// the casts tell the compiler what the type of isspace is
	// like in ctype.h, these functions take and return an int
//	change_space_to_dollar(s, (int (*)(int))isspace);
//	change_space_to_dollar(s, static_cast<int (*)(int)>(isspace));

	// we can tell the compiler what the template type is
    change_space_to_dollar<int (*)(int)>(s, isspace);

	
	cout << s << endl;
}


