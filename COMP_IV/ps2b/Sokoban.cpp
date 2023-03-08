/* "Copyright [2023] <Daniel Bergeron>" */
#include "ps2b/Sokoban.hpp"

GameObject::GameObject(int _x, int _y, typeObject _object) {
    x = _x;
    y = _y;
    object = _object;
    currTypeUnder = _object;
}

void GameObject::setBlock(int _x, int _y, typeObject _object,
                            map<typeObject, sf::Texture>& texture) {
    // reasigns textures
    x = _x;
    y = _y;
    object = _object;
    // gets texture from map of stored textures
    // so no new textures are created.
    sprite.setTexture(texture[_object]);
}

MoveObject::MoveObject() {
    pair<int, int> empty;
    empty.first = 0;
    empty.second = 0;
    currSpace = empty;
    nextSpace = empty;
    moveable = false;
}

Sokoban::Sokoban() {
    sf::Texture newText;
    xSize = 0;
    ySize = 0;
    newText.loadFromFile("sokoban/images/crate_02.png");
    getTexturePixelSize(newText, textureSize);
    textureMap[stored] = newText;
    pointsToWin = 0;
    playerLocation.first = 0;
    playerLocation.second = 0;
}

// gets the pixels sizes of the the texture passed in
void getTexturePixelSize(const sf::Texture& texture, pair<int, int>& cor) {
    sf::Vector2u pixels;
    pixels = texture.getSize();
    cor.first = static_cast<int>(pixels.x);
    cor.second = static_cast<int>(pixels.y);
    return;
}

// functions takes move
// checks for no move then
// sets Sokobans move Objects then
// it excuetes the commands within
// the move objects
void Sokoban::movePlayer(moveSet move) {
    MoveObject moveInfo;
    if (move == noMove) {
        return;
    }

    setMoveObjects(move);
    executeMoveObjects();
    return;
}

// returns the type under from anypoint in the matrix
// importent for setting new blocks
typeObject Sokoban::getTypeUnderAtPosition(pair<int, int> position) {
    return matrix[position.second][position.first].getCurrTypeUnder();
}

// checks win condition
// returns win/true when all
// points of ben aquired by player
const bool Sokoban::isWon(void) {
    // std::count_if(v.begin(), v.end(), [](int i) { return i % 4 == 0; });
    int points = 0;
    std::for_each(matrix.begin(), matrix.end(),
    [&](vector<GameObject> i) {
        for (GameObject obj : i) {
            if (obj.getTypeObject() == stored) {
                points++;
            }
        }
    });
    // cout << "pointed scored score: " << points << endl;
    if (pointsToWin > points) {
        return false;
    } else {
        return true;
    }
}

// function goal is to validate if the next space is avaible for movement
void Sokoban::setMoveObjects(moveSet move) {
    GameObject nextBlock, nextCrateBlock;
    pair<int, int> previousLoc, newLoc;
    // see if player can move
    // getSpace at move
    nextPlayerMove.setMoveable(false);
    nextBlockMove.setMoveable(false);
    nextBlock = getNextSpace(move, playerLocation);

    // no move if wall or object is in state stored
    if (nextBlock.getTypeObject() == wall
            || nextBlock.getTypeObject() == stored) {
        nextPlayerMove.setMoveable(false);
        return;
    // if next block is crate condition
    } else if (nextBlock.getTypeObject() == crate) {
        // checks to see if a crate is a moveable object
        currentCrateLocation.first = nextBlock.getXlocation();
        currentCrateLocation.second = nextBlock.getYlocation();
        nextCrateBlock = getNextSpace(move, currentCrateLocation);
        // if wall or another crate both player and crate can't move
        if (nextCrateBlock.getTypeObject() == wall
                || nextCrateBlock.getTypeObject() == crate) {
            nextBlockMove.setMoveable(false);
            nextPlayerMove.setMoveable(false);
        } else if (nextCrateBlock.getTypeObject() == storage_space
                    || nextCrateBlock.getTypeObject() == floor) {
            // set move player
            nextPlayerMove.setMoveable(true);
            nextPlayerMove.setCurrSpace(playerLocation);
            newLoc.first = nextBlock.getXlocation();
            newLoc.second = nextBlock.getYlocation();
            nextPlayerMove.setNextSpace(newLoc);

            // set move block
            nextBlockMove.setMoveable(true);
            previousLoc.first = nextBlock.getXlocation();
            previousLoc.second = nextBlock.getYlocation();
            nextBlockMove.setCurrSpace(previousLoc);
            newLoc.first = nextCrateBlock.getXlocation();
            newLoc.second = nextCrateBlock.getYlocation();
            nextBlockMove.setNextSpace(newLoc);
        }
        return;
    }
    // default condtion player is movable
    nextPlayerMove.setMoveable(true);
    nextPlayerMove.setCurrSpace(playerLocation);
    newLoc.first = nextBlock.getXlocation();
    newLoc.second = nextBlock.getYlocation();
    nextPlayerMove.setNextSpace(newLoc);
}

