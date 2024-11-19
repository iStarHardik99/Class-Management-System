#include <iostream>
#include <vector>
#include <fstream>  // for file handling
#include <algorithm>
#include <string>
#include <limits>   // for input validation
#include <stdio.h>
#include <stdlib.h> 

using namespace std;

struct Student 
{
    string name;
    string rollNo;
    string course;
    string studentClass;
    string contact;
};

vector<Student> students;

void saveDataToFile() 
{
    ofstream file("student_data.txt");
    if (file.is_open()) 
    {
        for (const auto& student : students) 
        {
            file << student.name << "," 
                 << student.rollNo << "," 
                 << student.course << "," 
                 << student.studentClass << "," 
                 << student.contact << endl;
        }
        file.close();
        cout << "Data saved successfully!" << endl;
    } 
    else 
    {
        cout << "Unable to open file for saving!" << endl;
    }
}

void loadDataFromFile() 
{
    ifstream file("student_data.txt");
    if (file.is_open()) 
    {
        students.clear(); // Clear any existing data in the vector
        string line, token;
        while (getline(file, line)) 
        {
            Student student;
            size_t pos = 0;
            pos = line.find(',');
            student.name = line.substr(0, pos);
            line.erase(0, pos + 1);
            
            pos = line.find(',');
            student.rollNo = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(',');
            student.course = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(',');
            student.studentClass = line.substr(0, pos);
            line.erase(0, pos + 1);

            student.contact = line;

            students.push_back(student);
        }
        file.close();
        cout << "Data loaded successfully!" << endl;
    } 
    else 
    {
        cout << "No previous data found to load!" << endl;
    }
}

void enter() 
{
    int count = 0;
    cout << "How many students do you want to enter? ";
    cin >> count;

    cin.ignore(); // Clear the input buffer

    for (int i = 0; i < count; i++) 
    {
        Student student;
        cout << "\nEnter the data of student " << students.size() + 1 << endl;

        cout << "Enter name: ";
        getline(cin, student.name);

        cout << "Enter Roll no: ";
        getline(cin, student.rollNo);

        cout << "Enter course: ";
        getline(cin, student.course);

        cout << "Enter class: ";
        getline(cin, student.studentClass);

        cout << "Enter contact: ";
        getline(cin, student.contact);

        students.push_back(student);
    }

    saveDataToFile();  // Save new entries to file
}


void show() 
{
    if (students.empty()) 
    {
        cout << "No data is entered!" << endl;
    } 
    else 
    {
        for (size_t i = 0; i < students.size(); i++) 
        {
            cout << "\nData of Student " << i + 1 << endl;
            cout << "Name: " << students[i].name << endl;
            cout << "Roll no: " << students[i].rollNo << endl;
            cout << "Course: " << students[i].course << endl;
            cout << "Class: " << students[i].studentClass << endl;
            cout << "Contact: " << students[i].contact << endl;
        }
    }
}

void search() 
{
    if (students.empty()) 
    {
        cout << "No data is entered!" << endl;
    } 
    else 
    {
        string rollno;
        cout << "Enter the roll no of the student: ";
        cin >> rollno;

        bool found = false;
        for (const auto& student : students) 
        {
            if (student.rollNo == rollno) 
            {
                cout << "Name: " << student.name << endl;
                cout << "Roll no: " << student.rollNo << endl;
                cout << "Course: " << student.course << endl;
                cout << "Class: " << student.studentClass << endl;
                cout << "Contact: " << student.contact << endl;
                found = true;
                break;
            }
        }
        if (!found) 
        {
            cout << "Student with Roll no " << rollno << " not found." << endl;
        }
    }
}

void update() 
{
    if (students.empty()) 
    {
        cout << "No data is entered!" << endl;
    } 
    else 
    {
        string rollno;
        cout << "Enter the roll no of the student which you want to update: ";
        cin >> rollno;

        bool found = false;
        for (auto& student : students) 
        {
            if (student.rollNo == rollno) 
            {
                cout << "\nPrevious data:" << endl;
                cout << "Name: " << student.name << endl;
                cout << "Roll no: " << student.rollNo << endl;
                cout << "Course: " << student.course << endl;
                cout << "Class: " << student.studentClass << endl;
                cout << "Contact: " << student.contact << endl;

                cout << "Enter Roll no: ";
                cin.ignore(); // Clear buffer
                getline(cin, student.rollNo);

                cout << "Enter course: ";
                getline(cin, student.course);

                cout << "Enter class: ";
                getline(cin, student.studentClass);

                cout << "Enter contact: ";
                getline(cin, student.contact);

                saveDataToFile();  // Save updated data to file
                found = true;
                break;
            }
        }
        if (!found) 
        {
            cout << "Student with Roll no " << rollno << " not found." << endl;
        }
    }
}

void deleterecord() {
    if (students.empty()) 
    {
        cout << "No data is entered!" << endl;
    } 
    else 
    {
        int a;
        cout << "Press 1 to delete all records" << endl;
        cout << "Press 2 to delete a specific record" << endl;
        cin >> a;

        if (a == 1) 
        {
            students.clear();
            cout << "All records are deleted!" << endl;
            saveDataToFile();  // Save empty data to file
        } 
        else if (a == 2) 
        {
            string rollno;
            cout << "Enter the roll no of the student you want to delete: ";
            cin >> rollno;

            auto it = remove_if(students.begin(), students.end(), [&](Student& student) 
            {
                return student.rollNo == rollno;
            });

            if (it != students.end()) 
            {
                students.erase(it, students.end());
                cout << "The record is deleted." << endl;
                saveDataToFile();  // Save updated data to file
            } 
            else 
            {
                cout << "Student with Roll no " << rollno << " not found." << endl;
            }
        } 
        else
        {
            cout << "Invalid input!" << endl;
        }
    }
}

void sortData() 
{
    if (students.empty()) 
    {
        cout << "No data is entered!" << endl;
        return;
    }

    int choice;
    cout << "Sort by: \n1. Name \n2. Roll No\n";
    cin >> choice;

    if (choice == 1) 
    {
        sort(students.begin(), students.end(), [](Student& a, Student& b) 
        {
            return a.name < b.name;
        }); 
        cout << "Data sorted by Name." << endl;
    }
    else if (choice == 2) 
    {
        sort(students.begin(), students.end(), [](Student& a, Student& b) {
            return a.rollNo < b.rollNo;
        });
        cout << "Data sorted by Roll No." << endl;
    } 
    else 
    {
        cout << "Invalid choice!" << endl;
    }
}


int main() 
{
    loadDataFromFile();  // Load data from file at startup
  
    int value;
    while (true) 
    {
        cout << "\nPress 1 to enter data" << endl;
        cout << "Press 2 to show data" << endl;
        cout << "Press 3 to search data" << endl;
        cout << "Press 4 to update data" << endl;
        cout << "Press 5 to delete data" << endl;
        cout << "Press 6 to sort data" << endl;
        cout << "Press 7 to exit" << endl;
        cin >> value;

        switch (value) 
        {
            case 1:
                enter();
                break;
            case 2:
                show();
                break;
            case 3:
                search();
                break;
            case 4:
                update();
                break;
            case 5:
                deleterecord();
                break;
            case 6:
                sortData();
                break;
            case 7:
                cout << "Exiting program..." << endl;
                return 0;
            default:
                cout << "Invalid input! Please try again." << endl;
        }
    }
    return 0;
}