#include <algorithm>
#include "sequence.h"

// Reading in a sequence
istream & operator>>(istream & cin, Sequence & s) {
    // Store length
    int length;
    cin >> length;
    s.length = length;

    // Add value to sum_of_squares and add to values vector
    int current;
    int sum = 0;
    for(int i = 0; i < length; i++) {
        cin >> current;
        sum += current*current;
        s.values.push_back(current);
    }
    s.sum_of_squares = sum;
    return cin;
}

// Printing an individual sequence
ostream & operator<<(ostream & cout, const Sequence & s) {
    // Print all the sequence values except the last one
    for(int i = 0; i < s.length-1; i++) {
        cout << s.values[i] << " ";
    }

    // Print last sequence value followed by line break instead of space
    cout << s.values[s.length-1] << endl;
    return cout;
}

int Sequence::getLength() {
    return length;
}

int Sequence::getSum() {
    return sum_of_squares;
}


bool compare_sequence(Sequence a, Sequence b) {
	if( a.getLength() < b.getLength() ) {
		return true;
	} else if( a.getLength() > b.getLength() ) {
		return false;
	} else {
		if( a.getSum() < b.getSum() ) {
			return true;
		} else if( a.getSum() > b.getSum() ) {
			return false;
		} else {
			return true;
		}
	}
}

// Sorting the sequences
void sort_list(vector<Sequence> &seq) {
	sort(seq.begin(), seq.end(), compare_sequence);
}

// Printing a vector of sequences
ostream & operator<<(ostream & cout, const vector<Sequence> & s_list) {
    vector<Sequence>::const_iterator itr;
    for( itr = s_list.begin(); itr != s_list.end(); itr++ ) {
        cout << (*itr);
    }
    return cout;
}
