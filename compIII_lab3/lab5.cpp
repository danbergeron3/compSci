//std::cout.setf(std::ios::fixed);
//std::cout.setf(std::ios::showpoint);
//std::cout.precision(2);
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class ComplexNumber{
    public:
    //constructors
    ComplexNumber();
    ComplexNumber(double real, double imaginary);
    //accessors
    double getRealNumber(void) const;
    double getImaginaryNumber(void) const;
    //mutators 
    void setRealNumber(double real);
    void setImaginaryNumber(double imaginary);
    void SetComplexNumber(double real, double imaginary);
    //helpers
    friend istream& operator>>(istream& instream, ComplexNumber cNumber);
    friend ostream& operator<<(ostream& ostream, ComplexNumber cNumber);
    
    private:
    double real;
    double imaginary;
};

const ComplexNumber operator+(const ComplexNumber& leftOp,const ComplexNumber& rightOp);
const ComplexNumber operator-(const ComplexNumber& leftOp,const ComplexNumber& rightOp);
const ComplexNumber operator*(const ComplexNumber& leftOp,const ComplexNumber& rightOp);
const ComplexNumber operator/(const ComplexNumber& leftOp,const ComplexNumber& rightOp);
const ComplexNumber operator!(const ComplexNumber& rightOp);
istream& operator>>(istream& instream, ComplexNumber cNumber);
ostream& operator<<(ostream& ostream, ComplexNumber cNumber);

int main(int argc, char* argv[]){
    ComplexNumber c1, c2(1, 2), c3(3,4);
    cout << "Value of c1 (default constructor):\n";
    cout << "c1.Re() == " << c1.getRealNumber() << ", c1.Im() == " << c1.getImaginaryNumber() << endl;
    cout << "Value of c2 (value constructor):\n";
    cout << "c1.Re() == " << c2.getRealNumber() << ", c1.Im() == " << c2.getImaginaryNumber() << endl; 
    cout << "c2 + c3 (" << c2 << " + " << c3 << ") == " << c2 + c3 << endl;
    cout << "c2 - c3 (" << c2 << " - " << c3 << ") == " << c2 - c3 << endl; 
    cout << "c2 * c3 (" << c2 << " * " << c3 << ") == " << c2 * c3 << endl; 
    cout << "c2 / c3 (" << c2 << " / " << c3 << ") == " << c2 / c3 << endl; 
    cout << "(c2/c3) + (c2*c3) == " << (c2/c3) + (c2*c3) << endl;
    cout << "Conjugate of c2 (1+2i) == " << !c2 << endl;

    vector<ComplexNumber>v1;
    //vector loops
    cout <<"\nVector output using indexed for-loop:\n";
    for(int i = 0; i <= 9; i++){
        ComplexNumber cNum(i, 2*i);
        v1.push_back(cNum);
        cout << v1[i] << endl;
    }
    cout <<"\nVector output using iterator for-loop:\n";
    vector <ComplexNumber>::iterator p;
    for (p = v1.begin(); p != v1.end(); p++)
    {
        cout << *p << endl;
    }
    return 0;
}

ComplexNumber::ComplexNumber(){
    real = 0;
    imaginary = 0;
}
ComplexNumber::ComplexNumber(double inReal, double inImaginary){
    real = inReal;
    imaginary = inImaginary; 
}

istream& operator>>(istream& inStream, ComplexNumber cNumber){
    inStream >> cNumber.real;
    char plusSign;
    inStream >> plusSign;
    if(plusSign != '+'){
        cout << "Failed to read object: ERROR\n";
        return inStream;
    }
    inStream >> cNumber.imaginary;
    return inStream;
}
ostream& operator<<(ostream& outstream, ComplexNumber cNumber){
    outstream << cNumber.getRealNumber() << "+" <<cNumber.getImaginaryNumber() << "i"; 
    return outstream;
}
double ComplexNumber::getRealNumber(void) const{
    return real;
}
double ComplexNumber::getImaginaryNumber(void) const{
    return imaginary;
}
void ComplexNumber::setRealNumber(double inReal){
    real = inReal;   
}
void ComplexNumber::setImaginaryNumber(double inImaginary){
    imaginary = inImaginary;
}
void ComplexNumber::SetComplexNumber(double inReal, double inImaginary){
    real = inReal;
    imaginary = inImaginary;
}
const ComplexNumber operator+(const ComplexNumber& leftOp, const ComplexNumber& rightOp){
    ComplexNumber temp;
    double real, imaginary;
    real = leftOp.getRealNumber() + rightOp.getRealNumber();
    imaginary = leftOp.getImaginaryNumber() + rightOp.getImaginaryNumber();
    temp.SetComplexNumber(real, imaginary);
    return temp;
}
const ComplexNumber operator-(const ComplexNumber& leftOp,const ComplexNumber& rightOp){
    ComplexNumber temp;
    double real, imaginary;
    real = leftOp.getRealNumber() - rightOp.getRealNumber();
    imaginary = leftOp.getImaginaryNumber() - rightOp.getImaginaryNumber();
    temp.SetComplexNumber(real, imaginary);
    return temp;
}
//(x+yi)(u+vi)=(xu-yv)+(xv+yu)i
//(x+yi)^{2}=x^{2}-y^{2}+2xyi
const ComplexNumber operator*(const ComplexNumber& leftOp,const ComplexNumber& rightOp){
    ComplexNumber temp;
    double real, imaginary;
    real = (leftOp.getRealNumber() * rightOp.getRealNumber()) - (leftOp.getImaginaryNumber() * rightOp.getImaginaryNumber());
    imaginary = (leftOp.getRealNumber() * rightOp.getImaginaryNumber()) + (leftOp.getImaginaryNumber() * rightOp.getRealNumber());
    temp.SetComplexNumber(real, imaginary);
    return temp;
}
const ComplexNumber operator/(const ComplexNumber& leftOp,const ComplexNumber& rightOp){
    ComplexNumber temp;
    if(rightOp.getImaginaryNumber() == 0 && rightOp.getRealNumber() == 0){
        return temp;
    }
    double real, imaginary, denom;
    denom = pow(rightOp.getRealNumber(), 2) + pow(rightOp.getImaginaryNumber(), 2);
    //(ux +vy)
    real = (leftOp.getRealNumber() * rightOp.getRealNumber()) + (leftOp.getImaginaryNumber() * rightOp.getImaginaryNumber());
    imaginary = (leftOp.getImaginaryNumber() * rightOp.getRealNumber()) - (leftOp.getRealNumber() * rightOp.getImaginaryNumber());
    temp.setRealNumber(real / denom);
    temp.setImaginaryNumber(imaginary / denom);
    return temp;
}
const ComplexNumber operator!(const ComplexNumber& rightOp){
    ComplexNumber temp;
    temp.setRealNumber(rightOp.getRealNumber());
    double imaginary = (rightOp.getImaginaryNumber());
    imaginary = imaginary - (imaginary * 2);
    temp.setImaginaryNumber(imaginary);
    return temp;
}