/***********************************************
Author: Daniel Bergeron 
Date: 11/21/2022
Purpose: Practice big three and expectation handling
Sources of Help: class, stackoverflow
Time Spent: 2hr
************************************************
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
Date:11/21/2022
Name:Daniel Bergeron
*/
#include <iostream>
#include <string>
using namespace std;

//drivers
void testPFArrayD(void);
void testException(void);

const int START_SIZE = 50;

class OutOfRange{
public:
    //constructors
    OutOfRange() : errorValue(-1), errorMessage("Error: out of Range"){}
    OutOfRange(int _error, string _errorMessage) : errorValue(_error), errorMessage(_errorMessage){}

    //accesors
    int index(void){ return errorValue; }
    void err(void){cout << errorMessage; }
private:
    int errorValue;
    string errorMessage;
};
//Objects of this class are partially filled arrays of doubles.
class PFArrayD
{
public:
    //Default constructor: Initializes with a capacity of START_SIZE.
    PFArrayD();
    //Value Constructor
    PFArrayD(int capacityValue);
    //Copy Constructor
    PFArrayD(const PFArrayD& pfaObject);
    
    //muttators & helpers

    void addElement(double element);
    //Precondition: The array is not full.
    //Postcondition: The element has been added.
    
    bool full( ) const { return (capacity == used); }
    //Returns true if the array is full, false otherwise.
    
    int getCapacity( ) const { return capacity; }
    //returns capacity

    int getNumberUsed( ) const { return used; }
    //returns used

    void emptyArray( ){ used = 0; }
    //Empties the array.
    
    double& operator[](int index);
    //Read and change access to elements 0 through numberUsed - 1.
    
    PFArrayD& operator =(const PFArrayD& rightSide);
    //overloads = operator

    //destructor
    ~PFArrayD( );
private:
    double *a; //for an array of doubles.
    int capacity; //for the size of the array.
    int used; //for the number of array positions currently in use.
    
};

int main(int argc, char *argv[])
{
     cout << "This program tests the class PFArrayD.\n";
     
     char ans;
     do
     {
         testPFArrayD();
         cout << "\nExpectation Testing Section: \n\n";
         testException();
         cout << "Test again? (y/n) ";
         cin >> ans;
     }while ((ans == 'y') || (ans == 'Y'));
     
    return 0;
}

void testException(void){
    //block1: build PFArray around user input
    int test_value = 0;
    cout << "Please enter the PFArray capacity you want to test\n";
    cin >> test_value;
    PFArrayD testArray(test_value);

    //block2: generates PFARRAY
    double x;
    cout << "The following PFArray will be used to test exceptions.\n";
    cout << "PFArray: ";
    for(int i = 0; i < (testArray.getCapacity() / 2); i++){
        x = static_cast<double>(i);
        x = x /(static_cast<double>(i) + 2.00);
        testArray.addElement(x); 
        cout << testArray[i] << ", ";
    }
    cout << endl;
    cout << "size: " << testArray.getNumberUsed() << " capacity: " << testArray.getCapacity() << endl;

    //block 3: Allows user to test valid and invalid indices
    int testIndex;
    double value;
    char ans;
    do{
        cout << "Enter test index: \n";
        cin >> testIndex;
        try{
            value = testArray[testIndex];
            cout << "The Value at the index " << testIndex << " is " << value << '.' << endl;
            cout << "Try an invalid index!\n";
        }
        catch(OutOfRange ex){
            cout << "Expectation Caught.\n";
            ex.err();
            cout << "index: " << ex.index() << endl;
        }
        cout << "Do you want to test another input?(y/n): ";
        cin >> ans;
    }while(ans == 'y' || ans == 'Y');

    //block 4: shows what happens when you add to a full PFArray;
    cout << "\nTesting Expectations when PFArray is full\n" << endl; 
    for(int i = testArray.getNumberUsed(); i < testArray.getCapacity(); i++){
        testArray.addElement(0.0);
    }
    try{
        testArray.addElement(1.1);
    }
    catch(OutOfRange ex){
        cout << "Expectation Caught.\n";
        ex.err();
        cout << " at index: " << ex.index() << endl;
    }
    
    return;
}

void testPFArrayD( )
{
    int cap;
    cout << "Enter capacity of this super array: ";
    cin >> cap;
    PFArrayD temp(cap);
    
    cout << "Enter up to " << cap << " nonnegative numbers.\n";
    cout << "Place a negative number at the end.\n";
    
    double next;
    cin >> next;
    while ((next >= 0) && (!temp.full( )))
    {
        temp.addElement(next);
        cin >> next;
    }
    
    cout << "You entered the following "
    << temp.getNumberUsed( ) << " numbers:\n";
    int index;
    int count = temp.getNumberUsed( );
    for (index = 0; index < count; index++)
        cout << temp[index] << " ";
    cout << endl;
    cout << "(plus a sentinel value.)\n";
}

double& PFArrayD::operator[](int index){
    if(index < 0 || index >= used){
        throw OutOfRange(index, "Error: index out of range. ");
    }
    return a[index];           
}

PFArrayD::PFArrayD(){
    capacity = START_SIZE;
    used = 0;
    a = new double[capacity];
}

PFArrayD::PFArrayD(int capacityValue){
    capacity = capacityValue;
    used = 0;
    a = new double[capacity];
}

PFArrayD::PFArrayD(const PFArrayD& pfaObject){
    capacity = pfaObject.capacity;
    used = pfaObject.used;
    a = new double[capacity];
    for(int i = 0; i < used; i++){
        a[i] = pfaObject.a[i];//revisit
    }
}

void PFArrayD::addElement(double element){
    if(full())
        throw OutOfRange(getCapacity(), "Error: PFArray is full");   
    a[used]= element;
    used++;  
    return;
}

PFArrayD& PFArrayD::operator =(const PFArrayD& rightSide){
    capacity = rightSide.used;
    used = rightSide.used;
    delete [] a;
    a = new double[capacity];
    for(int i = 0; i < used; i++){
        a[i] = rightSide.a[i];
    }
    return *this;
}

PFArrayD::~PFArrayD( ){
    delete [] a;
    a = nullptr;
}