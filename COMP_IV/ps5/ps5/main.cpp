// Copyright [2023] <Daniel Bergeron>
#include "Header/EDistance.hpp"

int main(int argc, char *argv[]) {
    // input handling
    std::ifstream fp;
    fp.open(argv[1]);
    string input1, input2;
    getline(fp, input1);
    if (input1.back() == '\r') {
        input1.pop_back();
    }
    getline(fp, input2);
    // deals with windows bs
    if (input2.back() == '\r') {
        input2.pop_back();
    } 
    fp.close();

    // Sequencing
    int x = 0;
    EDistance test(input1, input2);
    x = test.optDistance();
    cout << "optDistance: "<< x << endl;
    cout << "X   Y  Cost\n";
    cout << "____________\n\n";
    cout << test.alignment();
    return 0;
}
