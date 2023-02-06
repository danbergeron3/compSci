#include <bitset>
#include <string>
#include <iostream>
using namespace std;

class FibLFSR {
public:
FibLFSR(std::string seed); // constructor to create LFSR with
// the given initial seed
int step(); // simulate one step and return the
// new bit as 0 or 1
int generate(int k); // simulate k steps and return
// k-bit integer
friend ostream& operator<<(ostream& out, FibLFSR reg);

private:
    std::bitset<16> data;
};