// TASK-3: Student Record System in C++ (Enhanced with CSV, Validation, Phone & CNIC, Update Feature)

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <limits>
#include <cctype>
#include <algorithm>
using namespace std;

// ================= STUDENT CLASS =================
class Student {
    int id;
    string name;
    int age;
    string phone;
    string cnic;
    string course;

public:
    Student() : id(0), age(0) {}
    Student(int i, string n, int a, string p, string cn, string c) 
        : id(i), name(n), age(a), phone(p), cnic(cn), course(c) {}

    // Validation helpers
    static bool isDigits(const string &s) {
        return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
    }

    // Create new student record
    void createStudent(const vector<Student> &students) {
        cout << "\n======================================\n";
        cout << "        ADD NEW STUDENT RECORD\n";
        cout << "======================================\n";

        // Unique ID
// Unique 6-digit ID
while (true) {
    cout << "Enter Student ID (6 digits) : ";
    cin >> id;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter numbers only.\n";
        continue;
    }

    // Check if ID has exactly 6 digits
    if (id < 100000 || id > 999999) {
        cout << "Student ID must be exactly 6 digits.\n";
        continue;
    }

    // Check uniqueness
    bool exists = false;
    for (auto &s : students) {
        if (s.getID() == id) {
            exists = true;
            break;
        }
    }
    if (exists) {
        cout << "ID already exists! Enter a unique ID.\n";
        continue;
    }

    break;
}
        cin.ignore();
        cout << "Enter Name                  : ";
        getline(cin, name);

        // Age validation
        while (true) {
            cout << "Enter Age                   : ";
            cin >> age;
            if (cin.fail() || age <= 0 || age > 100) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid age! Enter a valid number (1-100).\n";
                continue;
            }
            break;
        }

        // Phone validation (11 digits)
        while (true) {
            cout << "Enter Phone Number          : ";
            cin >> phone;
            if (phone.size() != 11 || !isDigits(phone)) {
                cout << "Invalid phone number! Must be exactly 10 digits.\n";
                continue;
            }
            break;
        }

        // CNIC validation (13 digits)
        while (true) {
            cout << "Enter CNIC                  : ";
            cin >> cnic;
            if (cnic.size() != 13 || !isDigits(cnic)) {
                cout << "Invalid CNIC! Must be exactly 13 digits.\n";
                continue;
            }
            break;
        }

        cin.ignore();
        cout << "Enter Course                 : ";
        getline(cin, course);
    }

    // Update student record
    void updateStudent() {
        cin.ignore();
        cout << "\n======================================\n";
        cout << "        UPDATE STUDENT RECORD\n";
        cout << "======================================\n";

        cout << "Enter New Name         : ";
        getline(cin, name);

        while (true) {
            cout << "Enter New Age          : ";
            cin >> age;
            if (cin.fail() || age <= 0 || age > 100) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid age! Enter a valid number (1-100).\n";
                continue;
            }
            break;
        }

        while (true) {
            cout << "Enter New Phone Number : ";
            cin >> phone;
            if (phone.size() != 11 || !isDigits(phone)) {
                cout << "Invalid phone number! Must be exactly 11 digits.\n";
                continue;
            }
            break;
        }

        while (true) {
            cout << "Enter New CNIC         : ";
            cin >> cnic;
            if (cnic.size() != 13 || !isDigits(cnic)) {
                cout << "Invalid CNIC! Must be exactly 13 digits.\n";
                continue;
            }
            break;
        }

        cin.ignore();
        cout << "Enter New Course       : ";
        getline(cin, course);

        cout << "\nStudent record updated successfully!\n";
    }

    // Display student record
    void showStudent() const {
        cout << left << setw(10) << id
             << setw(20) << name
             << setw(8) << age
             << setw(15) << phone
             << setw(18) << cnic
             << setw(15) << course << endl;
    }

    // File helpers
    string toCSV() const {
        return to_string(id) + "," + name + "," + to_string(age) + "," + phone + "," + cnic + "," + course;
    }
    static Student fromCSV(const string &line) {
        stringstream ss(line);
        string token;
        vector<string> parts;
        while (getline(ss, token, ',')) {
            parts.push_back(token);
        }
        if (parts.size() != 6) return Student();
        return Student(stoi(parts[0]), parts[1], stoi(parts[2]), parts[3], parts[4], parts[5]);
    }

    // Getters
    int getID() const { return id; }
};

