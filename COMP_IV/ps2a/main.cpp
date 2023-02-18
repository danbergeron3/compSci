#include "Sokoban.hpp"

void generateGameMap(Sokoban& level);
void getTexturePixelSize(sf::Texture texture,int& x, int& y);

int main(){
    Sokoban lv;
    ifstream fp;
    fp.open("level1.txt");
    fp >> lv;
    generateGameMap(lv);
    fp.close();
    return 0;
}

void generateGameMap(Sokoban& level){
    int x, y; 
    sf::Texture texture, ground;;
    sf::Sprite sprite, floor;
    sf::Event event;
    sf::Vector2f location;
    GameObject block;
    bool drawn = false;
    
    texture.loadFromFile("sokoban/images/environment_03.png");
    getTexturePixelSize(texture, x, y);
    sf::RenderWindow window(sf::VideoMode(x * level.getWidth(), y * level.getHeight()), "Input");

    while (window.isOpen()) {
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        if(drawn == false){
            for(int i = 0; i < level.getHeight(); i++){
                for(int j = 0; j < level.getWidth(); j++){
                    block = level.getGameObject(j , i);
                    makePixelCoordinate(location, block, x, y);
                    if(block.getBlock() == player){
                        ground.loadFromFile("sokoban/images/ground_01.png");
                        floor.setTexture(ground);
                        floor.setPosition(location);
                        window.draw(floor);
                    }
                    sprite = level.getSprite(block);
                    sprite.setPosition(location);
                    window.draw(sprite);
                    window.display();
                }
            }
            drawn = true;
        }
    }
}



void getTexturePixelSize(sf::Texture texture, int& x, int& y){
    sf::Vector2u pixels;
    texture.loadFromFile("sokoban/images/environment_03.png");
    pixels = texture.getSize();
    x = static_cast<int>(pixels.x);
    y = static_cast<int>(pixels.y);
    return;
}