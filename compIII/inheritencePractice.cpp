#include <iostream>
#include <string>
using namespace std;

class Employee{
  public:
    //constructor
    Employee(): _name("unknown"), _payRate(0){}
    Employee(string name, double payRate) : _name(name), _payRate(payRate){}
  //getters
    string getName(void)const{return _name; }
    double getpayRate(void) const {return _payRate; }
    //helper
    double calcPay(int hours) const {
        return _payRate * hours;
    }
  private:
  string _name;
  double _payRate; 
};

class Manager : public Employee{
    public:
    Manager():Employee(){};
    Manager(string name, double payRate):Employee(name, payRate){}
    Manager(string name, double payRate, bool isSalaried):Employee(name, payRate), 
    _isSalaried(isSalaried){}
    private:
    bool _isSalaried = false;
};

ostream& operator<<(ostream& out, const Employee& one);

int main(int argc, char* argv[]){
    Employee john("John", 15.00);
    Manager mike("Mike", 3000, true);

    cout << john << endl;

    return 0;
}

ostream& operator<<(ostream& out, const Employee& one){
    out << one.getName() << " is an employee and the pay rate is: " <<
    one.getpayRate();
    return out;
}