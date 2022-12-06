#include <iostream>
#include <string>

// using declarations
using std::ostream;
using std::cout;
using std::endl;
using std::string;


class PayKind { // base class - no member variables
	public:
		void output(ostream& out) const { out << *this; }
				
	friend ostream& operator<< (ostream&, const PayKind&);
};

// Add the EmployeeKind base class (with no member variables). Declare and implement any
//additional functions required by EmployeeKind
class EmployeeKind {
    public:
        void output(ostream& out) const {out << *this;}
    friend ostream& operator<<(ostream&, const EmployeeKind&);
};

// • Add the PartTime class as a derived class of EmployeeKind (with one member variable, an
// unsigned called _maxHours). Declare and implement any additional functions required by
// PartTime.

class PartTime : public EmployeeKind {
    public:
        // constructor/destructor
        PartTime() : _maxHours(0) {}
        PartTime(unsigned hours) : _maxHours(hours) {}
        ~PartTime() {cout << "PartTime destructor Called\n";}

        //accessor function
        unsigned getMaxHours() const {return _maxHours; }
        void output(ostream& out) const {out << *this; }

    private:
        unsigned _maxHours;
    friend ostream& operator<< (ostream&, const PartTime&);
};

// Add the PerCourse class as a derived class of the PayKind class. PerCourse will have one
// member variable, an unsigned called _feePerCourse. Declare and implement any additional
// functions required by PerCourse.

class PerCourse : public PayKind { //derived class
    public:
        //constructor/destructor 
        PerCourse() : _feePerCourse(0) {}
        PerCourse(unsigned hourly) : _feePerCourse(hourly){} 
        ~PerCourse() {cout << "PerCourse destructor callled\n"; }

        //accessor function
        unsigned getPerCourse() const {return _feePerCourse;}

        void output(ostream& out) const {out << *this;}

    friend ostream& operator<< (ostream&, const PerCourse&);
    
    private:
        unsigned _feePerCourse;
};
class Salaried : public PayKind { // derived class
	public:
		// constructors/destructor
	    Salaried() : _annualSalary(0) {}	    
	    Salaried(unsigned salary) : _annualSalary(salary) {}
		~Salaried() { cout << "Salaried destructor called\n"; }
	
		// accessor functions
		unsigned getSalary() const { return _annualSalary; }
		
		void output(ostream& out) const { out << *this; }
				
	friend ostream& operator<< (ostream&, const Salaried&);
	
	private:
		unsigned _annualSalary;
};


class Hourly : public PayKind { // derived class
	public:
		// constructors/destructor
	    Hourly() : _hourlyRate(0) {}
	    Hourly(unsigned hourlyRate) : _hourlyRate(hourlyRate) {}
		~Hourly() { cout << "Hourly destructor called\n"; }
	
		// accessor functions
		unsigned getHourlyRate() const { return _hourlyRate; }
		
		void output(ostream& out) const { out << *this; }
				
	friend ostream& operator<< (ostream&, const Hourly&);
	
	private:
		unsigned _hourlyRate;
};


ostream& operator<< (ostream& out, const PayKind& p) {
    out << "Paykind (no member variables)\n" << endl;

    return out;
}

ostream& operator<< (ostream& out, const Salaried& s) {
    out << "Salary:\t\t" << s.getSalary() << endl;

    return out;
}

ostream& operator<< (ostream& out, const Hourly& s) {
    out << "Hourly Rate:\t" << s.getHourlyRate() << endl;

    return out;
}


class UMLPerson { // base class
	public:
		// constructors and destructor
	    UMLPerson() : _firstName("NoName"), _lastName("NoName"), _address("NoAddress"), _IDNumber_(0) {}
		
        UMLPerson(string firstName, string lastName, string address, unsigned _IDNumber) :
			_firstName(firstName), _lastName(lastName), _address(address), _IDNumber_(_IDNumber) {}
			
		UMLPerson(const UMLPerson&); // copy constructor
			
		~UMLPerson();
		
		// accessor functions
	    string getFirstName() const { return _firstName; }
        string getLastName() const { return _lastName; }
		string getAddress() const { return _address; }
		unsigned get_IDNumber() const { return _IDNumber_; }
		
