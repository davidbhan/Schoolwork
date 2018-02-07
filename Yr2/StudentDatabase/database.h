#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
using namespace std;

// structure for student profile
typedef struct profile_t {
    string studentID;
    string name;
    string phoneNumber;
} Profile;

// structure for class grade
typedef struct grade_t {
    string studentID;
    string classID;
    double mark;
} Grade;

// Database class, containing vector of profiles and grades
class Database {
private:
    // Define some data structure using STL containers here
    // to store all students' profiles and the grade records.
    vector<Profile> profiles;
    vector<Grade> grades;
public:
    bool add_profile(string id, string name, string phone);
    bool del_profile(string id);
    bool add_grade(string id, string class_id, double grade);
    bool del_grade(string id, string class_id);

    void display_profiles();
    void display_grades(string class_id);
};

#endif
