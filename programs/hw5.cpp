/***********************************************
Author: Daniel Bergeron
Date: 9/30/2022
Purpose: The purpose of this program is to create a rational number
class
Sources of Help: class recordings
Time Spent: 5hr
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
Date:9/30/2022
Name:Daniel Bergeron
*/
#include <iostream>
using namespace std;

class rational{
public: 
    //constructor
    rational(int wholenumber);
    rational(int numerator, int denominator);
    rational();

    //accsesor
    int getNumerator(void) const;
    int getDenominator(void) const;
    //mutator
    void setNumerator(int num);
    void setDenominator(int denom);
    void setRational(int num, int denom);

private:
    int numerator;
    int denominator;
    //helpers
    //is passed to valid integers
    //returns gcd.
    int leastCommonDivider(int uA, int uB);
    // passed too integers
    // returns normilized rational
    void normalize(int num, int denom);
    
};
//overloads arithmetic operators with ability to use rational class
const rational operator+(const rational &leftOprand, const rational &rightOprand);
const rational operator-(const rational &leftOprand, const rational &rightOprand);
const rational operator*(const rational &leftOprand, const rational &rightOprand);
const rational operator/(const rational &leftOprand, const rational &rightOprand);

//overloads comparison operators for rational class use
const bool operator==(const rational &leftOprand, const rational &rightOprand);
const bool operator<=(const rational &leftOprand, const rational &rightOprand);
const bool operator>=(const rational &leftOprand, const rational &rightOprand);
const bool operator<(const rational &leftOprand, const rational &rightOprand);
const bool operator>(const rational &leftOprand, const rational &rightOprand);

//overloads extraction & insertion operators for rational class
ostream& operator<<(ostream &outStream, const rational &rightOprand);
istream& operator>>(istream &intStream, rational &rightOprand);

int main(int argc, char* argv[]){
    rational r1, r2, r3;
    
    //tests constructors, mutators, and accessors
    cout << "Test 1: \n\n";
    cout << "The non-default constructors\n";
    rational r4(54);
    cout << r4 << endl;
    rational r5(54, 22);
    cout << r5 << endl;
    cout << "The getter functions\n";
    cout << r1.getNumerator() << " / " << r1.getDenominator() << endl;
    cout << "The setter functions\n";
    r1.setNumerator(4);
    r1.setDenominator(2);
    cout << r1.getNumerator() << " / " << r1.getDenominator() << endl;
    cout << "When denominator is set to 0\n";
    r1.setDenominator(0);

    //tests operators that where overloaded, also tests setter fo rational
    //& normilization funtion
    cout << "\n\nTest 2: \n\n";

    cout << "How many rounds of testing enter number: \n" 
    << "Note: Syntax is not checked in this driver\n";
    int n;
    char keep = 'n';
    cin >> n;
    for(int i =0; i < n; i++){
        if(keep == 'n'){
            cout << "Enter two fractions \'a/b\': ";
            cin >> r1 >> r2;
            cout << r1 << " vs " << r2 << endl;
        }
        cout << "Choose the test case: \n";
        cout << "[0] will break loop\n" 
        << "[1] test addtion\n"
        << "[2] test subtraction\n"
        << "[3] test multiplictation\n"
        << "[4} test division\n"
        << "[5] test ==\n"
        << "[6] test <=\n"
        << "[7] test >=\n"
        << "[8] test >\n"
        << "[9] test <\n?";
        
        int test;
        cin >> test;  
        if(test == 0){
            break;
        }

        switch (test){
            case 1:
                cout << r1 << " + " << r2 <<" = \n";
                r3 = r1 + r2;
                cout << r3 << endl; 
                break;
            case 2:
                cout << r1 << " - " << r2 <<" = \n";
                r3 = r1 - r2;
                cout << r3 << endl; 
                break;
            case 3:
                cout << r1 << " * " << r2 <<" = \n";
                r3 = r1 * r2;
                cout << r3 << endl; 
                break;
            case 4:
                cout << r1 << " / " << r2 <<" = \n";
                r3 = r1 / r2;
                cout << r3 << endl; 
                break;
            case 5:
                if( r1 == r2){
                cout << r1 << " does == " << r2 << endl;
                } else {
                    cout << r1 << " doesn't == " << r2 << endl;
                }       
                break;
            case 6:
                if( r1 <= r2){
                cout << r1 << " is <= " << r2 << endl;
                } else {
                    cout << r1 << " isn't <= " << r2 << endl;
                }       
                break;
            case 7:
                if( r1 >= r2){
                cout << r1 << " is >= " << r2 << endl;
                } else {
                    cout << r1 << " isn't >= " << r2 << endl;
                }       
                break;
            case 8:
                if( r1 > r2){
                cout << r1 << " is > " << r2 << endl;
                } else {
                    cout << r1 << " isn't > " << r2 << endl;
                }       
                break;
            case 9:    
                if( r1 < r2){
                cout << r1 << " is < " << r2 << endl;
                } else {
                    cout << r1 << " isn't < " << r2 << endl;
                }       
                break;         
            default:
                cout <<"You did something wrong!9\n";
                break;
        }
        if(i < n){
        cout << "Do you want to keep the same rationals y/n: ";
        cin >> keep;
        }
        
    }
    return 0;
}