		void output(ostream& out) const { out << *this; }
				
	friend ostream& operator<< (ostream&, const UMLPerson&);
	
	private:
	    string _firstName;
        string _lastName;
        string _address;
		unsigned _IDNumber_;
};


class Student : public UMLPerson { // derived class
    public:
		// constructors and destructor
        Student() : UMLPerson() { _GPA = 0.0; _smajor = "Undeclared"; _advisorName = "NoName"; }
		
        Student(string firstName, string lastName, string address, unsigned _IDNumber,
                double GPA, string smajor, string advisorName);
	    
	    Student(const Student&); // copy constructor
				
		~Student();
        
		void output(ostream& out) const { out << *this; }
		
		// accessor functions
	    double getGPA() const { return _GPA; }
        string getSmajor() const { return _smajor; }
		string getAdvisorName() const { return _advisorName; }
		
	friend ostream& operator<< (ostream&, const Student&);
        
    private:
		double _GPA;
        string _smajor;
        string _advisorName;
};


class Undergrad : public Student { // derived class
    public:
		// constructors and destructor
        Undergrad() : Student() { _classRank = "NoRank"; }
		
        Undergrad(string firstName, string lastName, string address, unsigned _IDNumber,
                double GPA, string smajor, string advisorName, string classRank);
	    
	    Undergrad(const Undergrad&); // copy constructor
				
		~Undergrad();
        
		void output(ostream& out) const { out << *this; }
		
		// accessor functions
		string getClassRank() const { return _classRank; }
		
	friend ostream& operator<< (ostream&, const Undergrad&);
        
    private:
		string _classRank; // freshman, sophomore, junior, or senior
};


class Grader : public Undergrad, public Hourly { // derived class
    public:
		// constructors and destructor
        Grader() : Undergrad() { _classNumber = "NoClassNumber"; }
		
        Grader(string firstName, string lastName, string address, unsigned _IDNumber,
               double GPA, string smajor, string advisorName, string classRank,
			   string classNumber, unsigned hourlyRate);
	    
	    Grader(const Grader&); // copy constructor
				
		~Grader();
        
		void output(ostream& out) const { out << *this; }
		
		// accessor functions
		string getClassNumber() const { return _classNumber; }
		
	friend ostream& operator<< (ostream&, const Grader&);
        
    private:
		string _classNumber; // e.g., COMP.2010
};


class Employee : public UMLPerson { // derived class
    public:
		// constructors and destructor
        Employee() : UMLPerson() { _SSN = "NoSSN"; }
		
        Employee(string firstName, string lastName, string address, unsigned _IDNumber,
				 string SSN);
	    
//	    Employee(const Employee&); // copy constructor
				
		~Employee() { cout << "Employee destructor called\n"; }
        
		void output(ostream& out) const { out << *this; }
		
		// accessor functions
		string getSSN() const { return _SSN; }
		
	friend ostream& operator<< (ostream&, const Employee&);
        
    private:
        string _SSN;
};


class Faculty : public Employee { // derived class
    public:
		// constructors and destructor
        Faculty() : Employee() { _department = "NoDepartment"; }
		
        Faculty(string firstName, string lastName, string address, unsigned _IDNumber,
				string SSN, string department);
	    
//	    Faculty(const Faculty&); // copy constructor
				
		~Faculty() { cout << "Faculty destructor called for " << getFirstName() + " " + getLastName() << endl; }
        
		void output(ostream& out) const { out << *this; }
		
		// accessor functions
		string getDepartment() const { return _department; }
		
	friend ostream& operator<< (ostream&, const Faculty&);
        
    private:
        string _department;
};

// • Add the Adjunct class as a derived class of Faculty, PerCourse, and PartTime (with one
// member variable, an unsigned called _maxCourses). Declare and implement any additional
// functions required by Adjunct.
class Adjunct : public Faculty, public PerCourse,public PartTime {
    public:
        //constructors and destructor
        Adjunct() : Faculty(), PerCourse(), PartTime() {_maxCourses = 0;}
        Adjunct(string fistname, string lastName, string address, unsigned _IDNumber, 
        string SSN, string department, string rank, unsigned hours, unsigned courseFee,  unsigned maxCourse);
        //TODO:
        //destructor
        ~Adjunct(){cout << "Adjunct Destructor called\n";}
        //accessors
        unsigned getMaxCourses()const {return _maxCourses;}

