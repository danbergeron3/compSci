// Copyright [2023] <Daniel Bergeron>
#include "ps3_header/PTree.hpp"

int main(int argc, char* argv[]) {
    string lBase, nDepth;
    double L;
    int N;
    lBase = argv[1];
    nDepth = argv[2];
    L = stod(lBase);
    N = stoi(nDepth);
    cout << "The Base triangle size input is " << L << endl;
    cout << "The depth input is " << N << endl;
    PTree sappling(N, L);
    sappling.pTree();

    sf::RenderWindow window1(sf::VideoMode(6 * L, 4 * L), "Tree");

    while (window1.isOpen()) {
        sf::Event event;
        while (window1.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window1.close();
            }
        }
        window1.clear(sf::Color::White);
        window1.draw(sappling);
        window1.display();
    }
    return 0;
}
