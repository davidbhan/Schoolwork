#include <iostream>
using namespace std;

bool isLeapYear(int year) {
	if (year % 400 == 0) {
		return true;
	} else if (year % 4 == 0 && year % 100 != 0) {
		return true;
	}
	return false;
}

int main() {
	int year = 0;

	while (true) {
		cout << "Enter a year (or negative number to quit): ";
		cin >> year;
		if (year < 0) {
			cout << "Bye!" << endl;
			break;
		}
		if (isLeapYear(year)) {
			cout << year << " is a leap year." << endl;
		} else {
			cout << year << " is not a leap year." << endl;
		}
	}


	return 0;
}