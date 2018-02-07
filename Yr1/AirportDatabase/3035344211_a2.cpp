#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
using namespace std;

//Structures
struct Promo { //Used to keep track of active promotions
	string destination;
	string airline;
	int fromDate;
	int toDate;
	int endDate;
	int price;
	int quota;
	int searchNum;
	bool deleteMe;
};

struct Airport { //Used for keeping track of purchase history
	string destination;
	string country;
	int tickets;
	int revenue;
};

struct Country { //Only used for generation most.txt
	string country;
	int tickets;
	int revenue;
};

//*******************************MAIN FUNCTIONS*******************************//
void initializePromos(Promo promos[], int& promosLength); //Fills promos[] from promos.txt, or mainDB.csv (if promos.txt doesn't exist)
void initializeAirports(Airport airports[], int& airportsLength); //Fills airports[] from airportsales.txt (or airportcode.txt if DNE)
void upsert(string oldInfo, string newInfo, Promo promos[], int& promosLength);
void updateArray(Promo promos[], int& promosLength); //Removes all elements with deleteMe flagged as true, shifts positions, updates promoLength
void addPromo(string fileName, Promo promos[], int& promosLength); //Reads in data from file with fileName and updates promos[]
void today(int date, Promo promos[], int& promosLength); //Loops through promos[] and flags all elements that need to be deleted with deleteMe = true
void clear(Promo promos[], int& promosLength); //Sets all searchNum to -1
void searchDest(string dest, Promo promos[], int& promosLength); //loops through promos[] by checking destination and assigns searchNum
void searchDate(int date, Promo promos[], int& promosLength); //loops through promos[] by comparing fromDate and endDate values
void preferAirline(string airline, Promo promos[], int& promosLength); //loops through promos[] by checking airline and updates searchNum
void noAirline(string airline, Promo promos[], int& promosLength); //loops through promos[] by checking airline and updates searchNum
void buyk(int k, int n, Promo promos[], int& promosLength, Airport airports[], int& airportsLength); //finds searchNum == k, buys if able, updates airports[]
void buy(string info, int n, Promo promos[], int& promosLength, Airport airports[], int& airportsLength); //finds match in promo[], updates airports[]
void most(Airport airports[], int& airportsLength); //Creates countries[] and adds data from airports[] to the countries[] to calculate max no. of tickets
void all(Promo promos[], int& promosLength, Airport airports[], int& airportsLength); //displays all active promos[] and the airports[]
void end(Promo promos[], int& promosLength, Airport airports[], int& airportsLength); //writes out data from promos[] and airports[] to files for saving

//******************************HELPER FUNCTIONS******************************//
string getSpaceTerm(string line, int n); //Returns the term after n number of spaces in a string (used for reading user input)
string getCommaTerm(string line, int n); //Returns the term after n number of commas in a string (used for reading csv files)
string getHyphenTerm(string line, int n); //Returns the term after n number of hyphens in a string (used for buy input format)
int stringToDate(string d); //Converts string in (YYYY mon DD) form to an int in YYYYMMDD form
int stringToInt(string s); //Converts a string to int
string intToString(int i); ////Converts int to string

