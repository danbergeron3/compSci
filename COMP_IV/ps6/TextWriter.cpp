// Copyright [2023] <Daniel Bergeron>
#include "Header/RandWriter.hpp"

int main(int argc, char* argv[]) {
    string Kstr = argv[1];
    string Lstr = argv[2];
    int K = stoi(Kstr);
    int L = stoi(Lstr);
    std::cout << "k value: " << K << std::endl;
    std::cout << "L value: " << L << std::endl;

    string input, temp;
    while (!std::cin.eof()) {
        std::cin >> temp;
        input += temp;
    }
    std::cout << input;
    string seed;
    for (int i = 0; i < K; i++) {
        seed += input[i];
    }
    std::cout << "Intial K-gram: " << seed << std::endl;
    RandWriter writer(input, K);
    try {
       writer.generate(seed, L);
    } catch (char* const er) {
        std::cout << er;
    }

    writer.operator<<(std::cout);
    return 0;
}
