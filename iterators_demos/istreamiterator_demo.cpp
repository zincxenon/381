#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>


using namespace std;

int main()
{
	ifstream input_file("data.txt");	// whitespace separated integers

	vector<int> vi;
	// read a bunch of ints until end of file, fill the vector
	istream_iterator<int> initer(input_file);
	// default ctor'd stream input iterator works  as end of file "end" value.
	istream_iterator<int> eofiter;

	copy(initer, eofiter, back_inserter(vi));
	// now output it with an ostream iterator:
	// write the integers one per line
	cout << "first read of data:" << endl;
	copy(vi.begin(), vi.end(), ostream_iterator<int>(cout, "\n"));
	
	input_file.clear();				// clear the EOF state
	input_file.close();				// close and re-open the file
	input_file.open("data.txt");

	// as a one-liner -- read the data a second time, adding it to the end
	copy(istream_iterator<int>(input_file), istream_iterator<int>(), back_inserter(vi));
	
	// now output it with an ostream iterator:
	// write the integers one per line
	cout << "after second read of data:" << endl;
	copy(vi.begin(), vi.end(), ostream_iterator<int>(cout, "\n"));

}