int main() {
	int promosLength = 0;
	int airportsLength = 0;
	Promo promos[500];
	Airport airports[200];

	initializePromos(promos, promosLength); //Initializes promos
	initializeAirports(airports, airportsLength); //Initializes airports
	updateArray(promos, promosLength); //Deletes any promotion with quota <= 0 (one of the test files had initial quota = 0)

	string input = "";
	string command = "";

	while(input != "end") {
		getline(cin, input);
		if(input.find("upsert") == 0) {
			string oldInfo;
			string newInfo;
			oldInfo = getSpaceTerm(input, 1);
			newInfo = getSpaceTerm(input, 3);
			upsert(oldInfo, newInfo, promos, promosLength);
		} else if(input.find("add promo") == 0) {
			string fileName;
	 		fileName = getSpaceTerm(input, 2);
	 		addPromo(fileName, promos, promosLength);
		} else if(input.find("all") == 0) {
			all(promos, promosLength, airports, airportsLength);
		} else if(input.find("today") == 0) {
			string sdate;
	 		int date;
	 		sdate = getSpaceTerm(input, 1);
	 		date = stringToInt(sdate);
	 		today(date, promos, promosLength);
	 		updateArray(promos, promosLength); //Handles array element deletion
		} else if(input.find("clear") == 0) {
			clear(promos, promosLength);
		} else if(input.find("search dest") == 0) {
			string dest;
	 		dest = getSpaceTerm(input, 2);
	 		searchDest(dest, promos, promosLength);
		} else if(input.find("search date") == 0) {
			string sdate;
	 		int date;
	 		sdate = getSpaceTerm(input, 2);
	 		date = stringToInt(sdate);
	 		searchDate(date, promos, promosLength);
		} else if(input.find("prefer airline") == 0) {
			string airline;
	 		airline = getSpaceTerm(input, 2);
	 		preferAirline(airline, promos, promosLength);
		} else if(input.find("no airline") == 0) {
			string airline;
	 		airline = getSpaceTerm(input, 2);
	 		noAirline(airline, promos, promosLength);
		} else if(input.find("buy #") == 0) {
			string sk, sn;
	 		int k, n;
	 		sk = getSpaceTerm(input, 1);
	 		sk = sk.substr(1,sk.length()-1);
	 		sn = getSpaceTerm(input, 2);
	 		k = stringToInt(sk);
	 		n = stringToInt(sn);
	 		buyk(k, n, promos, promosLength, airports, airportsLength);
	 		updateArray(promos, promosLength); //Handles array element deletion
		} else if(input.find("buy") == 0) {
			string info, sn;
	 		int n;
	 		info = getSpaceTerm(input, 1);
	 		sn = getSpaceTerm(input, 2);
	 		n = stringToInt(sn);
	 		buy(info, n, promos, promosLength, airports, airportsLength);
	 		updateArray(promos, promosLength); //Handles array element deletion
		} else if(input.find("most") == 0) {
			most(airports, airportsLength);
		} else if(input.find("end") == 0) {
			end(promos, promosLength, airports, airportsLength);
		} else {
			cout << "Please enter a recognized command" << endl;
		}		
	}
	return 0;
}

void initializePromos(Promo promos[], int& promosLength) {
	ifstream fin;
	fin.open("promos.txt");
	if(!fin.fail()) {
		cout << "Reading from promos.txt" << endl;
		string titles;
		getline(fin, titles);
		int i = 0;
		string temp;
		while(fin.good()) {
			getline(fin, promos[i].destination, ',');
			getline(fin, promos[i].airline, ',');
			getline(fin, temp, ',');
			promos[i].fromDate = stringToInt(temp);
			getline(fin, temp, ',');
			promos[i].toDate = stringToInt(temp);
			getline(fin, temp, ',');
			promos[i].price = stringToInt(temp);
			getline(fin, temp, ',');
			promos[i].endDate = stringToInt(temp);
			getline(fin, temp);
			promos[i].quota = stringToInt(temp);
			promos[i].searchNum = 0;
			promos[i].deleteMe = false;
			//cout << promos[i].destination << "," << promos[i].airline << "," << promos[i].fromDate << "," << promos[i].toDate << "," << promos[i].price << "," << promos[i].endDate  << "," << promos[i].quota<< endl;
			i++;
			promosLength++;
		}		
	} else if(fin.fail()) {
		cout << "Reading from mainDB.csv" << endl;
		fin.open("mainDB.csv");
		string titles;
		getline(fin, titles);
		int i = 0;
		string temp;
		while(fin.good()) {
			getline(fin, promos[i].destination, ',');
			getline(fin, promos[i].airline, ',');
			getline(fin, temp, ',');
			promos[i].fromDate = stringToInt(temp);
			getline(fin, temp, ',');
			promos[i].toDate = stringToInt(temp);
			getline(fin, temp, ',');
			promos[i].price = stringToInt(temp);
			getline(fin, temp, ',');
			promos[i].endDate = stringToInt(temp);
			getline(fin, temp);
			promos[i].quota = stringToInt(temp);
			promos[i].searchNum = 0;
			promos[i].deleteMe = false;
			//cout << promos[i].destination << "," << promos[i].airline << "," << promos[i].fromDate << "," << promos[i].toDate << "," << promos[i].price << "," << promos[i].endDate  << "," << promos[i].quota<< endl;			
			i++;
			promosLength++;
		}			
	}
	fin.close();
	cout << "Number of promos: " << promosLength << endl;	
	return;
}

