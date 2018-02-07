#include<iostream>
using namespace std;

bool is_palindrome(string input, int numOfSlots);
string clean_string(string input);

int main(){
    // Read in text
    string s;
    string input;
    do {
        getline(cin, s);
        input += s;
    } while (s.length() > 0);

    // Clean input string (remove punctuation and whitespace and make all lowercase)
    input = clean_string(input);
    cout << input << endl;
    if (is_palindrome(input, input.size()) == true ){
        cout << "Yes";
    }else{
        cout << "No";
    }
    
    return 0;
}

// Implement the is_palindrome() function here...
bool is_palindrome(string input, int numOfSlots) {
	for (int i = 0; i < numOfSlots/2+1; i++) {
		if (input[i] != input[numOfSlots-1-i]) {
			return false;
		}
	}
	return true;
}

string clean_string(string input) {
    string output = "";
    for (int i = 0; i < input.size(); i++) {
        if (input[i] >= '0' && input[i] <= '9') {
            output += input[i];
        } else if (input[i] >= 'a' && input[i] <= 'z') {
            output += input[i];
        } else if (input[i] >= 'A' && input[i] <= 'Z') {
            output += (input[i] - 'A' + 'a');
        }
    }
    return output;
}