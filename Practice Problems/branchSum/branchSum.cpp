#include <vector>
using namespace std;

// This is the class of the input root. Do not edit it.
class BinaryTree {
 public:
  int value;
  BinaryTree* left;
  BinaryTree* right;

  BinaryTree(int value) {
    this->value = value;
    left = nullptr;
    right = nullptr;
  }
};

void recSums(BinaryTree* root, vector<int>& vSum, int sum);

vector<int> branchSums(BinaryTree* root) {
  // Write your code here.
  int currSum = 0;
  vector<int> vSum;
  vSum.push_back(0);
  recSums(root, vSum, currSum);
  vSum.pop_back();
  return vSum;
}

void recSums(BinaryTree* root, vector<int>& vSum, int currSum){ 
  currSum = currSum + root->value;
  vSum[vSum.size()-1] = currSum;
  if(root->left == nullptr && root->right == nullptr) {
    vSum.push_back(currSum - root->value);
  }
  if(root->left != nullptr) {
    recSums(root->left, vSum, currSum);
  }
  if(root->right != nullptr) {
    recSums(root->right, vSum, currSum);
  }
}