/* "Copyright [2023] <Daniel Bergeron>" */
#include "Sokoban.hpp"

// Function abstracts the grunt work of
// making the visuals away from main
// pre: Is passed a valid Sokoban object
void generateGameMap(Sokoban& level);

// pre: Passed valid texture and int pair by refrence
// post: pair will be given new values
void getTexturePixelSize(sf::Texture& texture, pair<int, int>& cor);

int main() {
    // Simple driver to load and test maps
    Sokoban lv;
    ifstream fp;

    // test1

    fp.open("level1.txt");
    fp >> lv;
    sf::RenderWindow window1(sf::VideoMode(lv.getTextureSizeX() * lv .getWidth(),
                                lv.getTextureSizeY() * lv .getHeight()), "Sokoban");
    while (window1.isOpen()) {
        sf::Event event;
        while (window1.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window1.close();
        }
    }
        window1.draw(lv);
        window1.display();
    }
    fp.close();
    // test2
    fp.open("level2.txt");
    fp >> lv;

    sf::RenderWindow window2(sf::VideoMode(lv.getTextureSizeX() * lv .getWidth(),
                                lv.getTextureSizeY() * lv .getHeight()), "Sokoban");
    while (window2.isOpen()) {
        sf::Event event;
        while (window2.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window2.close();
        }
    }
        window2.draw(lv);
        window2.display();
    }

    fp.close();

    // stub test
    lv.movePlayer(noMove);

    return 0;
}


void getTexturePixelSize(sf::Texture& texture, pair<int, int>& cor) {
    sf::Vector2u pixels;
    texture.loadFromFile("sokoban/images/environment_03.png");
    pixels = texture.getSize();
    cor.first = static_cast<int>(pixels.x);
    cor.second = static_cast<int>(pixels.y);
    return;
}
