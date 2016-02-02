#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
using namespace std;

typedef map<string,int > Counts_t;
void print_pair(const Counts_t::value_type& count_pair);

int main()
{
    Counts_t counts;
    ifstream f( "map_word_counter_inp.txt" );
    
    cout << "enter a char to start input" << endl;
    char c;
    cin >> c;

    string token;
    int n = 0;

    while (f >> token) {
    	counts[token]++;
    	n++;
        }
    
    cout << n << " tokens processed, " << counts.size() << " unique ones found"<< endl;
    cout << "enter a char to start output of tokens:count results" << endl;
    cin >> c;
    
    for_each(counts.begin(), counts.end(), print_pair);
    return 0;
}


void print_pair(const Counts_t::value_type& count_pair)
{
	// print the information only if the word appeared more than once
	if(count_pair.second > 1)
		cout << count_pair.first << ": " << count_pair.second << endl;
}

