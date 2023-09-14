// Copyright [2023] <Daniel Bergeron>
#ifndef _HOME_DBERGERO3_PROGRAMS_COMP4_PS5_HEADER_EDISTANCE_HPP_
#define _HOME_DBERGERO3_PROGRAMS_COMP4_PS5_HEADER_EDISTANCE_HPP_
#include <fstream>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <algorithm>

class EDistance {
 public:
    EDistance(const string& ip1, const string& ip2);
    static int penalty(char a, char b);
    static int min(int a, int b, int c);
    int optDistance(void);
    string alignment(void);
 private:
    void testPrint() const;
    vector<vector<int>> costMatrix;
    string x;
    string y;
};

#endif  // _HOME_DBERGERO3_PROGRAMS_COMP4_PS5_HEADER_EDISTANCE_HPP_
