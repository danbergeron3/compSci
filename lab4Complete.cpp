#include <iostream>
#include <string>

using namespace std;


// ***** Add your Date class definition and driver program at the end of this file
// (at about line 107). *****

// The Month class provided below is a "helper" class for your Date class.
// Note that although both classes are defined in this single compilation unit (file),
// we are not nesting the Month class in the Date class or vice versa.

class Month {
	friend class Date;
	
	friend ostream& operator<< (ostream&, Month);
	
    private:
        enum EMonth { Jan=1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec };
            
        Month() : _month(Jan) {} // default constructor
        Month(int im) : _month( static_cast<EMonth>(im) ) {} // value constructor
        
        void setMonth(string m) { _month = StringToEMonth(m); } // mutator functions
		void setMonth(int im) { _month = static_cast<EMonth>(im); }
		
		/* Private helper member functions */
        EMonth StringToEMonth(string);
        int MonthToInt() { return static_cast<int>(_month); }
		string MonthToString();
		string MonthToString2();

	    EMonth _month;
};

/* Definitions of helper member functions for class Month */

Month::EMonth Month::StringToEMonth(string m) {
	if (m == "Jan") return Jan;
	else if (m == "Feb") return Feb;
	else if (m == "Mar") return Mar;
	else if (m == "Apr") return Apr;
	else if (m == "May") return May;
	else if (m == "Jun") return Jun;
	else if (m == "Jul") return Jul;
	else if (m == "Aug") return Aug;
	else if (m == "Sep") return Sep;
	else if (m == "Oct") return Oct;
	else if (m == "Nov") return Nov;
	else if (m == "Dec") return Dec;
	else {
		cerr << "Month::StringToMonth: Invalid input month \"" << m << "\"\n";
		exit(1);
	}
}

string Month::MonthToString() {
	switch (_month) {
		case Jan: return "Jan";
		case Feb: return "Feb";
		case Mar: return "Mar";
		case Apr: return "Apr";
		case May: return "May";
		case Jun: return "Jun";
		case Jul: return "Jul";
		case Aug: return "Aug";
		case Sep: return "Sep";
		case Oct: return "Oct";
		case Nov: return "Nov";
		case Dec: return "Dec";
		default:
			cerr << "MonthToString: invalid input month \'" << _month << "\'\n";
			exit(1);
	}
}

string Month::MonthToString2() {
	switch (_month) {
		case Jan: return "January";
		case Feb: return "February";
		case Mar: return "March";
		case Apr: return "April";
		case May: return "May";
		case Jun: return "June";
		case Jul: return "July";
		case Aug: return "August";
		case Sep: return "September";
		case Oct: return "October";
		case Nov: return "November";
		case Dec: return "December";
		default:
			cerr << "MonthToString: invalid input month \'" << _month << "\'\n";
			exit(1);
	}
}

/* Definition of friend function operator<< */

ostream& operator<< (ostream& out, Month m) {
	out << m.MonthToString2();
	return out;
}


// ***** Add your Date class definition and driver program below. *****

class Date{
    public:
		//friend 
		friend ostream& operator<< (ostream& out, Date &date);
		friend istream& operator>> (istream& in, Date &date);
		friend const Date& operator++(Date &op);
        //default constructors
        Date();
		//value constructor
        Date(int imonth);
        Date(string imonth);
		Date(int imonth, int iday, int iyear);
		Date(string imonth, int iday, int iyear);

        //mutators
        void setDateMonth(int imonth);

        //accessors
        string getDateMonthAsString2(void);
		int getMonthASInt(void);
        //helpers
        void outputDateAsInt(ostream& outStream);
        void outputDateAsString(ostream& outStream);
    private:
		//member variables
        int day;
        Month month;
        int year;
};

//++m1;prefix: m1 should be incremented
//new value of m1
const Date& operator++(Date &op);

int main(int argc, char* argv[]){
    Date d1, d2(2, 1, 2018), d3("Mar", 1, 2018);
	cout << "With the following declarations:\n";
	cout << "	Date d1, d2(2, 1, 2018), d3(\"Mar\", 1, 2018);\n";
	cout << "...and using operator<< :\n";
	cout << "d1 == " << d1 << endl;
	cout << "d2 == " << d2 << endl;
	cout << "d3 == " << d3 << endl << endl;//FIX ME
	cout << "After d3.setMonth(4):\n";
	d3.setDateMonth(4);
	cout << "d3 == " << d3 << endl << endl;
	cout << "With the following declaration:\n";
	Date d4(12, 31, 2018);
	cout << "	Date d4(12, 31, 2018);\n";
	cout << " d4.outputDateAsInt(cout) outputs "; 
	d4.outputDateAsInt(cout);
	cout << endl;
	cout << "d4.outputDateAsString(cout) outputs ";
	d4.outputDateAsString(cout);
	cout << endl;
	++d4;
	cout << "++d4 == " << d4;

	


    return 0;
}

Date::Date(){
	day = 1;
	month = 1;
	year = 2018;
}

Date::Date(int imonth){
	day = 1;
	Month current; 
	month.setMonth(imonth);
	year = 2018;
}

Date::Date(string imonth){
	day = 1;
	Month current; 
	month = current.StringToEMonth(imonth);
	year = 2018;
}

Date::Date(int imonth, int iday, int iyear){
	Month temp(imonth);
	month = temp;
	day = iday;
	year = iyear;
}

Date::Date(string imonth, int iday, int iyear){
	Month temp;
	temp.setMonth(imonth);
	day = iday;
	year = iyear;
	month = temp;
}

void Date::outputDateAsInt(ostream& outStream){
    outStream << month.MonthToInt() << "/" << day << "/" << year ;
    return;
}

void Date::outputDateAsString(ostream& outStream){
    outStream << month.MonthToString() << " "<< day << ", " << year;
    return;
}

void Date::setDateMonth(int imonth){
	month.setMonth(imonth);
}

string Date::getDateMonthAsString2(void){
	return month.MonthToString2();
	
}

ostream& operator<<(ostream& out, Date &date){
	out << date.getDateMonthAsString2(); 
	out << " ";
	out << date.day;
	out << ", "; 
	out << date.year;
	return out;
}

istream& operator>> (istream& in, Date &date){
	int num;
	in >> num;
	date.setDateMonth(num);
	
	char c;
	in >> c;
	if(c != '/'){
		cout << "Failed to set Date.\n";
		date.setDateMonth(0);
		return in;
	}

	in >> num;
	if(num <= 0 || num > 31)
	{
		cout << "Failed to set Date.\n";
		date.setDateMonth(0);
		date.day = 0;
		return in;
	} 
	date.day = num;

	in >> c;
	if(c != '/'){
		cout << "Failed to set Date.\n";
		date.setDateMonth(0);
		return in;
	}

	in >> num;
	if(num < 0)
	{
		cout << "Failed to set Date.\n";
		date.setDateMonth(0);
		date.day = 0;
		return in;
	} 
	date.day = num;

	return in;
}

const Date& operator++(Date &op){
	int temp = op.year;
	++temp;
	op.year = temp;
	return op;
}

int Date::getMonthASInt(void){
	return month.MonthToInt();
}