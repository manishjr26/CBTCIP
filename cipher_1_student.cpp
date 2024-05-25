#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

struct Student {
    int rollNo;
    string name;
    string department;
    string course;
    int year;
};

vector<Student> students;

void addStudent();
void displayStudents();
void searchStudent();
void modifyStudent(); 
void deleteStudent(); 
void showMenu();

int main() {
    showMenu();
    return 0;
}

void showMenu() {
    int choice;
    do {
        cout << "\n==== Student Record Management System ====\n";
        cout << "1. Add Student Record\n";
        cout << "2. Display All Student Records\n";
        cout << "3. Search Student Record\n";
        cout << "4. Modify Student Record\n";
        cout << "5. Delete Student Record\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Check if the input is valid
        if (cin.fail()) {
            cout << "Invalid choice! Please enter a number between 1 and 6.\n";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            continue; // Skip the rest of the loop and start over
        }

        // Clear input buffer to avoid incorrect inputs
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: modifyStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Please try again.\n";
        }
    } while(choice != 6);
}


void addStudent() {
    Student student;

    // Loop to ensure valid integer input for roll number
    while (true) {
        cout << "\nEnter Roll Number: ";
        cin >> student.rollNo;
        if (cin.fail()) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a valid integer for Roll Number.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            break; // Valid input
        }
    }

    cout << "Enter Name: ";
    getline(cin, student.name);
    cout << "Enter Department: ";
    getline(cin, student.department);
    cout << "Enter Course: ";
    getline(cin, student.course);
    cout << "Enter Year: ";
    cin >> student.year;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer

    students.push_back(student);
    cout << "\nStudent record has been created\n";
}

void displayStudents() {
    if (students.empty()) {
        cout << "\nNo student records found.\n";
        return;
    }

    cout << "\n==== Displaying All Student Records ====\n";
    for (const auto& student : students) {
        cout << "\nRoll Number: " << student.rollNo;
        cout << "\nName: " << student.name;
        cout << "\nDepartment: " << student.department;
        cout << "\nCourse: " << student.course;
        cout << "\nYear: " << student.year;
        cout << "\n====================================\n";
    }
}

void searchStudent() {
    int rollNo;
    cout << "\nEnter the roll number of the student to search: ";
    cin >> rollNo;

    // Clear input buffer to avoid incorrect inputs
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool found = false;
    for (const auto& student : students) {
        if (student.rollNo == rollNo) {
            cout << "\nRoll Number: " << student.rollNo;
            cout << "\nName: " << student.name;
            cout << "\nDepartment: " << student.department;
            cout << "\nCourse: " << student.course;
            cout << "\nYear: " << student.year;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nStudent record not found.\n";
    }
}

void modifyStudent() {
    int rollNo;
    cout << "\nEnter the roll number of the student to modify: ";
    cin >> rollNo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer

    bool found = false;
    for (auto& student : students) {
        if (student.rollNo == rollNo) {
            cout << "\nEnter new details for the student\n";
            cout << "Enter Name: ";
            getline(cin, student.name);
            cout << "Enter Department: ";
            getline(cin, student.department);
            cout << "Enter Course: ";
            getline(cin, student.course);
            cout << "Enter Year: ";
            cin >> student.year;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer

            cout << "\nStudent record has been updated\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nStudent record not found.\n";
    }
}

void deleteStudent() {
    int rollNo;
    cout << "\nEnter the roll number of the student to delete: ";
    cin >> rollNo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer

    auto it = students.begin();
    bool found = false;
    while (it != students.end()) {
        if (it->rollNo == rollNo) {
            it = students.erase(it);
            found = true;
            cout << "\nStudent record has been deleted\n";
            break;
        } else {
            ++it;
        }
    }

    if (!found) {
        cout << "\nStudent record not found.\n";
    }
}