        void output(ostream& out) const {out << *this; }

    friend ostream& operator<< (ostream&, const Adjunct&);

    private:
    unsigned _maxCourses;
};


class NTT : public Faculty, public Salaried { // derived class
    public:
		// constructors and destructor
        NTT() : Faculty(), Salaried() { _rank = "NoRank"; }
		
        NTT(string firstName, string lastName, string address, unsigned _IDNumber,
			string SSN, string department, string rank, unsigned salary);
	    
//	    NTT(const Faculty&); // copy constructor
				
		~NTT() { cout << "NTT destructor called for " << getFirstName() + " " + getLastName() << endl; }
        
		void output(ostream& out) const { out << *this; }
		
		// accessor functions
		string getRank() const { return _rank; }
		
	friend ostream& operator<< (ostream&, const NTT&);
        
    private:
        string _rank; // lecturer or senior lecturer
};


UMLPerson::UMLPerson(const UMLPerson& p) {
    // make an independent copy of any dynamic member variables of UMLPerson here
    _firstName = p._firstName;
    _lastName  = p._lastName;
    _address = p._address;
    _IDNumber_ = p._IDNumber_;
    cout << "UMLPerson copy constructor called for \"" << _firstName << " " << _lastName << "\"\n";
}

UMLPerson::~UMLPerson() {
	// delete any dynamic data members for UMLPerson here
	cout << "UMLPerson destructor called for \"" << _firstName << " " << _lastName << "\"\n";
}

Student::Student(string firstName, string lastName, string address, unsigned _IDNumber,
                 double GPA, string smajor, string advisorName)
	: UMLPerson(firstName, lastName, address, _IDNumber)
{
	_GPA = GPA;
    _smajor = smajor; 
	_advisorName = advisorName;
}

Student::Student(const Student& s) : UMLPerson(s) {
    // make an independent copy of any dynamic member variables of Student here
    _GPA = s._GPA;
    _smajor = s._smajor;
    _advisorName = s._advisorName;
	
    cout << "Student copy constructor called for \""
		 << s.getFirstName() << " " << s.getLastName() << "\"\n";
}

Student::~Student() {
	// delete any dynamic data members for Student here
	cout << "Student destructor called for \"" << getFirstName() << " " << getLastName() << "\"\n";
}

Undergrad::Undergrad(string firstName, string lastName, string address, unsigned _IDNumber,
                     double GPA, string smajor, string advisorName, string classRank)
	: Student(firstName, lastName, address, _IDNumber, GPA, smajor, advisorName)
{
	_classRank = classRank;
}



Undergrad::Undergrad(const Undergrad& u) : Student(u) {
    // make an independent copy of any dynamic member variables of Student here
    _classRank = u._classRank;
	
    cout << "Undergrad copy constructor called for \""
		 << u.getFirstName() << " " << u.getLastName() << "\"\n";
}

Undergrad::~Undergrad() {
	// delete any dynamic data members for Student here
	cout << "Undergrad destructor called for \"" << getFirstName() << " " << getLastName() << "\"\n";
}

Grader::Grader(string firstName, string lastName, string address, unsigned _IDNumber,
               double GPA, string smajor, string advisorName, string classRank,
			   string classNumber, unsigned hourlyRate)
	: Undergrad(firstName, lastName, address, _IDNumber, GPA, smajor, advisorName, classRank),
	  Hourly(hourlyRate)
{
	_classNumber = classNumber;
}

Grader::Grader(const Grader& g) : Undergrad(g), Hourly(g) {
    // make an independent copy of any dynamic member variables of Student here
    _classNumber = g._classNumber;
	
    cout << "Grader copy constructor called for \""
		 << g.getFirstName() << " " << g.getLastName() << "\"\n";
}

Grader::~Grader() {
	// delete any dynamic data members for Student here
	cout << "Grader destructor called for \"" << getFirstName() << " " << getLastName() << "\"\n";
}

