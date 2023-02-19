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
    target.draw(sprite, states);
}

void Sokoban::setSprite(GameObject& block) {
// pulls textures from files based of block type
    switch (block.getTypeObject()) {
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
            // Will set any other GameObject to wall
            // TODO(Daniel): Make code to deal with states that
            // are stored in matirx
            texture.loadFromFile("sokoban/images/block_06.png");
    }
    sprite.setTexture(texture);
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
    if (insert(in, objects, xtemp, ytemp)) {
        level.setMatrix(objects);
    }
    return in;
}

bool insert(ifstream& in, vector<GameObject>& objects, int xLimit, int yLimit ) {
    char input;
    int x = 0, y = 0;
    // Takes input and puts into a vector
    // based of what the char input is.
    // Two guards at the end to ensure
    // it dosen't go out of bounds.

    while ( !(in.eof()) ) {
        GameObject block;
        in >> input;
        switch ( input ) {
        case '@':
            block.setBlock(x, y, player);
            break;
        case '#':
            block.setBlock(x, y, wall);
            break;
        case '.':
            block.setBlock(x, y, floor);
            break;
        case 'A':
            block.setBlock(x, y, crate);
            break;
        case 'a':
            block.setBlock(x, y, storage_space);
            break;
        case '1':
            block.setBlock(x, y, stored);
            break;
        default:
            return false; }
        x++;
        if (y < yLimit) {
            objects.push_back(block);
        }
        if (x >= xLimit) {
            y++;
            x = 0;
        }
    }
    return true;
}

void Sokoban::setMatrix(vector<GameObject>& blocks) {
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

void getDrawPos(sf::Vector2f& location, const GameObject& block, const pair<int, int>& xyCor) {
    location.x = block.getXlocation() * xyCor.first;
    location.y = block.getYlocation() * xyCor.second;
}
