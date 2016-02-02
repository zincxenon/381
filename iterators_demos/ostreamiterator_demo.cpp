#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>


using namespace std;

void print(int i)
{
	cout << i << endl;
}

int main()
{
	vector<int> vi;
	
	for(int i = 0; i < 10; i++) {
		vi.push_back(10 * (i+1));
		}
	cout << "print with a for_each calling a function:" << endl;
	for_each(vi.begin(), vi.end(), print);
	
	cout << "print with an output stream iterator that separates with colons:" << endl;
	// create an output stream iterator - the stream followed by a delimiter character
	ostream_iterator<int> outiter(cout, ":");
	// write the integers with a ':' after each one
	copy(vi.begin(), vi.end(), outiter);
	cout << endl;

	// write the integers one per line
	cout << "print with an output stream iterator that puts on separate lines:" << endl;
	copy(vi.begin(), vi.end(), ostream_iterator<int>(cout, "\n"));

}



