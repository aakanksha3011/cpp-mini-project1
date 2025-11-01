#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Student {
public:
    int roll;
    string name;
    float marks;
    char grade;

    void calculateGrade() {
        if (marks >= 90) grade = 'A';
        else if (marks >= 75) grade = 'B';
        else if (marks >= 60) grade = 'C';
        else if (marks >= 40) grade = 'D';
        else grade = 'F';
    }

    void input() {
        cout << "\nEnter Roll No: ";
        cin >> roll;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Marks: ";
        cin >> marks;
        calculateGrade();
    }

    void display() {
        cout << "\nRoll No : " << roll;
        cout << "\nName    : " << name;
        cout << "\nMarks   : " << marks;
        cout << "\nGrade   : " << grade << "\n";
    }
};

// File name
string filename = "students.txt";

// Save all students to file
void saveToFile(vector<Student> &list) {
    ofstream fout(filename);
    for (auto &s : list) {
        fout << s.roll << "\n" << s.name << "\n" 
             << s.marks << "\n" << s.grade << "\n";
    }
    fout.close();
}

// Load from file
void loadFromFile(vector<Student> &list) {
    list.clear();
    ifstream fin(filename);
    if (!fin) return;

    while (!fin.eof()) {
        Student s;
        fin >> s.roll;
        fin.ignore();
        getline(fin, s.name);
        fin >> s.marks;
        fin >> s.grade;

        if (fin.eof()) break;
        list.push_back(s);
    }
    fin.close();
}

void addStudent(vector<Student> &list) {
    Student s;
    s.input();
    list.push_back(s);
    cout << "\n Student Added Successfully!\n";
}

void displayAll(vector<Student> &list) {
    if (list.empty()) {
        cout << "\nNo students found.\n";
        return;
    }

    cout << "\n=== All Students ===\n";
    for (auto &s : list) {
        s.display();
    }
}

void searchStudent(vector<Student> &list) {
    int r;
    cout << "\nEnter Roll No to Search: ";
    cin >> r;

    for (auto &s : list) {
        if (s.roll == r) {
            cout << "\n Student Found:\n";
            s.display();
            return;
        }
    }
    cout << "\n Student Not Found!\n";
}

void updateStudent(vector<Student> &list) {
    int r;
    cout << "\nEnter Roll No to Update: ";
    cin >> r;

    for (auto &s : list) {
        if (s.roll == r) {
            cout << "\nEnter New Details:\n";
            s.input();
            cout << "\n Updated Successfully!\n";
            return;
        }
    }
    cout << "\n Student Not Found!\n";
}

void deleteStudent(vector<Student> &list) {
    int r;
    cout << "\nEnter Roll No to Delete: ";
    cin >> r;

    for (int i = 0; i < list.size(); i++) {
        if (list[i].roll == r) {
            list.erase(list.begin() + i);
            cout << "\n Deleted Successfully!\n";
            return;
        }
    }
    cout << "\n Student Not Found!\n";
}

int main() {
    vector<Student> students;

    loadFromFile(students);

    int choice;

    do {
        cout << "\n===== STUDENT MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Save & Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent(students);
            break;
        case 2:
            displayAll(students);
            break;
        case 3:
            searchStudent(students);
            break;
        case 4:
            updateStudent(students);
            break;
        case 5:
            deleteStudent(students);
            break;
        case 6:
            saveToFile(students);
            cout << "\n Data Saved. Exiting...\n";
            break;
        default:
            cout << "\n Invalid Choice\n";
        }
    } while (choice != 6);

    return 0;
}

