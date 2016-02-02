#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// a function object class that calculates a mean, accumulating every supplied value,
// but it takes an optional baseline value when initialized that is subtracted 
// from every value
class Calc_Mean {
public:
	Calc_Mean(double in_baseline = 0.) : sum(0.), n(0), baseline(in_baseline) {}
	void operator() (double x)	// accumulate the supplied value
		{
			n++;
			x = x - baseline;
			sum += x;
		}
	double get_mean() const
		{return sum / double(n);}
	int get_n() const
		{return n;}
private:
	double sum;
	int n;
	double baseline;
};

// prototypes
void test1();
void test2();


int main()
{
	// test1();
	test2();
}


void test1()
{
	double b;
	cout << "Enter baseline value:";
	cin >> b;	// no error check
	cout << "Enter a bunch of values, ^D (EOF) when done:" << endl;
	
	Calc_Mean cm(b);
	
	double x;
	while (cin >> x)
		cm(x);	// use like an ordinary function
	cout << endl;
	
	cout << "mean of " << cm.get_n() << " values is " << cm.get_mean() << endl;
}

void test2()
{
	double b;
	cout << "Enter baseline value:";
	cin >> b;	// no error check

	cout << "Enter a bunch of values, ^D (EOF) when done:" << endl;
	vector<double> data;
	double x;
	while (cin >> x)
		data.push_back(x);
	
	// use with an algorithm
	Calc_Mean cm = for_each(data.begin(), data.end(), Calc_Mean(b));
	cout << endl;
	cout << "mean of " << cm.get_n() << " values is " << cm.get_mean() << endl;
}
		
/*
Enter baseline value: 10
Enter a bunch of values, ^D (EOF) when done:
10 20 30

mean of 3 values is 10
*/
