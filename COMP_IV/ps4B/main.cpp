/* "Copyright [2023] <Daniel Bergeron>" */
#include "Headers/Checkers.hpp"

void clearBuffer(void);

int main(int argc, char* argv[]) {
    sf::RenderWindow window1(sf::VideoMode(GAMEBOARDLENGTH * SPACESIZES,
                GAMEBOARDLENGTH * SPACESIZES), "CHECKERS");
    Checkers game1;
    sf::Vector2i location;

    // fonts
    sf::Text text, text2;
    sf::Font font;
    if (!font.loadFromFile("resources/endGameFont.ttf")) {
        cout << "Font failed to load\n";
    }
    text.setFont(font);
    text.setString("Game Over!!");
    text.setCharacterSize(100);
    text.setPosition((static_cast<float>(window1.getSize().x / 5.00)),
                (static_cast<float>(window1.getSize().y / 4.00)));
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    text2.setFont(font);
    text2.setString("Press Q to quit");
    text2.setCharacterSize(30);
    text2.setFillColor(sf::Color::Blue);
    text2.setStyle(sf::Text::Bold | sf::Text::Underlined);

    clearBuffer();
    while (window1.isOpen()) {
        sf::Event event;
        while (window1.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                clearBuffer();
                window1.close();
            }
        }
        // tells if its a move or not based on if present
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            // left mouse button is pressed:
            game1.highLight(sf::Mouse::getPosition(window1));
            location = sf::Mouse::getPosition(window1);
            location.x /= SPACESIZES;
            location.y /= SPACESIZES;
            game1.move(location);
        }
        while (game1.endGameCheck()) {
            // inside the main loop, between window.clear()
            // and window.display()
            while (window1.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    clearBuffer();
                    window1.close();
                    return 0;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                return 0;
            }
            window1.clear(sf::Color::Black);
            window1.draw(game1);
            if (game1.getBlackPieceCount() == 0) {
                text.setString("RED WINS!!!");
            } else if (game1.getRedPieceCount() == 0) {
                text.setString("Black WINS!!!");
            } else {
                // For possible edge case
                text.setString("Draw!");
            }
            window1.draw(text);
            window1.draw(text2);
            window1.display();
        }
        // take selected input and see if next position clicked position is good
        // then move

        window1.clear(sf::Color::Black);
        window1.draw(game1);
        window1.display();
    }
    // clearBuffer();
    return 0;
}

// removes junk input from buffer so next run doesn't
// segment fault
void clearBuffer(void) {
    while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {}
    while (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {}
}
