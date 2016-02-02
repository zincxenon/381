#include <iostream>
#include <iomanip>  // needed to use manipulators with parameters (precision, width)
#include <cmath>	// needed for pow function
using namespace std;

int main ()
{
	const int beginvalues = -10;
	const int endvalues = 16;
	const int nvalues = endvalues - beginvalues;
	
	int ipow[nvalues];	
	double ary[nvalues];	// an array for demo values
	
	int ipowindex = 0;
	for (int i = beginvalues; i < endvalues; i++) {	// fill array with interesting range of values
		ipow[ipowindex] = i;
		ary[ipowindex] = pow(3.14159265, i);
		ipowindex++;
		}
		
	// output index and array[index] using default settings
	cout << "Output using default settings" << endl;
	for (int i = 0; i < nvalues; i++)
		cout << ipow[i] << ' ' << ary[i] << endl;
/* 
Output using default settings
-10 1.06783e-05
-9 3.35468e-05
-8 0.00010539
-7 0.000331094
-6 0.00104016
-5 0.00326776
-4 0.010266
-3 0.0322515
-2 0.101321
-1 0.31831
0 1
1 3.14159
2 9.8696
3 31.0063
4 97.4091
5 306.02
6 961.389
7 3020.29
8 9488.53
9 29809.1
10 93648
11 294204
12 924269
13 2.90368e+06
14 9.12217e+06
15 2.86581e+07

Each output double value has either six significant digits or fewer if the value can be 
expressed just as accurately. For example, for ipow = 0, the value of one shows with no
decimal places and not even a decimal point. These are not printed in the default format 
unless there are non-zero places printed to the right of the decimal
point. See also ipow = 10 through 12, where the decimal places have all been rounded off. 
At i = 13 and beyond, 6 digits are not enough, so the output flips into scientific notation,
still showing six significant digits, but with an exponent of ten. A different rule, not
so easy to state, governs when small values flip into scientific notation.
 */		

	// save the current settings
	ios::fmtflags old_settings = cout.flags(); //save previous format flags
	int old_precision = cout.precision();	// save previous precision setting

	// don't need to save width setting, because it automatically resets to default value
	// after each numeric output item.
	
	// just change the precision
	cout << setprecision(8);
	cout << "\nOutput using integers with default output" << endl;
	cout << "doubles in general format, precision 8" << endl;
	for (int i = 0; i < nvalues; i++)
		cout << ipow[i] << ' ' << ary[i] << endl;
	
/*
Output using integers with default output
doubles in general format, precision 8
-10 1.0678279e-05
-9 3.3546804e-05
-8 0.00010539039
-7 0.00033109368
-6 0.0010401615
-5 0.0032677637
-4 0.010265982
-3 0.032251535
-2 0.10132118
-1 0.31830989
0 1
1 3.1415927
2 9.8696044
3 31.006277
4 97.409091
5 306.01968
6 961.38919
7 3020.2932
8 9488.5309
9 29809.099
10 93648.046
11 294204.01
12 924269.17
13 2903677.2
14 9122171
15 28658145

Here up to 8 significant digits are printed, which is enough to avoid the scientific notation
at ipow = 15. The result is still a mess because the values take up different numbers of spaces.

*/

	// change output format settings with member functions
	cout.setf(ios::fixed, ios::floatfield);  // set fixed floating format
	cout.precision(2);  // for fixed format, two decimal places
	// cout << fixed << setprecision(2);  // same effects, but using manipulators
	cout << "\nOutput using integers with width 2," << endl;
	cout << "doubles in fixed format, precision 2, width 8" << endl;
	for (int i = 0; i < nvalues; i++)
		cout << setw(2) << ipow[i] << ' ' << setw(8) << ary[i] << endl;
/*
Output using integers with width 2,
doubles in fixed format, precision 2, width 8
-10     0.00
-9     0.00
-8     0.00
-7     0.00
-6     0.00
-5     0.00
-4     0.01
-3     0.03
-2     0.10
-1     0.32
 0     1.00
 1     3.14
 2     9.87
 3    31.01
 4    97.41
 5   306.02
 6   961.39
 7  3020.29
 8  9488.53
 9 29809.10
10 93648.05
11 294204.01
12 924269.17
13 2903677.23
14 9122171.04
15 28658145.48

All the double values show two places to the right of the decimal point, with the results 
rounded to hundredths (possibly to zero). This output would be quite neat except for two
problems: (1) Since the minus sign counts in the width of the integers, the -10 value won't
fit into two spaces, and this messes up the first line. (2) Starting at ipow = 11, the output
is messed up because the results will not fit into the total space of 8 characters
(the decimal point counts as one space). Note that setting fixed format prevents the flipping 
into scientific notation, and forces the value of exactly one to show with a decimal point
and the specified number of places to the right of the decimal point.
*/

	cout << "\nOutput using integers with width 3 integers, " << endl;
	cout << "doubles in fixed format, precision 0, width 5" << endl;
	// can use manipulators to change precision and others inside an output statement
	// in fixed format, precision of zero means no decimal places
	for (int i = 0; i < nvalues; i++)
		cout << setw(3) << ipow[i] << ' ' << setprecision(0) << setw(5) << ary[i] << endl;

/*
Output using integers with width 3 integers, 
doubles in fixed format, precision 0, width 5
-10     0
 -9     0
 -8     0
 -7     0
 -6     0
 -5     0
 -4     0
 -3     0
 -2     0
 -1     0
  0     1
  1     3
  2    10
  3    31
  4    97
  5   306
  6   961
  7  3020
  8  9489
  9 29809
 10 93648
 11 294204
 12 924269
 13 2903677
 14 9122171
 15 28658145

This gives room for the negative integer values, and so it produces a neat output until 
ipow = 11, whereupon the output takes additional digits just as in the previous example. 
Because the fixed precision is zero, everything is rounded to the nearest integer value, 
and thus neither a decimal point nor places to the right of the decimal point appear.
For values less the one, of course, the result rounds off to zero.
*/

	cout << "\nOutput using integers with width 3 integers, " << endl;
	cout << "doubles in fixed format, precision 8, width 18" << endl;
	cout << setprecision(8);
	for (int i = 0; i < nvalues; i++)
		cout << setw(3) << ipow[i] << ' ' << setw(18) << ary[i] << endl;
		
/*
Output using integers with width 3 integers, 
doubles in fixed format, precision 8, width 18
-10         0.00001068
 -9         0.00003355
 -8         0.00010539
 -7         0.00033109
 -6         0.00104016
 -5         0.00326776
 -4         0.01026598
 -3         0.03225153
 -2         0.10132118
 -1         0.31830989
  0         1.00000000
  1         3.14159265
  2         9.86960438
  3        31.00627657
  4        97.40909059
  5       306.01968304
  6       961.38918698
  7      3020.29320362
  8      9488.53092933
  9     29809.09902689
 10     93648.04640600
 11    294204.01427594
 12    924269.16884980
 13   2903677.22748013
 14   9122171.03582395
 15  28658145.47818740
 
 This output is the first that is completely neat over the whole range of values.
 The width for the doubles leaves enough room for the additional digits to the left
 of the decimal point. Of course, the precision of 8 produces a lots of decimal places
 which we may not need.  
*/	
		

	// restore output format flags and precision
	cout.flags(old_settings);
	cout.precision(old_precision);

	cout << "\nOutput using original settings" << endl;
	for (int i = 0; i < nvalues; i++)
		cout << ipow[i] << ' ' << ary[i] << endl;
/*
Output using original settings
-10 1.06783e-05
-9 3.35468e-05
-8 0.00010539
-7 0.000331094
-6 0.00104016
-5 0.00326776
-4 0.010266
-3 0.0322515
-2 0.101321
-1 0.31831
0 1
1 3.14159
2 9.8696
3 31.0063
4 97.4091
5 306.02
6 961.389
7 3020.29
8 9488.53
9 29809.1
10 93648
11 294204
12 924269
13 2.90368e+06
14 9.12217e+06
15 2.86581e+07
*/
}