// checks what game object is at the next space based of user input
GameObject& Sokoban::getNextSpace(moveSet move, pair<int, int> CurrObjectLoc) {
    int nextX, nextY;
    nextX = CurrObjectLoc.first;
    nextY = CurrObjectLoc.second;
    switch (move) {
    case up:
        nextY -= 1;
        break;
    case down:
        nextY += 1;
        break;
    case left:
        nextX -= 1;
        break;
    case right:
        nextX += 1;
        break;
    default:
        return matrix[CurrObjectLoc.first][CurrObjectLoc.second];
        break;
    }
    return matrix[nextY][nextX];
}

// function uses two moveObjects one to replace
// the object on the space it is being moved from
// i.e. the replace object, the other object is
// the one being move to another location the moving
// object, which retains its curr type but the type
// under changes to that of the object which was
// originaly there
bool Sokoban::executeMoveObjects(void) {
    GameObject replaceBlock, movingBlock;
    pair<int, int> oldPosition, newPosition;
    if (nextPlayerMove.getMovable() == false
            && nextBlockMove.getMovable() == false) {
        return false;
    } else if (nextPlayerMove.getMovable() == true
                && nextBlockMove.getMovable() == true) {
        // move crate & updateMap;
        oldPosition = nextBlockMove.getCurrSpace();
        newPosition = nextBlockMove.getNextSpace();
        // if crate is on storage space change to stored state
        if (getTypeUnderAtPosition(newPosition) == storage_space) {
            replaceBlock.setBlock(oldPosition.first, oldPosition.second,
                        getTypeUnderAtPosition(oldPosition), textureMap);
            // set stored state on crate at new location
            movingBlock.setBlock(newPosition.first,
                        newPosition.second, stored, textureMap);
            movingBlock.setCurrTypeUnder(getTypeUnderAtPosition(newPosition));
            moveMatrixBlocks(replaceBlock, movingBlock);
            // pointsToWin--; 
        } else {
            replaceBlock.setBlock(oldPosition.first, oldPosition.second,
                    getTypeUnderAtPosition(oldPosition), textureMap);
            replaceBlock.setCurrTypeUnder(replaceBlock.getTypeObject());

            movingBlock.setBlock(newPosition.first,
                    newPosition.second, crate, textureMap);
            movingBlock.setCurrTypeUnder(getTypeUnderAtPosition(newPosition));
            moveMatrixBlocks(replaceBlock, movingBlock);
        }
        // move player, updateMap, update currLocation
        oldPosition = nextPlayerMove.getCurrSpace();
        newPosition = nextPlayerMove.getNextSpace();

        replaceBlock.setBlock(oldPosition.first, oldPosition.second,
                    getTypeUnderAtPosition(oldPosition), textureMap);
        replaceBlock.setCurrTypeUnder(replaceBlock.getTypeObject());

        movingBlock.setBlock(newPosition.first,
                    newPosition.second, player, textureMap);
        movingBlock.setCurrTypeUnder(
                matrix[newPosition.second][newPosition.first].getTypeObject());
        playerLocation = newPosition;
        moveMatrixBlocks(replaceBlock, movingBlock);
        return true;
    } else if (nextPlayerMove.getMovable() == true
                    && nextBlockMove.getMovable() == false) {
        oldPosition = nextPlayerMove.getCurrSpace();
        newPosition = nextPlayerMove.getNextSpace();

        // always get the type that will be under player
        replaceBlock.setBlock(oldPosition.first, oldPosition.second,
                    getTypeUnderAtPosition(oldPosition), textureMap);
        replaceBlock.setCurrTypeUnder(replaceBlock.getTypeObject());
        movingBlock.setBlock(newPosition.first,
                    newPosition.second, player, textureMap);
        movingBlock.setCurrTypeUnder(
                matrix[newPosition.second][newPosition.first].getTypeObject());
        playerLocation = newPosition;
        moveMatrixBlocks(replaceBlock, movingBlock);
        return true;
    }
    return false;
}

