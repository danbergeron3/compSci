#include <exception>
#include <iostream>
using namespace std;


class DivideByZero : invalid_argument{
public:
    explicit DivideByZero(const string& whatArg) : invalid_argument(whatArg){}
    const char *what() const noexcept {
        return "something from the argument was passed into constructor\n";
    }
private:
    
};

int main(int argc, char* argv[]){
    
    return 0;
}