// Copyright [2023] <Daniel Bergeron>
#include "Header/RandWriter.hpp"

// Note: all of the below constructors/methods should be public.
    // -------------------------------------------------------------------
    // create a Markov model of order k from given text
    // Assume that text has length at least k.
RandWriter::RandWriter(string text, int k) {
    input = text;
    currState = text;
    int size = static_cast<int>(text.size());
    order = k;
    //  make alpha bet
    char c;
    alphabet += text[0];
    for (int i = 1; i < size; i++) {
        c = text[i];
        // find returns npos -1 if nothing found
        if (static_cast<int>(alphabet.find(c, 0)) < 0) {
            alphabet += c;
        }
    }

    std::string kgram, temp;
    std::map<string, int> kGramPlus1;
    // loop to fill symbol table
    // i increments the entire sting
    // j increments the kgram on the string
    int j = 0;
    int index = 0;
    // std::cout << input << std::endl;
    for (int i = 0; i < size; i++) {
        kgram.clear();
        index = i;
        for (j = 0; j < order; j++) {
            if (index > size - 1) {
                index = 0;
                kgram += text[index];
            } else {
                kgram += text[index];
            }
            index++;
        }
        // std::cout << kgram << " ";
        // insert kgram into its text freq map
        kfreq[kgram]++;
        // we have a kgram now we must break it into
        // its k + 1
        // builds new map with value and ties it to
        // old map
        symbolTable[kgram];
        if (index > size - 1) {
            index = 0;
        }
        temp = kgram;
        temp += text[index];

        kGramPlus1[temp] = 0;
        (symbolTable[kgram])[temp]++;
    }
}

int RandWriter::orderK() const {  // order k of Markov model
    return order;
}

// -------------------------------------------------------------------
    // number of occurrences of kgram in text
    // throw an exception if kgram is not of length k
int RandWriter::freq(string kgram) const {
    int size = 0;
    size = static_cast<int>(kgram.length());
    // std::cout << "Size " << size << std::endl;
    int freq = 0;
    if (order == 0 && kgram == " ") {
        return static_cast<int>(input.size());
    }
    if (size != order) {
        throw "Size Mismatch";
    }
    if (kfreq.find(kgram) == kfreq.end()) {
        return 0;
    }
    freq = kfreq.find(kgram)->second;
    return freq;
}

// number of times that character c follows kgram
// if order=0, return num of times char c appears
// (throw an exception if kgram is not of length k)
int RandWriter::freq(string kgram, char c) const {
    int count = 0;
    int size = 0;
    size = static_cast<int>(kgram.length());
    if (size != order) {
        throw "Size Mismatch";
    }
    string p1kgram;  // k + 1
    if (order == 0) {
        for (int i = 0; i < static_cast<int>(input.size()); i++) {
            if (input[i] == c) {
                count++;
            }
        }
        return count;
    }
    // we need to kgram plus one
    if (kfreq.find(kgram) == kfreq.end()) {
        return 0;
    }
    auto n = symbolTable.find(kgram)->second.begin();
    for (; n != symbolTable.find(kgram)->second.end(); n++) {
        p1kgram = n->first;
        // if first char == c increase the count
        if (p1kgram[static_cast<int>((p1kgram.size()-1))] == c) {
            count += n->second;
        }
    }
    return count;
}

// -------------------------------------------------------------------
// random character following given kgram
// (Throw an exception if kgram is not of length k.
// Throw an exception if no such kgram.)
char RandWriter::kRand(string kgram) {
    // get all k plus one grams there occurences
    // add occurences up
    // generate random number of occurences and from 0 to total occurences
    // put number on range if
    // construct a trivial random generator engine from a time-based seed:
    int size = static_cast<int>(kgram.length());
    if (size != order) {
        throw "Size Mismatch\n";
    }
    if (kfreq.find(kgram) == kfreq.end()) {
        throw "No Such Kgram\n";
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    // std::cout << "SEEEEDD:::"<<seed << std::endl;
    std::default_random_engine generator(seed);
    auto p = symbolTable[kgram].begin();
    int upperBounds = 0, randNum;
    // gets total amount for upperbounds

    for (unsigned i = 0; i < alphabet.size(); i++) {
        upperBounds += freq(kgram, alphabet[i]);
    }

    randNum = (generator() % upperBounds) + 1;

    int first = 0, second = 0;
    char c = kgram[0];
    // use randnum to get next letter out of range of possible next char
    for (p = symbolTable[kgram].begin(); p != symbolTable[kgram].end(); p++) {
        second += p->second;
        // std::cout << "First: " << first << "Second: " << second << std::endl;
        if (randNum <= second) {
            // std::cout << "Char: "<< p->first[size] << std::endl;
            c = p->first[size];
            break;
        } else {
            first += p->second;
        }
    }
    return c;
}

// -------------------------------------------------------------------
// generate a string of length L characters
// by simulating a trajectory through the corresponding
// Markov chain. The first k characters of the newly
// generated string should be the argument kgram.
// Throw an exception if kgram is not of length k.
// Assume that L is at least k.
string RandWriter::generate(string kgram, int L) {
    // first get kgram size
    string chain;

    /*if (order == 0) {
        int index = 0;
        for (int i = 0; i < L; i++) {
            if (index > static_cast<int>(input.length())) {
                index = 0;
            }
            chain += input[index];
            index++;
        }
        currState = chain;
        return chain;
    }*/
    // std::cout << kgram << "what\n";
    int size = static_cast<int>(kgram.length());
    if (size != order) {
        throw "Size Mismatch\n";
    }
    if (kfreq.find(kgram) == kfreq.end()) {
        throw "Kgram not in map\n";
    }
    if (size > L) {
        for (int i = 0; i < L; i++) {
            chain += kgram[i];
        }
        currState = chain;
        return chain;
    }
    // else we begin the generation

    chain = kgram;
    char c;
    int i = size;
    // std::cout << size-1 << std::endl;
    while (i < L) {
        c = kRand(kgram);
        chain += c;
        kgram.replace(0, size, chain, i - (size - 1), size);
        i++;
    }
    currState = chain;
    return chain;
}

// -------------------------------------------------------------------
// << // overload the stream insertion operator and display
// the internal state of the Markov Model. Print out
// the order, the alphabet, and the frequencies of
// the k-grams and k+1-grams.
std::ostream& RandWriter::operator<<(std::ostream& out) {
    out << "\nOrder: " << order << std::endl;
    out << "Alphabet:\n" << alphabet << std::endl;
    out << "CurrState:\n" << currState << std::endl;
    out << "Frequcies k-grams:\n" << std::endl;

    for (auto i : symbolTable) {
        out << i.first << " " << freq(i.first) << std::endl;
    }

    out << "Frequcies k+1-grams:\n" << std::endl;
    string str;
    for (auto i : symbolTable) {
        for (auto j : i.second) {
            str = j.first;
            out << str << " " << j.second << std::endl;
        }
    }
    return out;
}
