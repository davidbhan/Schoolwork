#include <iostream>
#include <algorithm>
#include "database.h"
using namespace std;

// Add profile information to profiles vector
bool Database::add_profile(string id, string name, string phone) {
	// Check for ID match through iteration
	vector<Profile>::iterator profile_itr;
	for (profile_itr = profiles.begin(); profile_itr != profiles.end(); profile_itr++) {
		if ((*profile_itr).studentID == id) {
			(*profile_itr).name = name;
			(*profile_itr).phoneNumber = phone;
			cout << "Profile Updated" << endl;
			return true;
		}
	}

	// add new record if none exists
	Profile prof;
	prof.studentID = id;
	prof.name = name;
	prof.phoneNumber = phone;
	profiles.push_back(prof);

	return true;
}


// Delete a profile given studnt id
bool Database::del_profile(string id) {
	bool success = false;
	
	// Delete student profile
	vector<Profile>::iterator profile_itr;
	for (profile_itr = profiles.begin(); profile_itr != profiles.end(); profile_itr++) {
		if ((*profile_itr).studentID == id) {
			profiles.erase(profile_itr);
			success = true;
			break;
		}
	}

	// Delete student grades if student existed in profiles, then return
	if (success) {
		vector<Grade>::iterator grade_itr;
		for (grade_itr = grades.begin(); grade_itr != grades.end(); grade_itr++) {
			if ((*grade_itr).studentID == id) {
				grades.erase(grade_itr);
			}
		}
		return success;
	}

	// Display message if none exists
	cout << "Record Not Exists" << endl;
	return success;
}

// Add grade to database
bool Database::add_grade(string id, string class_id, double grade) {
	bool success = false;

	// Check if student exists by looping through profiles
	vector<Profile>::iterator profile_itr;
	for (profile_itr = profiles.begin(); profile_itr != profiles.end(); profile_itr++) {
		if ((*profile_itr).studentID == id) {

			// Check if grade entry already exists by iterating through grades
			vector<Grade>::iterator grade_itr;
			for (grade_itr = grades.begin(); grade_itr != grades.end(); grade_itr++) {
				if ((*grade_itr).studentID == id && (*grade_itr).classID == class_id) {
					// Update grade and return
					(*grade_itr).mark = grade;
					cout << "Updated" << endl;
					return success;
				}
			}

			// If no current grade, add a new entry
			Grade grad;
			grad.studentID = id;
			grad.classID = class_id;
			grad.mark = grade;
			grades.push_back(grad);

			success = true;
			return success;

		}
	}

	cout << "Student Not Exists" << endl;
	return success;
}

// Delete grade from database
bool Database::del_grade(string id, string class_id) {
	bool success = false;

	// Check if grade entry exists by iterating through grades
	vector<Grade>::iterator grade_itr;
	for (grade_itr = grades.begin(); grade_itr != grades.end(); grade_itr++) {
		if ((*grade_itr).studentID == id && (*grade_itr).classID == class_id) {
			grades.erase(grade_itr);
			success = true;
			return success;
		}
	}

	cout << "Record Not Exists" << endl;
	return success;
}

// Comparison function for sorting profiles
bool compare_name(Profile a, Profile b) {
	return a.name < b.name;
}

// Display profiles
void Database::display_profiles() {
	// Sort profiles by name in ascending order
	sort(profiles.begin(), profiles.end(), compare_name);

	// Iterate through profiles and display them
	vector<Profile>::const_iterator profile_itr;
	for (profile_itr = profiles.begin(); profile_itr != profiles.end(); profile_itr++) {
		cout << (*profile_itr).name << " " << (*profile_itr).studentID << " " << (*profile_itr).phoneNumber << endl;
	}

	return;
}

// Comparison function for sorting grades
bool compare_marK(Grade a, Grade b) {
	return a.mark < b.mark;
}

// Display grades and basic info
void Database::display_grades(string class_id) {
	// Handles empty grade record
	if (grades.size() < 1) {
		cout << "No Records Found" << endl;
		return;
	}

	// Info variables
	double max = 0.0;
	double min = 100.0;
	double total_grades = 0.0;
	int num_grades = 0;

	// Sort grades by mark in ascending order
	sort(grades.begin(), grades.end(), compare_marK);

	// Iterate through grades and display them
	vector<Grade>::const_iterator grade_itr;
	for (grade_itr = grades.begin(); grade_itr != grades.end(); grade_itr++) {

		// Filter unwanted classes
		if ((*grade_itr).classID == class_id) {

			total_grades += (*grade_itr).mark;
			num_grades++;
			if ((*grade_itr).mark > max) {
				max = (*grade_itr).mark;
			}
			if ((*grade_itr).mark < min) {
				min = (*grade_itr).mark;
			}

			// Find matching student name to current studentID
			string name;

			vector<Profile>::const_iterator profile_itr;
			for (profile_itr = profiles.begin(); profile_itr != profiles.end(); profile_itr++) {
				if ((*profile_itr).studentID == (*grade_itr).studentID) {
					name = (*profile_itr).name;
					break;
				}
			}

			cout << name << " " << (*grade_itr).studentID << " " << (*grade_itr).mark << endl;
		}
	}

	cout << "Min " << min << endl;
	cout << "Max " << max << endl;
	cout << "Average " << total_grades/num_grades << endl;

}

