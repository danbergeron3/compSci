#include "FibLFSR.hpp"




FibLFSR::FibLFSR(std::string seed){
    if(seed.size() != 16){
        cout << "ERROR: seed must have size of 16\n" ;
        return;
    }
    std::bitset<16> newData(seed);
    data = newData;
}

ostream& operator<<(ostream& out, FibLFSR reg)
{
    out << reg.data;
    return out;
}

int FibLFSR::step(){
    int tap1 = 15, tap2 = 13, tap3 = 12 , tap4 = 10; 
    bool newVal = false;
    std::bitset<16> newData = data; 
    for(int i = 15; i > 0; i--){
        newData[i] = data[i -1];
    }  
    newVal = data[tap1] ^ data[tap2];
    newVal = newVal ^ data[tap3];
    newVal = newVal ^ data[tap4];
    newData[0] = newVal;

    data = newData;
    return newVal;
}

int FibLFSR::generate(int k){
    int value = 0;

    for(int i = 0; i < k; i++ ){
        value *= 2;
        value += step(); 
    }
    return value;
}