/* "Copyright [2023] <Daniel Bergeron>" */
#include "Headers/Checkers.hpp"

void clearMouseBuffer(void);

int main(int argc, char* argv[]) {
    sf::RenderWindow window1(sf::VideoMode(GAMEBOARDLENGTH * SPACESIZES,
                GAMEBOARDLENGTH * SPACESIZES), "CHECKERS");
    Checkers game1;
    while (window1.isOpen()) {
        sf::Event event;
        while (window1.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            clearMouseBuffer();
            window1.close();
        }
    }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            // left mouse button is pressed:
            game1.highLight(sf::Mouse::getPosition(window1));
        }
        window1.clear(sf::Color::Black);
        window1.draw(game1);
        window1.display();
    }
    return 0;
}

void clearMouseBuffer(void) {
    while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {}
}
