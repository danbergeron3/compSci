#include "FibLFSR.hpp"

int main(int argc, char* argv[]){
    FibLFSR test1("0110110001101100");
    int newNum = 0, newNum2 = 0;
    for(int i = 10; i >= 0; i--){
        newNum = test1.step();
        cout << test1 << " " << newNum << endl;
    }
    
    cout << endl;

    FibLFSR test2("1100011011000011");
    for(int i = 0; i < 6; i++){
        newNum2 = test2.generate(5);
        cout << test2 << " " << newNum2 << endl;
    }
    return 0;
}