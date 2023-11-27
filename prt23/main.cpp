#include <iostream>
#include "student.h"

using namespace std;

int main()
{
    Student st1;
    Student st2("Carrington 2");
    st2.marks = 99;

    cout << "Second student instance memory location " << &st2 << endl;
    return 0;
}
