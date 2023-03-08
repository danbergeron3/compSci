/* "Copyright [2023] <Daniel Bergeron>" */
#include <string>
#include "ps2b/Sokoban.hpp"

moveSet getKeyBoardInput(void);
bool resetLevel(moveSet reKey, ifstream& fp, Sokoban& lv, std::string gameMap);

int main(int argc, char* argv[]) {
    // Simple driver to load and test maps
    Sokoban lv;
    ifstream fp;
    moveSet input = noMove;
    std::string gameMap;
    int fontSize = 100;
    gameMap = argv[1];
    fp.open(gameMap);
    if (fp.fail()) {
        cout << "Failed to open file\n";
        return -1;
    }
    fp >> lv;
    fp.close();

    sf::Text text, text2;
    sf::Font font;
    if (!font.loadFromFile("endGameFont.ttf")) {
        cout << "Font failed to load\n";
    }
    text.setFont(font);
    text2.setFont(font);
    text.setString("YOU WON!!");
    text2.setString("Press Q to quit");
    text.setCharacterSize(100);
    text2.setCharacterSize(30);
    text.setPosition((lv.getTextureSizeX() * lv.getWidth())/2.50,
                (lv.getTextureSizeY() * lv.getHeight())/2.00);
    text.setFillColor(sf::Color::Green);
    text2.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text2.setStyle(sf::Text::Bold | sf::Text::Underlined);

    auto endGame = [](moveSet in) {  // Lambda expression
        if (in == quiet) {
            return true;
        }
        return false;
    };

    sf::RenderWindow window1(sf::VideoMode(lv.getTextureSizeX() * lv.getWidth(),
    lv.getTextureSizeY() * lv.getHeight()), "Sokoban");

    while (window1.isOpen()) {
        sf::Event event;
        while (window1.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window1.close();
            }
        }
        input = getKeyBoardInput();
        if (endGame(input)) {
            return 0;
        }
        if ( resetLevel(input, fp, lv, gameMap) ) {
            window1.clear(sf::Color::Black);
            input = getKeyBoardInput();
        }
        lv.movePlayer(input);
        window1.draw(lv);
        window1.display();
        while (lv.isWon() == true) {
            // inside the main loop, between window.clear() and window.display()
            window1.draw(text);
            window1.draw(text2);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                return 0;
            }
            input = getKeyBoardInput();
            if (resetLevel(input, fp, lv, gameMap)) {
                window1.clear(sf::Color::Black);
            }
            window1.display();
            while (window1.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window1.close();
                    return 0;
                }
            }
        }
    }
    return 0;
}

bool resetLevel(moveSet reKey, ifstream& fp, Sokoban& lv, std::string gameMap) {
        Sokoban newlv;
        if (reKey == restart) {
            fp.open(gameMap);
            fp >> lv;
            fp.close();
            return true;
        }
        return false;
}

moveSet getKeyBoardInput(void) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {}
        return up;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {}
        return down;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {}
        return left;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {}
        return right;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {}
        return restart;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        return quiet;
    } else {
        return noMove;
    }
}
