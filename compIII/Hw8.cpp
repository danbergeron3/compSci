/***********************************************
Author: Daniel Bergeron
Date: 11/6/2022
Purpose: <Insert a short description of what
your program does here.>
Sources of Help: class notes, and work
Time Spent: 2hr
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
Date:11/6/2022
Name:Daniel Bergeron
*/
#include <iostream>
#include <string>
using namespace std;

class Person
{
public:
    Person() : name("None") {}
    Person(string theName) : name(theName){}
    Person(const Person& theObject);
    string getName(void) const;
    void setName(string theName){name = theName;}
    Person& operator=(const Person& rtSide);
    friend istream& operator>>(istream& inStream, Person& personObject);
    friend ostream& operator<<(ostream& outStream, const Person& pObject);
private:
    string name;
};

// Create a base class called Vehicle that has the manufacturer’s name (type string), number of
// cylinders in the engine (type int), and owner (type Person given in the code that follows). Then
// create a class called Truck that is derived from Vehicle and has additional properties, the load
// capacity in tons (type double since it may contain a fractional part) and towing capacity in pounds
// (type int). 
class Vehicle{
public:
    //Constructors
    Vehicle() : _manufacturer("Unkown Manufacturer"), _cylinders(0), _owner(Person("Unkown Owner")){}
    Vehicle(string manufacturer, int cylinders, Person& owner) : 
    _manufacturer(manufacturer), _cylinders(cylinders), _owner(owner){}
    Vehicle(const Vehicle& toCopy); 
    //accesors
    string getManufacturer(void) const {return _manufacturer; }
    int getCylinders(void) const {return _cylinders; }
    Person getOwner(void) const {return _owner; }
    //mutators
    void setOwner(Person& owner){_owner = owner; }
    void setCylinder(int cylinder){_cylinders = cylinder; }
    void setManufacturer(string manufacturer){_manufacturer = manufacturer; }
    //asignement
    const Vehicle& operator=(const Vehicle& rightOp);
    //friends
    friend ostream& operator<<(ostream& out,const Vehicle& rightOp);
private:
    string _manufacturer;
    int _cylinders;
    Person _owner;   
};

class Truck : public Vehicle{
public:
    //construct
    Truck() : Vehicle(), _towing_capIB(0), _load_capTons(0.0) {}
    Truck(string manufacturer, int cylinders, Person& owner, int towing_capIB, double load_capTons) :
    Vehicle(manufacturer, cylinders, owner), _towing_capIB(towing_capIB), _load_capTons(load_capTons){}
    Truck(const Truck& toCopy);
    //mutators/setters
    int getTowingCapacityIB(void){return _towing_capIB; }
    double getLoadCapacityTons(void){return _load_capTons; }
    void setTowingCapacityIB(int pounds){_towing_capIB = pounds; }
    void setLoadCapacityTons(double Tons){_load_capTons = Tons; }
    //assignment
    const Truck& operator=(const Truck& rightOp);
    //friends
    friend ostream& operator<<(ostream& out,const Truck& rightOp);
private:
    int _towing_capIB;
    double _load_capTons;
};
//driver
int main(int argc,char* argv[]){
    cout <<"/////////////////// Testing Person Class ////////////////\n";
    Person p1;
    cout <<"Testing default constructor: the person is: " << p1 << endl;
    Person p2("Daniel Bergeron");
    cout << "Testing constructor(string): I am: " << p2 << endl;
    Person p3(p2);
    cout << "\nTesting copy constructor: another me is: " << p3 << endl;
    cout << "Testing >> overloading: Enter your name: ";
    cin >> p1;
    cout << "Your: " << p1 << endl;
    p2 = p1;
    cout << "Testing = overloading: Another you is: " << p2 << endl;
    
    cout << "\n///////////////// Testing Vehicle Class ////////////////\n";
    cout << "// Testing default constructor: the Vehicle is:\n";
    Vehicle v1;
    cout << v1;
    cout << "Testing copy constructor(string manufacturer, int cylinders, Person& owner): for my car: \n";
    Person temp("Daniel Bergeron");
    Vehicle v2("Nissan altima", 4, temp);
    cout << v2;
    cout << "\nTesting copy constructor: my second same car: \n";
    Vehicle v3(v2);
    cout << v3;
    cout << "\nTesting = overloading: \n";
    v1 = v2;
    cout << "Your Car is: " << v1 << endl << "yourSecondCar is:" << v2 << endl;

    cout << "\n///////////////// Testing Truck Class ////////////////\n";
    cout << "Testing default constructor: the Truck is: \n"; 
    Truck t1;
    cout << t1 << endl;
    cout << "Testing constructor(string manufacturer, int cylinders, Person& owner, int towing_capIB, double load_capTons): for a truck:\n";
    Truck t2("Ford Maverick", 4, p2, 155, 2);
    cout << t2 << endl;
    cout << "Testing = overloading: ";
    t1 = t2;
    cout << "hisTruck is: " << t1 << endl;
    cout << "his same Truck is: " << t2 << endl;
    return 0;
}
//Unknown Manufactory, 0 cylinders, belongs to: Unknown Owner, load capacity: 0, towing capacity: 0
ostream& operator<<(ostream& out, const Truck& rightOp){
    out << rightOp.getManufacturer() << ", " << rightOp.getCylinders();
    out << " cylinders, belongs to: " << rightOp.getOwner() << ", load capacity: ";
    out << rightOp._load_capTons << ", towing capacity: " << rightOp._towing_capIB;
    return out;
}

const Truck& Truck::operator=(const Truck& rightOp){
    Person own = rightOp.getOwner();
    this->setOwner(own);
    this->setCylinder(rightOp.getCylinders());
    this->setManufacturer(rightOp.getManufacturer());
    this->_load_capTons = rightOp._load_capTons;
    this->_towing_capIB = rightOp._towing_capIB;
    return *this;
}
Truck::Truck(const Truck& toCopy){
    Person own = toCopy.getOwner();
    this->setOwner(own);
    this->setCylinder(toCopy.getCylinders());
    this->setManufacturer(toCopy.getManufacturer());
}

const Vehicle& Vehicle::operator=(const Vehicle& rightOp){
    this->_owner = rightOp._owner;
    this->_cylinders = rightOp._cylinders;
    this->_manufacturer = rightOp._manufacturer;
    return *this;
}
//format //Ford Van, 8 cylinders, belongs to: Sirong Lin
ostream& operator<<(ostream& out, const Vehicle& rightOp){
    out << rightOp._manufacturer << ", " << rightOp._cylinders << " cylinders, belongs to: ";
    out << rightOp._owner;
    return out;
}

Vehicle::Vehicle(const Vehicle& toCopy){
    this->_owner = toCopy._owner;
    this->_cylinders = toCopy._cylinders;
    this->_manufacturer = toCopy._manufacturer;
}

Person::Person(const Person& theObject){
    this->name = theObject.name;
}

string Person::getName(void) const{
    return name;
}

Person& Person::operator=(const Person& rtSide){
    this->name = rtSide.name;
    return *this;
}

istream& operator>>(istream& inStream, Person& personObject){
    inStream >> personObject.name;
    personObject.name += ' ';
    string last;
    inStream >> last;
    personObject.name += last;
    return inStream;
}

ostream& operator<<(ostream& outStream, const Person& pObject){
    outStream << pObject.name;
    return outStream;
}