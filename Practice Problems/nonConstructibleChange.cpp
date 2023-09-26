#include <vector>
#include <algorithm>
using namespace std;

int nonConstructibleChange(vector<int> coins) {
  // Write your code here.
  vector<int>::iterator m = coins.begin();
  int change = 0;
  // empty condition
  
  sort(coins.begin(), coins.end());
  for(; m != coins.end(); m++) {
    //add each value if delta is greater than one we have our answer
      if (*m > change + 1) {
        return change + 1; 
      } else {
        change += *m;
      }
    }
    return change + 1;
  }

