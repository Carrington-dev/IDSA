#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <iostream>

using namespace std;

class Student
{
public:
    Student();
    Student(string name);
    ~Student();
    void print();
    int marks;
    string name;
};

#endif // STUDENT_H
