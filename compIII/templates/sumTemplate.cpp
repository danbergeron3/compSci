#include <iostream>
using namespace std;

template <class T>
T sumArray(const T arr[],const int size);


int main(int argc, char* argv[]){
    int arrInt[] = {1,2,3,4,5}; 
    double arrDouble[] = {1.2,2.3,3.4};
    float arrFloat[] = {.3, .5, .9, .8};
    char arrChar [] = {'c', 'b', 'd'};
    cout << "For the following input:\n";
    cout << "int arrInt[] = {1,2,3,4,5}; \n";
    cout << "double arrDouble[] = {1.2,2.3,3.4}; \n";
    cout << "float arrFloat[] = {.3, .5, .9, .8};\n";
    cout << "char arrChar [] = {'c', 'b', 'd'};\n";
    cout << "We the output:\n";

    cout << "SumInt = " << sumArray(arrInt, 5) << endl;
    cout << "SumDouble = " << sumArray(arrDouble, 3) << endl;
    cout << "SumFloat = " << sumArray(arrFloat, 4) << endl;
    cout << "SumChar = " <<sumArray(arrChar, 3) << endl;

    return 0;
}

template <class T>
T sumArray(const T arr[],const int size){
    T sum = arr[0];
    for(int i = 1; i < size; i++){
        sum += arr[i]; 
    }
    return sum;
}