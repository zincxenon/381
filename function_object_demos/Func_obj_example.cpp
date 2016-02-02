#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// a function object class that calculates a mean, accumulating every supplied value

class Calc_Mean {
public:
	Calc_Mean() : sum(0.), n(0) {}
	void operator() (double x)	// accumulate the supplied value
		{
			n++;
			sum += x;
		}
	double get_mean() const
		{return sum / double(n);}
	int get_n() const
		{return n;}
private:
	double sum;
	int n;
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
	cout << "Enter a bunch of values, ^D (EOF) when done:" << endl;
	
	double x;
	Calc_Mean cm;
	
	while (cin >> x)
		cm(x);	// use like an ordinary function
		
	cout << endl;
	cout << "mean of " << cm.get_n() << " values is " << cm.get_mean() << endl;
}

void test2()
{
	cout << "Enter a bunch of values, ^D (EOF) when done:" << endl;
	vector<double> data;
	double x;
	while (cin >> x)
		data.push_back(x);  
		
	// use with an algorithm
	Calc_Mean cm = for_each(data.begin(), data.end(), Calc_Mean());
	
	cout << endl;
	cout << "mean of " << cm.get_n() << " values is " << cm.get_mean() << endl;
}
