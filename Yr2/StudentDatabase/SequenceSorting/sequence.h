
#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <vector>
#include <iostream>
using namespace std;

class Sequence {
private:
    //Define some variable to store this sequence and its length
    int length; // len(S)
    int sum_of_squares; // D(S)
    vector<int> values;
public:
    Sequence(){};
    int getLength();
    int getSum();
    friend istream & operator>>(istream & cin, Sequence & s);
    friend ostream & operator<<(ostream & cout, const Sequence & s);

};

// Reading in a sequence
istream & operator>>(istream & cin, Sequence & s);

// Printing an individual sequence
ostream & operator<<(ostream & cout, const Sequence & s);

// Sorting the sequences
void sort_list(vector<Sequence> &seq);

/* Other Neccessary Defination Here */

// Printing a vector of sequences
ostream & operator<<(ostream & cout, const vector<Sequence> & s_list);

#endif
