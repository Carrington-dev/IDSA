#include "thing.h"
#include <iostream>

using namespace std;

Thing::Thing()
{
    value = -1;

    cout << "Hello from the default constructor!" << endl;

}

Thing::Thing(int v)
{
    value = v;
    cout << "Hello from the alternate constructor! You passed in the value "<<  value <<"!" << endl;
}

void Thing::print()
{
    cout << "I am an instance of the Thing class and I store the value "<< value  << "!" << endl;
}


Thing::~Thing(){
    cout << "My final value is " << value << ". Goodbye." << endl;
}
