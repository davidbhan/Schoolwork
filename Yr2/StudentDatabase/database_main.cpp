#include "database.h"
#include <iostream>
using namespace std;

int main(int argc, char **args) {
    string command, command_type;
    string id, name, phone, class_id;
    double grade;
    Database record_set;
    while(cin >> command >> command_type) {
        if(command_type == "profile") {
            if (command == "create") {
                cin >> id >> name >> phone;
                record_set.add_profile(id, name, phone);
            } else if (command == "delete") {
                cin >> id;
                record_set.del_profile(id);
            } else if (command == "display") {
                record_set.display_profiles();
            }
        } else if (command_type == "grade") {
            if (command == "create") {
                cin >> id >> class_id >> grade;
                record_set.add_grade(id, class_id, grade);
            } else if (command == "delete") {
                cin >> id >> class_id;
                record_set.del_grade(id, class_id);
            } else if (command == "display") {
                cin >> class_id;
                record_set.display_grades(class_id);
            }
        }
    }
}
