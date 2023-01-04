#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]){
    
    ifstream inStream;
    ofstream outStream;
    string next;
    int sum = 0,val ,i = 1;
    inStream.open("input.txt");
    if(inStream.fail()){
        cout << "Failed to open input file \n";
        exit(1);
    }
    outStream.open("output.txt");
    if(outStream.fail()){
        cout << "Failed to open output file\n";
        exit(1);
    }
    

    do{
        getline(inStream, next);
        if(next.empty()){
            //neww
            outStream << "Elf "<< i << " has " << sum << " calories.\n";
            i++;
            sum = 0;
        } else {
            val = stoi(next);// converts to int
            sum += val; 
            next.clear();
        }
    }while(!inStream.eof());
    

    inStream.close();
    outStream.close();
    return 0;
}