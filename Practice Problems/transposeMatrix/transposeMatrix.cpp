/*Transpose Matrix
* Solution by: Daniel Bergeron
* given a matrix transpose the matrix
* i.e flip the matrix so the rows become columns
* the columns become rows
*/

#include <vector>
using namespace std;

vector<vector<int>> transposeMatrix(vector<vector<int>> matrix) {
  // vars
  int row, column;
  
  // intialize a rows vector to be the size of the 
  // matrix's columns with value of 0, then 
  // intilize new matrix with size of Martixs columns
  // to get row amounts, then fill with the vector called row
  vector<int> vecRow(matrix.size(), 0);
  vector<vector<int>> newMatrix(matrix[0].size(), vecRow);

  // loop through matrix's rows and columns
  for (row = 0; row < matrix.size(); row++) {
    for (column = 0; column < matrix[row].size(); column++) {

      // fill newMatrix's row with what was at matrix'x columns
      newMatrix[column][row] = matrix[row][column];
    
    }
  }
  return newMatrix;
}
