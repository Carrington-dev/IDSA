#include "student.h"
#include <iostream>
#include <string>

using namespace std;

Student::Student()
{
        marks = 34;
        cout << "I am the constructor running" << endl;

}

Student::Student(string name)
{
        name = name;
        cout << "I am the constructor running as the over loader " << name << endl;

}

void Student::print()
{
    cout << "Marks are " << marks << endl;
}


Student::~Student(){
 cout << "My final value is " << marks << ". Goodbye." << endl;
}
