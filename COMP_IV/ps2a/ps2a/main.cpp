/* "Copyright [2023] <Daniel Bergeron>" */
#include "Sokoban.hpp"

// Function abstracts the grunt work of
// making the visuals away from main
// pre: Is passed a valid Sokoban object
void generateGameMap(Sokoban& level);

// pre: Passed valid texture and int pair by refrence
// post: pair will be given new value
void getTexturePixelSize(sf::Texture texture, pair<int, int>& cor);

int main() {
    // Simple driver to load and test maps
    Sokoban lv;
    ifstream fp;

    // test1
    fp.open("level1.txt");
    fp >> lv;
    generateGameMap(lv);
    fp.close();

    // test2
    fp.open("level2.txt");
    fp >> lv;
    generateGameMap(lv);
    fp.close();

    // stub test
    lv.movePlayer(noMove);

    return 0;
}

void generateGameMap(Sokoban& level) {
    sf::Texture texture, ground;;
    sf::Sprite sprite, floor;
    sf::Event event;
    sf::Vector2f location;
    pair<int, int> textureSize;
    GameObject block;
    bool drawn = false;

    // gets pixel sizes & creats a window that will fit all gamObjects
    texture.loadFromFile("sokoban/images/environment_03.png");
    getTexturePixelSize(texture, textureSize);
    sf::RenderWindow window(sf::VideoMode(textureSize.first * level.getWidth(),
                                textureSize.second * level.getHeight()), "Input");

    // Game Loop, draw and maintain map
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                }
            }
            if (drawn == false) {
                // pulls blocks from matrix to be drawn
                for (int y = 0; y < level.getHeight(); y++) {
                    for (int x = 0; x < level.getWidth(); x++) {
                        block = level.getGameObject(y , x);
                        getDrawPos(location, block, textureSize);

                        // Special Case Player Block, ground needs to be drawn first
                        if (block.getTypeObject() == player) {
                            ground.loadFromFile("sokoban/images/ground_01.png");
                            floor.setTexture(ground);
                            floor.setPosition(location);
                            window.draw(floor);
                        }

                        // Draws and updates window
                        level.setSprite(block);
                        sprite = level.getSprite();
                        sprite.setPosition(location);
                        window.draw(sprite);
                        window.display();
                    }
                }
                drawn = true;
            }
        }
}

void getTexturePixelSize(sf::Texture texture, pair<int, int>& cor) {
    sf::Vector2u pixels;
    texture.loadFromFile("sokoban/images/environment_03.png");
    pixels = texture.getSize();
    cor.first = static_cast<int>(pixels.x);
    cor.second = static_cast<int>(pixels.y);
    return;
}
