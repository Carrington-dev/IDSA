#include <iostream>
#include <thing.h>

using namespace std;

int main()
{
    Thing t1;
    Thing t2(42);

    //Call the print function of the instances above;
    t1.print();
    t2.print();

    // change the values of the objects above
    t1.value = 10;
    t2.value = 500;

    //Call the print function of the instances above;
    t1.print();
    t2.print();

    // Dynamically allocate a thing and use the default constructor
    Thing* ptr1 = new Thing();
    // Dynamically allocate a thing and use the overloaded constructor
    Thing* ptr2 = new Thing(-42);

    // Change the values
    // Note that we use -> to access the members from a pointer
    ptr1->value = -10;
    ptr2->value = -500;

    // Print them...
    ptr1->print();
    ptr2->print();

    // Show the addresses:
    cout << "The address of t1 is: " << &t1 << endl;
    cout << "The address of t2 is: " << &t2 << endl;
    cout << "The address of the first dynamically allocated object is: "
    << ptr1 << endl;
    cout << "The address of the second dynamically allocated object is: "
    << ptr2 << endl;
    cout << "The address of the pointer ptr1 is: " << &ptr1 << endl;
    cout << "The address of the pointer ptr2 is: " << &ptr2 << endl;

    // Delete the object that ptr1 points to
    delete ptr1;
    // Oops we forgot to delete the object that ptr2 points to
    // delete ptr2;



    return 0;
}
