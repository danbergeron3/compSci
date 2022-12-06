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
        //constructors
        Date();
        Date(int month);
        Date(string month);

        //mutators
        void setDateMonth(int month);

        //accessors
        Month getDatemonth(void);
        //helpers
        void outputDateAsInt(ostream& outStream);
        void outputDateAsString(ostream& outStream);
    private:
        int day;
        Month month;
        int year;

};

int main(int argc, char* argv[]){
    
    return 0;
}

void Date::outputDateAsInt(ostream& outStream){
    outStream << month.MonthToInt() << "/" << day << "/" << year;
    return;
}

void Date::outputDateAsString(ostream& outStream){
    outStream << month.MonthToString() << " "<< day << ", " << year;
    return;
}

