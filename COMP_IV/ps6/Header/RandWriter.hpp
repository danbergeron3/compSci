// Copyright [2023] <Daniel Bergeron>
#ifndef _HOME_DBERGERO3_PROGRAMS_COMP4_PS6_HEADER_RANDWRITER_HPP_
#define _HOME_DBERGERO3_PROGRAMS_COMP4_PS6_HEADER_RANDWRITER_HPP_

#include <iostream>
#include <string>
using std::string;
#include <map>
#include <utility>
using std::pair;
#include <chrono>
#include <random>

class RandWriter {
 public:
    // Note: all of the below constructors/methods should be public.
    // -------------------------------------------------------------------
    // create a Markov model of order k from given text
    RandWriter(string text, int k);  // Assume that text has length at least k.
    //  -------------------------------------------------------------------
    int orderK() const;  // order k of Markov model
    // -------------------------------------------------------------------
    // number of occurrences of kgram in text
    int freq(string kgram) const;  // throw an exception if kgram is not of
    // length k
    // -------------------------------------------------------------------
    // number of times that character c follows kgram
    // if order=0, return num of times char c appears
    // (throw an exception if kgram is not of length k)
    int freq(string kgram, char c) const;
    // -------------------------------------------------------------------
    // random character following given kgram
    // (Throw an exception if kgram is not of length k.
    // Throw an exception if no such kgram.)
    char kRand(string kgram);
    // -------------------------------------------------------------------
    // generate a string of length L characters
    // by simulating a trajectory through the corresponding
    // Markov chain. The first k characters of the newly
    // generated string should be the argument kgram.
    // Throw an exception if kgram is not of length k.
    // Assume that L is at least k.
    string generate(string kgram, int L);
    // -------------------------------------------------------------------
    // overload the stream insertion operator and display
    std::ostream& operator<<(std::ostream& out);
    // the internal state of the Markov Model. Print out
    // the order, the alphabet, and the frequencies of
    // the k-grams and k+1-grams.4

 private:
    int order;
    string input;
    string alphabet;
    string currState;
    // map to hold k grams and the maps it to K+1 grams and there occurence
    std::map<string, int> kfreq;
    std::map<string, std::map<string, int>> symbolTable;
};
#endif  // _HOME_DBERGERO3_PROGRAMS_COMP4_PS6_HEADER_RANDWRITER_HPP_