rational::rational(){
    numerator = 0;
    denominator = 1;
}

rational::rational(int wholenumber){
    numerator = wholenumber;
    denominator = 1;
}

rational::rational(int num, int denom){
    numerator = num;
    denominator = denom;
    normalize(numerator, denominator);
} 

int rational::getNumerator(void)const{
    return numerator;
}

int rational::getDenominator(void) const{
    return denominator;
}

void rational::setNumerator(int num){
    numerator = num; 
    normalize(numerator, denominator);

}

void rational::setDenominator(int denom){
    if(denom == 0){
        cout << "Invalid: denominator can't be zero\n";
    } else {
        denominator = denom;
    }
    normalize(numerator, denominator);
}

void rational::setRational(int num, int denom){
    //int lcd ->least common denom 
    normalize(num, denom);
}

void rational::normalize(int num, int denom){
    int lcd = leastCommonDivider(num, denom);
    if(lcd > 1){
        numerator = num / lcd;
        denominator = denom / lcd;
    } else {
        numerator = num;
        denominator = denom;
    }
    if(numerator < 0 && denominator < 0 ||numerator > 0 && denominator < 0){
        numerator = ~num + 1;
        denominator = ~denom + 1;
    }
}

//function uses the euclidian algorythem to find the gcd of the
//greatest common denominator of the two numbers.
int rational::leastCommonDivider(int A, int B){
    //orders the numbers for algorythem
    //if it is -1 will exit because -1 converts to zero in unsigend
    int temp;
    if(A == -1 || B == -1){
        return 1;
    }
    unsigned int uA = static_cast<int>(A), uB = static_cast<int>(B);
    if(uA < uB){
        temp = uA;
        uA = uB;
        uB = temp;
    }
    if(uA != 0 && uB != 0){
        temp = uB;
        uB = uA % uB;
        uA = temp;
        temp = leastCommonDivider(uA, uB);
        return temp;
    } else {
        if(uA == 0){
            return uB;
        } else {
            return uA;
        }
    }
}

const rational operator+(const rational &leftOprand, const rational &rightOprand){
    rational sum;
    //will add fraction if they are the same else calculate,
    //lcd then add and simplify
    if(leftOprand.getDenominator() == rightOprand.getDenominator()){
        sum.setRational(leftOprand.getNumerator() + 
        rightOprand.getNumerator(), leftOprand.getDenominator());
    } else {
        int newDenominator, newNumerator;
        newDenominator = leftOprand.getDenominator() * rightOprand.getDenominator();
        newNumerator = (leftOprand.getNumerator() * rightOprand.getDenominator()) + 
        (leftOprand.getDenominator() * rightOprand.getNumerator());
        sum.setRational(newNumerator, newDenominator);
    }
    return sum;
}

