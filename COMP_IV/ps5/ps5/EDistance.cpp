// Copyright [2023] <Daniel Bergeron>
#include "Header/EDistance.hpp"

void EDistance::testPrint() const {
    std::cout << "===" << std::endl;
    for (int i = 0; i < static_cast<int>(x.size() + 1); i++) {
        for (int j = 0; j < static_cast<int>(y.size() + 1); j++) {
            std::cout << " " << costMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "===" << std::endl;
}

EDistance::EDistance(const string& ip1, const string& ip2) {
    x = ip1;  // our x side
    y = ip2;  // our y side
    int size1 = ip1.length();
    int size2 = ip2.length();

    costMatrix.resize(size1 + 1);
    for (int i = 0; i < size1 + 1; i++) {
        costMatrix[i].resize(size2 + 1);
    }

    costMatrix[size1][size2] = 0;
    for (int i = size2 - 1; i >= 0; i--) {
        costMatrix[size1][i] = costMatrix[size1][i + 1] + 2;
    }

    for (int i = size1 - 1; i >= 0; i--) {
        costMatrix[i][size2] = costMatrix[i + 1][size2] + 2;
    }

    testPrint();
}

int EDistance::penalty(char a, char b) {
    if (a == b) {
        return 0;
    }
    return 1;
}
int EDistance::min(int a, int b, int c) {
    return std::min(std::min(a, b), c);
}
int EDistance::optDistance(void) {
     for (int i = costMatrix.size() - 2; i >= 0; i--) {
        for (int j = costMatrix[i].size() - 2; j >= 0; j--) {
            costMatrix[i][j] = min(costMatrix[i+1][j+1] + penalty(x[i], y[j]),
                                costMatrix[i+1][j] + 2, costMatrix[i][j+1] + 2);
        }
    }

     testPrint();

    return costMatrix[0][0];
}
string EDistance::alignment(void) {
    auto toChar = [](int cost) {
        return static_cast<char>(cost + '0');    
    };
    string oString;  // output string
   /* oString += x[0];
    oString += "   ";
    oString += y[0];
    oString += "   ";
    oString += toChar(penalty(x[0], y[0]));
    oString += '\n';*/
    // Resoureces
    // need a return string
    // cost vector
    // function to convert num to chars
    // main case
    int i = 0, j = 0;
    int minVal;
    int cost = 0;
    while (i <= static_cast<int>(x.size()-1)
                && j <= static_cast<int>(y.size()-1)) {
        // base case at costmatrix[0][0]
        // load directly into string, inset x[0], y[0], then num
        // most optimal alligment
        // letters are matched
        // therefore we put both letters in ouput string
        // insert char 0
        // push into cost matrix
        minVal = min(costMatrix[i+1][j+1],
                        costMatrix[i+1][j], costMatrix[i][j+1]);
        if (minVal == costMatrix[i+1][j+1]) {
            i++;
            j++;
            cost = penalty(x[i], y[j]);
            if(cost == 0 && (i > static_cast<int>(x.size()-1) 
                        || j > static_cast<int>(x.size()-1))) {
                return oString;
            }
            oString += x[i];
            oString += "   ";
            oString += y[j];
            oString += "   ";
            oString += toChar(cost);
            oString += '\n';
        } else if (minVal == costMatrix[i+1][j]) {
            i++;
            oString += x[i];
            oString += "   ";
            oString += '-';
            oString += "   ";
            oString += '2';
            oString += '\n';
        } else if (minVal == costMatrix[i][j + 1]) {
            j++;
            oString += '-';
            oString += "   ";
            oString += y[j];
            oString += "   ";
            oString += '2';
            oString += '\n';
        }
    }
    return oString;
}
