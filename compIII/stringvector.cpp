/***********************************************
Author: Daniel Bergeron
Date: 10/16/2022
Purpose: A class that stores a dynamic array of strings
Sources of Help: class slides
Time Spent: 1.5hrs
***********************************************/
/*
Computing III -- COMP.2010 Honor Statement
The practice of good ethical behavior is essential for maintaining
good order in the classroom, providing an enriching learning
experience for students, and as training as a practicing computing
professional upon graduation. This practice is manifested in the
University’s Academic Integrity policy. Students are expected to
strictly avoid academic dishonesty and adhere to the Academic
Integrity policy as outlined in the course catalog. Violations will
be dealt with as outlined therein.
All programming assignments in this class are to be done by the
student alone. No outside help is permitted except the instructor and
approved tutors.
I certify that the work submitted with this assignment is mine and was
generated in a manner consistent with this document, the course
academic policy on the course website on Blackboard, and the UMass
Lowell academic code.
Date: 10/16/2022
Name: Daniel Bergeron
*/

#include <iostream>
#include<string>
using namespace std;

class DynamicStringArray {
public:

    DynamicStringArray();

    DynamicStringArray(const DynamicStringArray& obj);

    /*A function named addEntry that takes a string as input. The function should create a new
    dynamic array one element larger than dynamicArray, copy all elements from dynamicArray into
    the new array, add the new string onto the end of the new array, increment size, delete the old
    dynamicArray, and then set dynamicArray to the new array.*/
    void addEntry(string inString);

    /*A function named deleteEntry that takes a string(removeString) as input. The function should search
    dynamicArray for the string. If not found, it returns false. If found, it creates a new dynamic
    array one element smaller than dynamicArray. It should copy all elements except the input
    string into the new array, delete dynamicArray, decrement size, and return true.*/
    bool deleteEntry(string rmString);

    /*A function named getEntry that takes an integer as input and returns a pointer that references
    to the string at that index in dynamicArray. It should return nullptr if the index is out of
    dynamicArray’s bounds.*/
    string* getEntry(int index);

    //overloads assingment as a memberFunction
    DynamicStringArray& operator=(const DynamicStringArray& rightOp);

    //function will return size
    int getStringArraySize(void);

    ~DynamicStringArray();

private:
    string* dynamicArray;
    int size;
};

int main(int argc, char* argv[]) {
    DynamicStringArray sA1;
    sA1.addEntry("Hello ");
    sA1.addEntry("Dynamic ");
    sA1.addEntry("Array ");
    cout << *(sA1.getEntry(0)) << *(sA1.getEntry(1)) << *(sA1.getEntry(2));
    int size = sA1.getStringArraySize(); \

        cout << "\nCurrent size: " << size << endl;
    sA1.deleteEntry("Hello ");
    cout << *(sA1.getEntry(0)) << *(sA1.getEntry(1));
    cout << "\nCurrent size: " << sA1.getStringArraySize() << endl;

    //sA2.operator=(sA1);
    DynamicStringArray sA2(sA1);
    cout << "S2: " << *(sA2.getEntry(0)) << *(sA2.getEntry(1));
    cout << "\nSize of S2 after copy: " << sA1.getStringArraySize() << endl;

    sA2.addEntry("debug ");
    sA2.addEntry("is ");
    sA2.addEntry("hard ");
    sA1.operator=(sA2);
    for (int i = 0; i < sA1.getStringArraySize(); i++) {
        cout << *(sA2.getEntry(i));
    }
    cout << endl;

    sA2.~DynamicStringArray();
    sA1.~DynamicStringArray();
    return 0;
}

DynamicStringArray::DynamicStringArray() {
    dynamicArray = nullptr;
    size = 0;
}

DynamicStringArray::DynamicStringArray(const DynamicStringArray& obj) {
    dynamicArray = new string[obj.size];
    size = obj.size;
    for (int i = 0; i < size; i++) {
        dynamicArray[i] = obj.dynamicArray[i];
    }
}

void DynamicStringArray::addEntry(string inString) {
    string* newArray = new string[size + 1];
    for (int i = 0; i < size; i++) {
        newArray[i] = dynamicArray[i];
    }
    newArray[size] = inString;
    size++;
    delete[] dynamicArray;
    dynamicArray = newArray;
    return;
}

bool DynamicStringArray::deleteEntry(string rmString) {
    //deletes in O(n) time 
    bool found = false;
    string* newArray = new string[size - 1];
    for (int i = 0; i < size - 1; i++) {
        if (dynamicArray[i] == rmString) {
            found = true;
            for (int j = i + 1; j < size; j++) {
                newArray[j - 1] = dynamicArray[j];
            }
            break;
        }
        else {
            newArray[i] = dynamicArray[i];
        }
    }
    if (found == false) {
        delete[] newArray;
    }
    else {
        dynamicArray = newArray;
        size--;
    }
    return found;
}

string* DynamicStringArray::getEntry(int index) {
    if (index > size) {
        return nullptr;
    }
    return dynamicArray + index;
}

DynamicStringArray& DynamicStringArray::operator=(const DynamicStringArray& rightOp) {
    if (this == &rightOp)return *this;
    delete[] dynamicArray;
    string* temp = new string[rightOp.size];
    for (int i = 0; i < rightOp.size; i++) {
       temp[i] = rightOp.dynamicArray[i];
    }
    dynamicArray = temp;
    size = rightOp.size;
    return *this;
}

int DynamicStringArray::getStringArraySize(void) {
    return size;
}

DynamicStringArray::~DynamicStringArray() {
    if (dynamicArray != nullptr) {
        delete[] dynamicArray;
        dynamicArray = nullptr;
    }

}