void initializeAirports(Airport airports[], int& airportsLength) {
	fstream fin;
	fin.open("airportsales.txt");
	if(!fin.fail()) { 
		cout << "reading from airportsales.txt" << endl;
		string titles;
		getline(fin, titles);		
		int i = 0;		
		while(fin.good()) {
			string temp;
			getline(fin, airports[i].destination, ',');
			getline(fin, airports[i].country, ',');
			getline(fin, temp, ',');
			airports[i].tickets = stringToInt(temp);
			getline(fin, temp);
			airports[i].revenue = stringToInt(temp);
			//cout << airports[i].destination << "," << airports[i].country << "," << airports[i].tickets << "," << airports[i].revenue << endl;			
			i++;
			airportsLength++;
		}
	} else if(fin.fail()) {
		fin.open("airportcode.txt");
		cout << "reading from airportcode.txt" << endl;
		int i = 0;
		while(fin.good()) {
			getline(fin, airports[i].destination, ',');
			getline(fin, airports[i].country);
			airports[i].tickets = 0;
			airports[i].revenue = 0;
			//cout << airports[i].destination << "," << airports[i].country << "," << airports[i].tickets << "," << airports[i].revenue << endl;						
			i++;
			airportsLength++;
		}
	}
	fin.close();
	cout << "Number of airports: " << airportsLength << endl;	

	return;	
}

void updateArray(Promo promos[], int& promosLength) {
	for(int i = 0; i < promosLength; i++) {
		if(promos[i].quota <= 0) {
			promos[i].deleteMe = true;
		}
	}

	Promo newArray[500];
	int newLength = 0;	

	for(int i = 0; i < promosLength; i++) {
		if(!promos[i].deleteMe) {
			newArray[newLength] = promos[i];
			newLength++;
		}
	}

	for(int i = 0; i < promosLength; i++) {
		promos[i] = newArray[i];
	}
	promosLength = newLength;
	
	return;
}

void upsert(string oldInfo, string newInfo, Promo promos[], int& promosLength) {
	bool updated = false;
	for(int i = 0; i < promosLength; i++) {
		if(promos[i].destination == getHyphenTerm(oldInfo, 0) && promos[i].airline == getHyphenTerm(oldInfo, 1) && promos[i].fromDate == stringToInt(getHyphenTerm(oldInfo, 2)) && promos[i].toDate == stringToInt(getHyphenTerm(oldInfo, 3)) && promos[i].price == stringToInt(getHyphenTerm(oldInfo, 4))) {
			promos[i].destination == getHyphenTerm(newInfo, 0);
			promos[i].airline == getHyphenTerm(newInfofo, 1);
			promos[i].fromDate == stringToInt(getHyphenTerm(newInfo, 2));
			promos[i].toDate == stringToInt(getHyphenTerm(newInfo, 3));
			promos[i].price == stringToInt(getHyphenTerm(newInfo, 4));
			promos[i].quota == stringToInt(getHyphenTerm(newInfo, 5));
			updated = true;
		}
	}
	if(updated) {
		cout << "Promo updated" << endl;
	} else {
		promos[promosLength].destination == getHyphenTerm(newInfo, 0);
		promos[promosLength].airline == getHyphenTerm(innewInfofo, 1);
		promos[promosLength].fromDate == stringToInt(getHyphenTerm(newInfo, 2));
		promos[promosLength].toDate == stringToInt(getHyphenTerm(newInfo, 3));
		promos[promosLength].price == stringToInt(getHyphenTerm(newInfo, 4));
		promos[promosLength].quota == stringToInt(getHyphenTerm(newInfo, 5));
		promosLength++;
		cout << "Promo added" << endl;
	}
}