Employee::Employee(string firstName, string lastName, string address, unsigned _IDNumber,
                   string SSN)
	: UMLPerson(firstName, lastName, address, _IDNumber)
{
	_SSN = SSN;
}

Faculty::Faculty(string firstName, string lastName, string address, unsigned _IDNumber,
                 string SSN, string department)
	: Employee(firstName, lastName, address, _IDNumber, SSN)
{
	_department = department;
}

Adjunct::Adjunct(string firstName, string lastName, string address, unsigned _IDNumber, 
        string SSN, string department, string rank, unsigned hours, unsigned courseFee, unsigned maxCourse) 
        : Faculty(firstName, lastName, address, _IDNumber, SSN, department) ,
        PerCourse(courseFee), PartTime(hours){
            _maxCourses = maxCourse;
}

NTT::NTT(string firstName, string lastName, string address, unsigned _IDNumber,
         string SSN, string department, string rank, unsigned salary)
	: Faculty(firstName, lastName, address, _IDNumber, SSN, department), Salaried(salary)
{
	_rank = rank;
}

ostream& operator<< (ostream& out, const UMLPerson& p) {
    out << "First Name:\t" << p._firstName << endl
        << "Last Name:\t" << p._lastName << endl
        << "Address:\t" << p._address << endl
        << "ID Number:\t" << p._IDNumber_ << endl;
        
    return out;
}

ostream& operator<< (ostream& out, const Student& s) {
	s.UMLPerson::output(out); // display the UMLPerson variables
	
    out << "GPA:\t\t" << s.getGPA() << endl
        << "Major:\t\t" << s.getSmajor() << endl
        << "Advisor Name:\t" << s.getAdvisorName() << endl;
        
    return out;
}

ostream& operator<< (ostream& out, const Undergrad& u) {
	u.Student::output(out); // display the Student variables
	
    out << "Class Rank:\t" << u.getClassRank() << endl;
        
    return out;
}

ostream& operator<< (ostream& out, const Grader& u) {
	u.Undergrad::output(out); // display the Student variables
	
    out << "Class Number:\t" << u.getClassNumber() << endl;
	
	u.Hourly::output(out); // display the Hourly variables
        
    return out;
}

ostream& operator<< (ostream& out, const Employee& e) {
	e.UMLPerson::output(out); // display the UMLPerson variables
	
    out << "SSN:\t\t" << e.getSSN() << endl;
        
    return out;
}

ostream& operator<< (ostream& out, const Faculty& f) {
	f.Employee::output(out); // display the Employee variables
	
    out << "Department:\t" << f.getDepartment() << endl;
        
    return out;
}

ostream& operator<< (ostream& out, const NTT& n) {
	n.Faculty::output(out); // display the Faculty variables
	
    out << "Rank:\t\t" << n.getRank() << endl;
	
	n.Salaried::output(out); // display the Salary variables

    return out;
}


int main (void) {
	UMLPerson p;
	cout << "UMLPerson():\n" << p << endl;
	
    Student s;
    cout << "Student():\n" << s << endl;
	
	Undergrad u;
	cout << "Undergrad():\n" << u << endl;
	
	Grader g;
	cout << "Grader():\n" << g << endl;
    
    Undergrad s1("Sally", "Brown", "110 Canal Street", 12345678, 4.0, "CS", "Tom Wilkes", "senior");
    Undergrad s2("Jimmy", "Smith", "99 Canal Street", 87654321, 3.0, "CS", "Tom Wilkes", "freshman");
 
    cout << "Undergrad s1(Sally...):\n" << s1 << endl;
	cout << "Undergrad s2(Jimmy...):\n" << s2 << endl;
	
	Grader g1("John", "Doe", "89 Canal Street", 54329876, 3.5, "CS", "Tom Wilkes", "junior",
			  "COMP.2010", 25.00);
	cout << "Grader g1(John...):\n" << g1 << endl;
	
	Grader g2(g1); // invoke copy constructor
	cout << "Grader g2(copy of g1 - John...):\n" << g2 << endl;
	
	NTT n1("Tom", "Wilkes", "Foo Street", 52901256, "123-45-6789", "Computer Science", "Assistant Teaching Professor", 12345);
	cout << "NTT Faculty n1(Tom...):\n" << n1 << endl;

    return 0;
}
