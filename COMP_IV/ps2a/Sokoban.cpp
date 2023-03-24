/* "Copyright [2023] <Daniel Bergeron>" */
#include "Sokoban.hpp"

GameObject::GameObject(int _x, int _y, typeObject _object) {
    x = _x;
    y = _y;
    object = _object;
}

void Sokoban::movePlayer(moveSet) {
    // TODO(Daniel): Finish.
    cout << "Player Doesn't feel like moving!\n";
    return;
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    GameObject block;
    sf::Vector2f location;
    sf::Texture floorTexture;
    sf::Sprite floorSprite, sprite;
    map<typeObject, sf::Texture>::const_iterator pos = textureMap.find(floor);
    floorTexture = pos->second;
    floorSprite.setTexture(floorTexture);
    target.draw(sprite, states);
    // pulls blocks from matrix to be drawn
    for (int y = 0; y < ySize; y++) {
        for (int x = 0; x < xSize; x++) {
            block = matrix[y][x];
            getDrawPos(location, block, textureSize);
            if (block.getTypeObject() == player) {
                floorSprite.setPosition(location);
                target.draw(floorSprite, states);
            }
            sprite = matrix[y][x].getSprite();
            sprite.setPosition(location);
            target.draw(sprite, states);
        }
    }
}

ifstream& operator>>(ifstream& in, Sokoban& level) {
    // objects and var
    int xtemp, ytemp;
    vector<GameObject> objects, tempVec;
    // make sure matirx is clear before it is used again.
    level.matrix.clear();
    // take map size input
    in >> xtemp >> ytemp;
    if (xtemp <= 0 && ytemp <= 0) {
        exit(1);
    }
    level.xSize = xtemp;
    level.ySize = ytemp;


    // make matrix outline
    level.matrix.resize(ytemp);
    for (int i = 0; i < static_cast<int>(level.matrix.size()); i++) {
        for ( int j = 0; j < xtemp; j++ ) {
            GameObject empty;
            level.matrix[i].push_back(empty);
        }
    }

    // start reading chars
    // use to build Game objects
    // place in input vector then build matrix
    if (level.buildGameObjectVector(in, objects)) {
        level.setSokobanMatrix(objects);
    }
    return in;
}

bool Sokoban::buildGameObjectVector(ifstream& in, vector<GameObject>& objects) {
    char input;
    int x = 0, y = 0;
    // Takes input and puts into a vector
    // based of what the char input is.
    // Two guards at the end to ensure
    // it dosen't go out of bounds.

    while ( !(in.eof()) ) {
        GameObject block;
        sf::Texture texture;
        in >> input;
        switch ( input ) {
        case '@':
            texture.loadFromFile("sokoban/images/player_05.png");
            setTextureInMap(player, texture);
            block.setBlock(x, y, player, textureMap);
            break;
        case '#':
            texture.loadFromFile("sokoban/images/block_06.png");
            setTextureInMap(wall, texture);
            block.setBlock(x, y, wall, textureMap);
            break;
        case '.':
            texture.loadFromFile("sokoban/images/ground_01.png");
            setTextureInMap(floor, texture);
            block.setBlock(x, y, floor, textureMap);
            break;
        case 'A':
            texture.loadFromFile("sokoban/images/crate_03.png");
            setTextureInMap(crate, texture);
            block.setBlock(x, y, crate, textureMap);
            break;
        case 'a':
            texture.loadFromFile("sokoban/images/ground_04.png");
            setTextureInMap(storage_space, texture);
            block.setBlock(x, y, storage_space, textureMap);
            break;
        case '1':
            texture.loadFromFile("sokoban/images/ground_01.png");
            setTextureInMap(floor, texture);
            block.setBlock(x, y, stored, textureMap);
            break;
        default:
            return false; }
        x++;
        if (y < ySize) {
            objects.push_back(block);
        }
        if (x >= xSize) {
            y++;
            x = 0;
        }
    }

    return true;
}

void Sokoban::setSokobanMatrix(vector<GameObject>& blocks) {
    // puts block in matrix based of the objects
    // predetermined location
    int x = 0, y = 0;
    int val = blocks.size();
    for (int i = 0; i < val; i++) {
        x = blocks[i].getXlocation();
        y = blocks[i].getYlocation();
        matrix[y][x] = blocks[i];
    }
}

void GameObject::setBlock(int _x, int _y, typeObject _object,
                            map<typeObject, sf::Texture>& texture) {
    // reasigns textures
    x = _x;
    y = _y;
    object = _object;
    sprite.setTexture(texture[_object]);
}

void Sokoban::setTextureInMap(typeObject type, sf::Texture& texture) {
    textureMap[type] = texture;
}

Sokoban::Sokoban() {
    sf::Texture newText;
    /*int xSize;
    int ySize;
    vector<vector<GameObject>> matrix;
    pair<int, int> textureSize;
    map<typeObject , sf::Texture> textureMap;*/
    xSize = 0;
    ySize = 0;
    newText.loadFromFile("sokoban/images/ground_01.png");
    getTexturePixelSize(newText, textureSize);
}

void getTexturePixelSize(sf::Texture texture, pair<int, int>& cor) {
    sf::Vector2u pixels;
    pixels = texture.getSize();
    cor.first = static_cast<int>(pixels.x);
    cor.second = static_cast<int>(pixels.y);
    return;
}

void getDrawPos(sf::Vector2f& location, const GameObject& block, const pair<int, int>& xyCor) {
    location.x = block.getXlocation() * xyCor.first;
    location.y = block.getYlocation() * xyCor.second;
}