void addPromo(string fileName, Promo promos[], int& promosLength) {
 	ifstream fin;
 	string destination, airline;
 	int fromDate, toDate, price, endDate, quota;	

	fin.open(fileName);
	if(fin.fail()) {
		cout << "Error opening file" << endl;
		return;
	}

	string temp;
	getline(fin, temp, ':');
	getline(fin, airline);
	while(fin.good()) {
		getline(fin, temp);
		if(getSpaceTerm(temp, 0) == "deal") {
			endDate = stringToDate(temp.substr(10));
		} else if(getSpaceTerm(temp, 0) == "#") {
			continue;
		} else {
			destination = getCommaTerm(temp, 0);
			string s = "";
			s += getSpaceTerm(getCommaTerm(temp, 1), 0) + " ";
			s += getSpaceTerm(getCommaTerm(temp, 1), 1) + " ";
			s += getSpaceTerm(getCommaTerm(temp, 1), 2);
			fromDate = stringToDate(s);
			s = "";
			s += getSpaceTerm(getCommaTerm(temp, 1), 4) + " ";
			s += getSpaceTerm(getCommaTerm(temp, 1), 5) + " ";
			s += getSpaceTerm(getCommaTerm(temp, 1), 6);
			toDate = stringToDate(s);
			price = stringToInt(getSpaceTerm(getCommaTerm(temp, 2), 1));
			quota = stringToInt(getSpaceTerm(getCommaTerm(temp, 3), 1));
			cout << destination << "," << airline << "," << fromDate << "," << toDate << "," << price << "," << endDate << "," << quota << endl;

			bool quotaAdded = false;
			for(int i = 0; i < promosLength; i++) {
				if(promos[i].destination == destination && promos[i].airline == airline && promos[i].fromDate == fromDate && promos[i].toDate == toDate && promos[i].price == price && promos[i].endDate == endDate) {
					promos[i].quota += quota;
					cout << "Quota added" << endl;
					quotaAdded = true;
				} 
			}
			if(!quotaAdded) {
				promos[promosLength].destination = destination;
				promos[promosLength].airline = airline;
				promos[promosLength].fromDate = fromDate;
				promos[promosLength].toDate = toDate;
				promos[promosLength].price = price;
				promos[promosLength].endDate = endDate;
				promos[promosLength].quota = quota;
				promos[promosLength].searchNum = 0;
				promos[promosLength].deleteMe = false;
				promosLength += 1;
				cout << "Entry added" << endl;
			}
		}		
	}
	fin.close();
	return;
}

void today(int date, Promo promos[], int& promosLength) {
	for(int i = 0; i < promosLength; i++) {
		if(promos[i].endDate < date) {
			promos[i].deleteMe = true;
		}
	}			
	return;
}

void clear(Promo promos[], int& promosLength) {
	for(int i = 0; i < promosLength; i++) {
		promos[i].searchNum = 0;
	}
	return;
}

void searchDest(string dest, Promo promos[], int& promosLength) {
	clear(promos, promosLength);
	int j = 1;
	for(int i = 0; i < promosLength; i++) {
		if(promos[i].destination == dest) {
			promos[i].searchNum = j;
			cout << "<" << promos[i].searchNum << "> " << promos[i].destination << "-" << promos[i].airline << "-" << promos[i].fromDate << "-" << promos[i].toDate << "-" << promos[i].price << "-" << promos[i].endDate  << "-" << promos[i].quota<< endl;
			j++;
		}
	}	
	return;
}

void searchDate(int date, Promo promos[], int& promosLength) {
	clear(promos, promosLength);
	int j = 1;
	for(int i = 0; i < promosLength; i++) {
		if(promos[i].fromDate <= date && promos[i].toDate >= date) {
			promos[i].searchNum = j;
			cout << "<" << promos[i].searchNum << "> " << promos[i].destination << "-" << promos[i].airline << "-" << promos[i].fromDate << "-" << promos[i].toDate << "-" << promos[i].price << "-" << promos[i].endDate  << "-" << promos[i].quota<< endl;
			j++;
		}
	}	
	return;
}

void preferAirline(string airline, Promo promos[], int& promosLength) {
	int j = 1;
	for(int i = 0; i < promosLength; i++) {
		if(promos[i].searchNum != 0) {
			promos[i].searchNum = 0;
			if(promos[i].airline == airline) {
				promos[i].searchNum = j;
				cout << "<" << promos[i].searchNum << "> " << promos[i].destination << "-" << promos[i].airline << "-" << promos[i].fromDate << "-" << promos[i].toDate << "-" << promos[i].price << "-" << promos[i].endDate  << "-" << promos[i].quota<< endl;
				j++;
			}
		}	
	}	
	return;
}
 
