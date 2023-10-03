#include <vector>
// Author: Daniel Bergeron
using namespace std;
// basix bubble sort 
// time is O(n^2) time, n^2-1 since it 
// never touches the last index 
// O(1) space complexity since no new space
// is allocated
vector<int> bubbleSort(vector<int> array) {
  
  int i;
  int j, temp;
  int max = array.size();
  for(i = 0 ; i < array.size(); i++) {
    for(j = 0; j < max-1; j++) {
        if(array[j] > array[j+1]) {
          temp = array[j];
          array[j] = array[j+1];
          array[j+1] = temp;
        }
      }
      max--;
    }
  return array;
}