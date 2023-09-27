// Find the value closest to target value in a BST

#include <cmath>
using namespace std;
class BST {
 public:
  int value;
  BST* left;
  BST* right;

  BST(int val);
  BST& insert(int val);
};

int findClosestValueInBst(BST* tree, int target) {

  // iterativly is faster but harder
  // compare value with root if value is greater go right
  // if equal return 
  // if less go left
  // keep track of differences absolute value 
  // keep track of node 
  // should be O(logn) for time and O(1) for space

  BST* next = tree;
  BST* closest = tree;
  while (next != NULL) {
    if(target > next->value) {

      // find minimun difference
      // give closest the node with lowest abs dif

      if(abs(target - next->value) < abs(target - closest->value)) {
        closest = next;
      } 
      next = next->right;
    } else if (target < next->value) {
      if(abs(target - next->value) < abs(target - closest->value)) {
        closest = next;
      } 
      next = next->left;
    } else {
      return next->value;
    }
  }
  return closest->value;
}