void noAirline(string airline, Promo promos[], int& promosLength) {
	int j = 1;
	for(int i = 0; i < promosLength; i++) {
		if(promos[i].searchNum != 0) {
			promos[i].searchNum = 0;
			if(promos[i].airline != airline) {
				promos[i].searchNum = j;
				cout << "<" << promos[i].searchNum << "> " << promos[i].destination << "-" << promos[i].airline << "-" << promos[i].fromDate << "-" << promos[i].toDate << "-" << promos[i].price << "-" << promos[i].endDate  << "-" << promos[i].quota<< endl;
				j++;
			}
		}	
	}	
	return;
}

void buyk(int k, int n, Promo promos[], int& promosLength, Airport airports[], int& airportsLength) {
	bool matchFound = false;
	for(int i = 0; i < promosLength; i++) {
		if(promos[i].searchNum == k) {
			matchFound = true;
			if(promos[i].quota < n) {
				cout << "Not enough quota" << endl;
			} else {
				promos[i].quota -= n;			
				if(promos[i].quota == 0) {
					promos[i].deleteMe = true;
				}

				for(int j = 0; j < airportsLength; j++) {
					if(airports[j].destination == promos[i].destination) {
						airports[j].tickets += n;
						airports[j].revenue += n*0.9*promos[i].price;
						cout << "Airports[] updated" << endl;
					}
				}
			}
		}
	}
	if(!matchFound) {
		cout << "Please enter a valid number" << endl;
	}
	return;
}

void buy(string info, int n, Promo promos[], int& promosLength, Airport airports[], int& airportsLength) {
	for(int i = 0; i < promosLength; i++) {
		//cout << getHyphenTerm(info,0) << "-" << getHyphenTerm(info,1) << "-" << getHyphenTerm(info,2) << "-" << getHyphenTerm(info,3) << "-" << getHyphenTerm(info,4) << endl;
		if(promos[i].destination == getHyphenTerm(info, 0) && promos[i].airline == getHyphenTerm(info, 1) && promos[i].fromDate == stringToInt(getHyphenTerm(info, 2)) && promos[i].toDate == stringToInt(getHyphenTerm(info, 3)) && promos[i].price == stringToInt(getHyphenTerm(info, 4))) {
			if(promos[i].quota >= n) {
				promos[i].quota -= n;
				if(promos[i].quota == 0) {
					promos[i].deleteMe = true;
				}
				cout << "Destination: " << promos[i].destination << endl;
				for(int j = 0; j < airportsLength; j++) {
					if(airports[j].destination == promos[i].destination) {
						airports[j].tickets += n;
						airports[j].revenue += (n*promos[i].price)*(0.9);
						cout << "Airports[] updated" << endl;
					}
				}
			} else {
				cout << "Not enough quota" << endl;
			}
		}
	}

	return;
}

void most(Airport airports[], int& airportsLength) {
	Country countries[200];
	int countriesLength = 0;

	for(int i = 0; i < airportsLength; i++) { //Loop through airports[] to add each country to array without duplicates
		bool matchFound = false;
		for(int j = 0; j < countriesLength; j++) { //Loop through countries[] to see if country entry already exists
			if(countries[j].country == airports[i].country) {
				matchFound = true;
				countries[j].tickets += airports[i].tickets;
				countries[j].revenue += airports[i].revenue;
			}
		}
		if(!matchFound) {
			countriesLength += 1;
			countries[countriesLength].country = airports[i].country;
			countries[countriesLength].tickets = airports[i].tickets;
			countries[countriesLength].revenue = airports[i].revenue;			
		}
	}

	string s = "";
	int maxTickets = 0;	
	int revenue = 0;

	for(int i = 0; i < countriesLength; i++) {
		if(countries[i].tickets >= maxTickets) {
			maxTickets = countries[i].tickets;
			revenue = countries[i].revenue;
			s = countries[i].country;
		}
	}

	ofstream fout;
	fout.open("most.txt");
	if(fout.is_open()) {
		fout << s << endl;
		fout << "#" << maxTickets << endl;
		fout << "$" << revenue << endl;
	}
	fout.close();	
	return;
} 