// replaces the block being moved with replace block
// and puts moving block in its new position
void Sokoban::moveMatrixBlocks(const GameObject& replaceBlock,
                                    const GameObject& movingBlock) {
    matrix[replaceBlock.getYlocation()][replaceBlock.getXlocation()]
                = replaceBlock;
    matrix[movingBlock.getYlocation()][movingBlock.getXlocation()]
                = movingBlock;
}

// renders the game map using the information
// contained in the matrix's gameObjects
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
            setDrawPos(location, block, textureSize);
            // if there is a layered block the type under must be drawn first
            if (block.getTypeObject() == player
                    || block.getTypeObject() == stored) {
                pos = textureMap.find(block.getCurrTypeUnder());
                floorTexture = pos->second;
                floorSprite.setTexture(floorTexture);
                floorSprite.setPosition(location);
                target.draw(floorSprite, states);
            }
            sprite = matrix[y][x].getSprite();
            sprite.setPosition(location);
            target.draw(sprite, states);
        }
    }
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
            playerLocation.first = x;
            playerLocation.second = y;
            block.setCurrTypeUnder(floor);
            break;
        case '#':
            texture.loadFromFile("sokoban/images/block_06.png");
            setTextureInMap(wall, texture);
            block.setBlock(x, y, wall, textureMap);
            block.setCurrTypeUnder(floor);
            break;
        case '.':
            texture.loadFromFile("sokoban/images/ground_01.png");
            setTextureInMap(floor, texture);
            block.setBlock(x, y, floor, textureMap);
            block.setCurrTypeUnder(floor);
            break;
        case 'A':
            texture.loadFromFile("sokoban/images/crate_03.png");
            setTextureInMap(crate, texture);
            block.setBlock(x, y, crate, textureMap);
            block.setCurrTypeUnder(floor);
            break;
        case 'a':
            texture.loadFromFile("sokoban/images/ground_04.png");
            setTextureInMap(storage_space, texture);
            block.setBlock(x, y, storage_space, textureMap);
            block.setCurrTypeUnder(storage_space);
            pointsToWin++;
            break;
        case '1':
            texture.loadFromFile("sokoban/images/ground_01.png");
            setTextureInMap(crate, texture);
            block.setBlock(x, y, stored, textureMap);
            block.setCurrTypeUnder(floor);
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

void Sokoban::setSokobanMatrix(const vector<GameObject>& blocks) {
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

ifstream& operator>>(ifstream& in, Sokoban& level) {
    // objects and var
    int xtemp, ytemp;
    vector<GameObject> objects, tempVec;
    level.pointsToWin = 0;
    // make sure matirx is clear before it is used again.
    level.matrix.clear();
    // take map size input
    in >> xtemp;
    in >> ytemp;
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

// loads new textures into map
void Sokoban::setTextureInMap(typeObject type, sf::Texture& texture) {
    textureMap[type] = texture;
}

// get drawing position of game object
void setDrawPos(sf::Vector2f& location,
            const GameObject& block, const pair<int, int>& xyCor) {
    location.x = block.getXlocation() * xyCor.first;
    location.y = block.getYlocation() * xyCor.second;
}
