
#include "Sokoban.hpp"

void Sokoban::movePlayer(void){
    return;
}

/*void Sokoban::generateGameMap(void){
    int x, y;
    texture.loadFromFile("sokoban/images/environment_03.png");
    getTexturePixelSize(texture, x, y);
    sf::Vector2f location;
    sf::RenderWindow window(sf::VideoMode(x * xSize, y * ySize), "Input");
    GameObject block;  
    bool drawn = false;

    while (window.isOpen()) {
        sf::Event event;
        sf::Sprite floor;
        sf::Texture ground;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        if(drawn == false){
            for(int i = 0; i < ySize; i++){
                for(int j = 0; j < xSize; j++){
                    block = matrix[j][i];
                    location.x = block.getXlocation() * x;
                    location.y = block.getYlocation() * y;
                    if(block.getBlock() == player){
                        ground.loadFromFile("sokoban/images/ground_01.png");
                        floor.setTexture(texture);
                        floor.setPosition(location);
                        window.draw(floor);
                    }
                    sprite = getSprite(block);
                    sprite.setPosition(location);
                    window.draw(sprite);
                    window.display();
                }
            }
            drawn = true;
        }
    }
}*/

sf::Sprite Sokoban::getSprite(GameObject& block){
    
    //nill, player, wall, floor, crate, storage_space, stored};
    
    switch(block.getBlock()){
        case player:
            texture.loadFromFile("sokoban/images/player_05.png");
            break;
        case wall:
            texture.loadFromFile("sokoban/images/block_06.png");
            break;
        case floor:
            texture.loadFromFile("sokoban/images/ground_01.png");
            break;
        case crate:
            texture.loadFromFile("sokoban/images/crate_03.png");
            break;
        case storage_space:
            texture.loadFromFile("sokoban/images/ground_04.png");
            break;
        default:
            return sprite; 
    }
    sprite.setTexture(texture);
    return sprite; 

}
void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const{
   target.draw(sprite, states);
   
}

GameObject::GameObject(int _x, int _y, typeObject _object){
    x = _x;
    y = _y;
    object = _object;
}

ifstream& operator>>(ifstream& in, Sokoban& level){
    //objects and var
    int xtemp, ytemp;
    vector<GameObject> objects, tempVec;

    //take map size input 
    in >> xtemp >> ytemp;
    if(xtemp <= 0 && ytemp <= 0){
        exit(1);
    }
    level.xSize = xtemp;
    level.ySize = ytemp;

    //make matrix outline
    level.matrix.resize(ytemp);
    for(int i = 0; i < static_cast<int>(level.matrix.size()); i++){
        for(int j = 0; j < xtemp; j++){
            GameObject empty;
            level.matrix[i].push_back(empty);
        }
    }

    //start reading chars
    //use to build Game objects
    //place in input vector
    if(insert(in, objects, xtemp, ytemp)){
        level.buildMatrix(objects);
    }
    
    //build map
    return in;
}

bool insert(ifstream& in, vector<GameObject>& objects, int xLimit, int yLimit){
    char input;
    int x = 0, y = 0;
    while(!(in.eof())){
        GameObject block;
        in >> input;
        switch (input){
        case '@':
            block.setBlock(x, y, player);
            x++;
            break;
        case '#':
            block.setBlock(x, y, wall);
            x++;
            break;
        case '.':
            block.setBlock(x, y, floor);
            x++;
            break;
        case 'A':
            block.setBlock(x, y, crate);
            x++;
            break;
        case 'a':
            block.setBlock(x, y, storage_space);
            x++;
            break;
        case '1':
            block.setBlock(x, y, stored);
            x++;
            break;
        default:
            return false;}  
        if(y < yLimit){
            objects.push_back(block); 
        }
        if(x >= xLimit){
            y++;
            x = 0;
        }
        
    }
    return true;
}

void Sokoban::buildMatrix(vector<GameObject>& blocks){
    int x = 0, y = 0;
    int val = blocks.size();
    for(int i = 0; i < val; i++){
        x = blocks[i].getXlocation();
        y = blocks[i].getYlocation();
        matrix[y][x] = blocks[i];
    }
}

void makePixelCoordinate(sf::Vector2f& location, GameObject& block, int xPixel, int yPixel){
    location.x = block.getXlocation() * xPixel;
    location.y = block.getYlocation() * yPixel;
}