void all(Promo promos[], int& promosLength, Airport airports[], int& airportsLength) {
	for(int i = 0; i < promosLength; i++) {
		cout << promos[i].destination << "," << promos[i].airline << "," << promos[i].fromDate << "," << promos[i].toDate << "," << promos[i].price << "," << promos[i].endDate  << "," << promos[i].quota << "," << promos[i].deleteMe << endl;
	}
	cout << "promos: " << promosLength << endl;

	for(int i = 0; i < airportsLength; i++) {
		cout << airports[i].destination << "," << airports[i].country << "," << airports[i].tickets << "," << airports[i].revenue << endl;
	}
	cout << "airports: " << airportsLength << endl;
}

void end(Promo promos[], int& promosLength, Airport airports[], int& airportsLength) {
	ofstream fout;	

	//Saves the promo array to promos.txt
	fout.open("promos.txt");
	fout << "destination,airline,from date,to date,price,deal ends,quota";
	for(int i = 0; i < promosLength; i++) {
		fout << endl << promos[i].destination << "," << promos[i].airline << "," << promos[i].fromDate << "," << promos[i].toDate << "," << promos[i].price << "," << promos[i].endDate  << "," << promos[i].quota;
	}
	cout << "promos.txt created" << endl;
	fout.close();

	//Saves the airports array to airportsales.txt
	fout.open("airportsales.txt");
	fout << "destination,country,tickets,revenue";
	for(int i = 0; i < airportsLength; i++) {
		fout << endl << airports[i].destination << "," << airports[i].country << "," << airports[i].tickets << "," << airports[i].revenue;
	}
	cout << "airportsales.txt created" << endl;
	fout.close();
	exit(1);
	return;
}

string getSpaceTerm(string line, int n) {
	int numOfSpaces = 0;
	string s = "";
	for(int i = 0; i < line.length(); i++){
		if(line[i] == ' '){
			numOfSpaces++;
		}
		if(numOfSpaces == n && line[i] != ' '){
			s += line[i];
		}
	}
	return s;
}

string getCommaTerm(string line, int n) {
	int numOfCommas = 0;
	string s = "";
	for(int i = 0; i < line.length(); i++){
		if(line[i] == ','){
			numOfCommas++;
		}
		if(numOfCommas == n && line[i] != ','){
			s += line[i];
		}
	}
	return s;
}

string getHyphenTerm(string line, int n) {
	int numOfHyphens = 0;
	string s = "";
	for(int i = 0; i < line.length(); i++){
		if(line[i] == '-'){
			numOfHyphens++;
		}
		if(numOfHyphens == n && line[i] != '-'){
			s += line[i];
		}
	}
	return s;
}

int stringToDate(string d) {
	string temp = "";
	string year, month, day;
	year = getSpaceTerm(d, 0);	
	temp += year;
	month = getSpaceTerm(d, 1);
	if(month == "Jan") {
		temp += "01";
	} else if (month == "Feb") {
		temp += "02";
	} else if (month == "Mar") {
		temp += "03";
	} else if (month == "Apr") {
		temp += "04";
	} else if (month == "May") {
		temp += "05";
	} else if (month == "Jun") {
		temp += "06";
	} else if (month == "Jul") {
		temp += "07";
	} else if (month == "Aug") {
		temp += "08";
	} else if (month == "Sep") {
		temp += "09";
	} else if (month == "Oct") {
		temp += "10";
	} else if (month == "Nov") {
		temp += "11";
	} else if (month == "Dec") {
		temp += "12";
	} else {
		cout << "Improper month format" << endl;
		return -1;
	}	
	day = getSpaceTerm(d, 2);
	if(stringToInt(day) < 10){
		temp += "0";
		temp += day;
	} else {
		temp += day;
	}
	int date;
	date = stringToInt(temp);
	return date;
}

int stringToInt(string s) {
	int i;
	stringstream magic;
 	magic << s;
 	magic >> i;
	return i;
}

string intToString(int i) {
	string s;
	stringstream magic;
	magic << i;
	magic >> s;
	return s;
}