const rational operator-(const rational &leftOprand, const rational &rightOprand){
    //will subtract fraction if they are the same else calculate,
    //lcd then subtract and simplify
    rational diffrence;
    if(leftOprand.getDenominator() == rightOprand.getDenominator()){
        diffrence.setRational(leftOprand.getNumerator() - 
        rightOprand.getNumerator(), leftOprand.getDenominator());
    } else {
        int newDenominator, newNumerator;
        newDenominator = leftOprand.getDenominator() * rightOprand.getDenominator();
        newNumerator = (leftOprand.getNumerator() * rightOprand.getDenominator()) - 
        (leftOprand.getDenominator() * rightOprand.getNumerator());
        diffrence.setRational(newNumerator, newDenominator);
    }
    return diffrence;
}

const rational operator*(const rational &leftOprand, const rational &rightOprand){
    rational product;
    int num = leftOprand.getNumerator() * rightOprand.getNumerator(); 
    int denom = leftOprand.getDenominator() * rightOprand.getDenominator();
    product.setRational(num,denom);
    return product;
}

const rational operator/(const rational &leftOprand, const rational &rightOprand){
    rational divisor;
    //assigns first fraction to corresponding variable num1, num2
    //assigns second fraction to reciprocal, then multiplies across 
    int num1 = leftOprand.getNumerator();
    int denom1 = leftOprand.getDenominator();
    int num2 = rightOprand.getDenominator();
    int denom2 = rightOprand.getNumerator();
    divisor.setRational(num1*num2, denom1 * denom2);
    return divisor;
}

const bool operator==(const rational &leftOprand, const rational &rightOprand){
    if(leftOprand.getNumerator() == rightOprand.getNumerator() && 
    leftOprand.getDenominator() == leftOprand.getDenominator()){
        return true;
    } else {
        return false;
    }
}
// 1/2 < 8/9 if a/b < c/d given that a * d < b * c
const bool operator<=(const rational &leftOprand, const rational &rightOprand){
    if(leftOprand.getNumerator() * rightOprand.getDenominator() <= 
    leftOprand.getDenominator() * rightOprand.getNumerator()){
        return true;
    } else {
        return false;
    }
}

const bool operator>=(const rational &leftOprand, const rational &rightOprand){
    if(leftOprand.getNumerator() * rightOprand.getDenominator() >= 
    leftOprand.getDenominator() * rightOprand.getNumerator()){
        return true;
    } else {
        return false;
    }
}

const bool operator<(const rational &leftOprand, const rational &rightOprand){
    if(leftOprand.getNumerator() * rightOprand.getDenominator() < 
    leftOprand.getDenominator() * rightOprand.getNumerator()){
        return true;
    } else {
        return false;
    }
}

const bool operator>(const rational &leftOprand, const rational &rightOprand){
    if(leftOprand.getNumerator() * rightOprand.getDenominator() > 
    leftOprand.getDenominator() * rightOprand.getNumerator()){
        return true;
    } else {
        return false;
    }
}

ostream& operator<<(ostream &outStream, const rational &rightOprand){
    outStream << rightOprand.getNumerator();
    outStream << "/";
    outStream << rightOprand.getDenominator();
    return outStream;
}

istream& operator>>(istream &inStream, rational &rightOprand){
    int num;
    char c;
    inStream >> num;
    inStream >> c;
    if(c != '/'){
        cout << "Need a \"/\".\n";
    } else {
        int denom;
        inStream >> denom;
        if(denom == 0){
            cout << "Denominator can't be zero.\n";
        } else {
            rightOprand.setRational(num, denom);
        }
    }
    return inStream;
}