// ================= FILE HELPERS =================
const string FILENAME = "students.csv";

vector<Student> loadStudents() {
    vector<Student> students;
    ifstream ifs(FILENAME);
    string line;
    while (getline(ifs, line)) {
        if (!line.empty()) students.push_back(Student::fromCSV(line));
    }
    return students;
}

void saveStudents(const vector<Student> &students) {
    ofstream ofs(FILENAME);
    for (auto &s : students) {
        ofs << s.toCSV() << "\n";
    }
}

// ================= FUNCTIONS =================
void addStudent() {
    vector<Student> students = loadStudents();
    Student st;
    st.createStudent(students);
    students.push_back(st);
    saveStudents(students);
    cout << "\nStudent record added successfully!\n";
}

void viewAllStudents() {
    vector<Student> students = loadStudents();
    cout << "\n==============================================================================\n";
    cout << "                              ALL STUDENT RECORDS\n";
    cout << "==============================================================================\n";
    cout << left << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(8) << "Age"
         << setw(15) << "Phone"
         << setw(18) << "CNIC"
         << setw(15) << "Course" << endl;
    cout << "------------------------------------------------------------------------------\n";

    if (students.empty()) {
        cout << "No student records found.\n";
        return;
    }
    for (auto &s : students) s.showStudent();
}

void searchStudent() {
    int searchID;
    cout << "\nEnter Student ID to search: ";
    cin >> searchID;

    vector<Student> students = loadStudents();
    for (auto &s : students) {
        if (s.getID() == searchID) {
            cout << "\nStudent Found:\n";
            cout << left << setw(10) << "ID"
                 << setw(20) << "Name"
                 << setw(8) << "Age"
                 << setw(15) << "Phone"
                 << setw(18) << "CNIC"
                 << setw(15) << "Course" << endl;
            cout << "--------------------------------------------------------------------------\n";
            s.showStudent();
            return;
        }
    }
    cout << "\nStudent ID not found!\n";
}

void deleteStudent() {
    int deleteID;
    cout << "\nEnter Student ID to delete: ";
    cin >> deleteID;

    vector<Student> students = loadStudents();
    vector<Student> updated;
    bool found = false;

    for (auto &s : students) {
        if (s.getID() == deleteID) {
            found = true; // skip this student
        } else {
            updated.push_back(s);
        }
    }

    saveStudents(updated);

    if (found)
        cout << "\nStudent record deleted successfully!\n";
    else
        cout << "\nStudent ID not found!\n";
}

void updateStudent() {
    int updateID;
    cout << "\nEnter Student ID to update: ";
    cin >> updateID;

    vector<Student> students = loadStudents();
    bool found = false;

    for (auto &s : students) {
        if (s.getID() == updateID) {
            s.updateStudent();
            found = true;
            break;
        }
    }

    saveStudents(students);

    if (!found)
        cout << "\nStudent ID not found!\n";
}

// ================= MAIN =================
int main() {
    int choice;
    do {
        cout << "\n======================================\n";
        cout << "        STUDENT RECORD SYSTEM\n";
        cout << "======================================\n";
        cout << " 1. Add New Student\n";
        cout << " 2. View All Students\n";
        cout << " 3. Search Student by ID\n";
        cout << " 4. Delete Student by ID\n";
        cout << " 5. Update Student Record\n";
        cout << " 6. Exit\n";
        cout << "======================================\n";
        cout << "Choose an option (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewAllStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: updateStudent(); break;
            case 6: cout << "\nExiting Student Record System...\n"; break;
            default: cout << "\nInvalid choice! Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
