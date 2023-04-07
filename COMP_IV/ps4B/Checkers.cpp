// "Copyright [2023] Daniel Bergeron"
#include "Headers/Checkers.hpp"

// consturctors
Piece::Piece(bool _isKing, bool _isHighLighted, bool _isPresent,
        pieceType _type, sf::Sprite _sprite, sf::RectangleShape _highlight) {
    isKing = _isKing;
    isHighLighted = _isHighLighted;
    type = _type;
    sprite = _sprite;
    highlight = _highlight;
    isPresent = _isPresent;
}

Checkers::Checkers() {
    tileSize.x = static_cast<float>(SPACESIZES);
    tileSize.y = tileSize.x;

    currHighLight.x = -1;
    currHighLight.y = -1;

    // load background()
    loadBackground();

    // loadstextures into map
    loadTextureMap();

    // adds pieces to matrix
    loadPieceMatrix();

    // loads moves into map
    loadMoveMap();
}

void Checkers::loadMoveMap(void) {
    // enum moveSet {nil, upLeft, upRight, downLeft, downRight, upLeftJump,
    // upRightJump, downRightJump, downLeftJump };
    sf::Vector2i moveVal;
    moveVal.x = 0; moveVal.y = 0;
    moveMap[nil] = moveVal;
    moveVal.x = -1; moveVal.y = -1;
    moveMap[upLeft] = moveVal;
    moveVal.x = 1; moveVal.y = -1;
    moveMap[upRight] = moveVal;
    moveVal.x = 1; moveVal.y = 1;
    moveMap[downLeft] = moveVal;
    moveVal.x = -1; moveVal.y = 1;
    moveMap[downRight] = moveVal;
    moveVal.x = -2; moveVal.y = -2;
    moveMap[upLeftJump] = moveVal;
    moveVal.x = 2; moveVal.y = -2;
    moveMap[upRightJump] = moveVal;
    moveVal.x = -2; moveVal.y = 2;
    moveMap[downRightJump] = moveVal;
    moveVal.x = 2; moveVal.y = 2;
    moveMap[downLeftJump] = moveVal;
    return;
}

// helper functions for constructor
// loads static tile background
void Checkers::loadBackground(void) {
    sf::RectangleShape tile;
    pieceType previousColor = black;
    tile.setSize(tileSize);

    for (int i = 0; i < GAMEBOARDLENGTH; i++) {
        // gives checker offsett for each row
        if (i % 2 != 0) {
            previousColor = red;
        } else {
            previousColor = black;
        }
        // gives checker offsett for each cloumn
        for (int j = 0; j < GAMEBOARDLENGTH; j++) {
            if (previousColor == black) {
                tile.setFillColor(sf::Color::Red);
                previousColor = red;
            } else if (previousColor == red) {
                tile.setFillColor(sf::Color::Black);
                previousColor = black;
            }
            tile.setPosition(tileSize.x * i, tileSize.x * j);
            background[i][j] = tile;
        }
    }
}

// loads the piece matirx into checkers
// this matrix is dynamic
void Checkers::loadPieceMatrix(void) {
    // bool _isKing, bool _isHighLighted, bool _isPresent, pieceType _type,
    // sf::Sprite _sprite, sf::RectangleShape _highlight)
    // vector<vector<Piece>> pieceMatrix;
    sf::Sprite sprite;
    sf::RectangleShape highlight;
    sf::Vector2f mapPos;
    int offset = 0;

    highlight.setSize(tileSize);
    highlight.setFillColor(sf::Color::Yellow);
    sprite.setTexture(textureMap[black]);
    Piece pawn(false, false, true, black, sprite, highlight);

    // fill y axis
    for (int i = 0; i < GAMEBOARDLENGTH; i++) {
        vector<Piece> pRow;
        pieceMatrix.push_back(pRow);
    }

    for (int i = 0; i < GAMEBOARDLENGTH; i++) {
        offset = i;
        for (int j = 0; j < GAMEBOARDLENGTH; j++) {
            mapPos.x = i;
            mapPos.y = j;
            pawn.setPosition(mapPos);
            if (j > UPPERBOARDLIMIT) {
                    pawn.setType(red);
                    sprite.setTexture(textureMap[red]);
                    pawn.setSprite(sprite);
            } else {
                pawn.setType(black);
                sprite.setTexture(textureMap[black]);
                pawn.setSprite(sprite);
            }
            if (j > UPPERBOARDLIMIT && j < LOWERBOARDLIMIT) {
                pawn.setType(empty);
                pawn.setIsPresent(false);
            } else {
                (offset % 2 == 0) ? pawn.setIsPresent(false)
                        :pawn.setIsPresent(true);
            }
            pieceMatrix[i].push_back(pawn);
            offset++;
        }
    }
}

// loads a texture map for sprites to
// acces since they having a lot of textures
// is heavy
void Checkers::loadTextureMap(void) {
    sf::Texture texture;
    texture.loadFromFile("resources/blackking.png");
    textureMap[blackKing] = texture;
    texture.loadFromFile("resources/blackpawn.png");
    textureMap[black] = texture;
    texture.loadFromFile("resources/redking.png");
    textureMap[redKing] = texture;
    texture.loadFromFile("resources/redpawn.png");
    textureMap[red] = texture;
}

// draw function is a overrides of sfml drawable
void Checkers::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    Piece piece;
    sf::Vector2f posOffsett;
    sf::Sprite spritePiece;
    sf::RectangleShape highLight;
    for (int i = 0; i < GAMEBOARDLENGTH; i++) {
        for (int j = 0; j < GAMEBOARDLENGTH; j++) {
            target.draw(background[i][j], states);
            piece = pieceMatrix[i][j];
            if (piece.getIsPresent() == true) {
                posOffsett = piece.getPosition();
                posOffsett.x = posOffsett.x * SPACESIZES;
                posOffsett.y = posOffsett.y * SPACESIZES;
                if (piece.getIsHighLighted() == true) {
                    highLight = piece.getHighLighted();
                    highLight.setPosition(posOffsett);
                    target.draw(highLight, states);
                }
                spritePiece = piece.getSprite();
                spritePiece.setPosition(posOffsett);
                target.draw(spritePiece, states);
            }
        }
    }
    return;
}

// is passed a moses position in pixel space
// highlights the piece in tile space
void Checkers::highLight(sf::Vector2i localPosition) {
    // highlight current selection
    int colorTurn = getTurn();
    Piece selected = pieceMatrix[localPosition.x / SPACESIZES]
                [localPosition.y / SPACESIZES];
    // if piece exsits highlight else do nothing
    if (selected.getIsPresent() == true) {
        if (colorTurn == 0 && selected.getpieceType() >= black) {
            return;
        } else if (colorTurn == 1 && selected.getpieceType() < black) {
            return;
        }
    } else {
        return;
    }
    selected.setIsHighLighted(true);

    pieceMatrix[localPosition.x / SPACESIZES]
                [localPosition.y / SPACESIZES] = selected;

    // remove previous selection
    if (currHighLight == selected.getPosition()) {
        currPiece = selected;
        return;
    }
    if (currHighLight.x >= 0 && currHighLight.y >= 0) {
        pieceMatrix[currHighLight.x][currHighLight.y].setIsHighLighted(false);
    }
    currHighLight.x = selected.getPosition().x;
    currHighLight.y = selected.getPosition().y;
    currPiece = selected;
    return;
}


// is already converted to tile space
bool Checkers::move(sf::Vector2i LocalPosition) {
    // first check if piece at location is present
    // or if it is the selected piece
    Piece newPiece = pieceMatrix[LocalPosition.x][LocalPosition.y];
    if (newPiece.getIsPresent() == true
                || newPiece.getIsHighLighted() == true) {
        return false;
    }

    // call function to seee if local position matches anything in moveset
    // if so return move to use
    moveSet currMove;
    currMove = getMovetype(LocalPosition);
    if (currMove == nil) {
        return false;
    }
    // check if king
    // if king all moves from here are valid
    // call a function to execute move if
    // if king condition fails move based on color
    // get piece color & branch based off piece color
    // red only moves up and black down
    // inside color if's
    pieceType currType = currPiece.getpieceType();
    if (currType == red) {
        if (currMove == downLeft || currMove == downRight
            || currMove == downLeftJump || currMove == downRightJump) {
                return false;
        }
    } else if (currType == black) {
        if (currMove == upLeft || currMove == upRight
            || currMove == upLeftJump || currMove == upRightJump) {
                return false;
        }
    }
    resetHighLight();
    // if execute happens piece is move into Local position on matrix
    // if executed then new turn
    if (executeMove(currMove)) {
        increaseTurn();
    }

    // after move, check if piece is in the bottom(black)
    // or top(red) if so call king function
    if ((currType == black && LocalPosition.y == 7)
            || (currType == red && LocalPosition.y == 0)) {
        makeKing(currType, LocalPosition);
    }

    // return true if move worked
    return true;
}

// goal of function is to validate the seleceted space
// need to figure out where curr piece is in regards to newSpace
moveSet Checkers::getMovetype(sf::Vector2i LPosition) {
    Piece emptySpace;
    moveSet move = nil;
    sf::Vector2i offset;
    offset.x = currPiece.getPosition().x;
    offset.y = currPiece.getPosition().y;

    // 1) use map to store what each move does mathamtically
    // 2) using the curr pieces positon use the pair retieved from
    // map add x & y together if the the sums agree return move type

    map<moveSet, sf::Vector2i>::iterator m;
    for (m = moveMap.begin(); m != moveMap.end(); ++m) {
        offset.x += m->second.x;
        offset.y += m->second.y;
        move = m->first;
        if (offset == LPosition) {
            return move;
        } else {
            offset.x = currPiece.getPosition().x;
            offset.y = currPiece.getPosition().y;
            move = nil;
        }
    }
    return move;
}

// resest highlight for next draw cycle
void Checkers::resetHighLight(void) {
    Piece selected = pieceMatrix[currHighLight.x][currHighLight.y];
    selected.setIsHighLighted(false);
    pieceMatrix[currHighLight.x][currHighLight.y] = selected;
    return;
}

bool Checkers::executeMove(moveSet currMove) {
    // if move is jump remove middle piece
    // jumps are negative since piece will be taken
    // so go to a normal move space in that direction
    // and check if piece is present if not move fails
    bool failedJumped;
    if (currMove < 0) {
        failedJumped = removePiece(static_cast<moveSet>(abs(currMove)));
        if (failedJumped) {
            cout << "jump failed\n";
            return false;
        }
    }
    Piece newPiece;
    // set new position
    sf::Vector2i pos = moveMap[currMove];
    pos.x += currPiece.getPosition().x;
    pos.y += currPiece.getPosition().y;

    newPiece = currPiece;
    newPiece.setPosition(static_cast<sf::Vector2f>(pos));
    newPiece.setIsHighLighted(false);
    // enable new piece with same attributes as currpiece
    pieceMatrix[pos.x][pos.y] = newPiece;
    // disable currPiece
    currPiece.setIsPresent(false);
    currPiece.setType(empty);
    currPiece.setIsHighLighted(false);
    pieceMatrix[currPiece.getPosition().x][currPiece.getPosition().y]
        = currPiece;
    return true;
}

void Checkers::makeKing(pieceType currType, sf::Vector2i pos) {
    sf::Sprite sprite;
    Piece king =  pieceMatrix[pos.x][pos.y];
    int x = currType;
    x++;
    currType = static_cast<pieceType>(x);
    king.setType(currType);
    king.setIsKing(true);
    sprite.setTexture(textureMap[currType]);
    king.setSprite(sprite);

    pieceMatrix[pos.x][pos.y] = king;
}

bool Checkers::removePiece(moveSet destroyMove) {
    // need moving pieces to test come back to later

    sf::Vector2i pos = moveMap[destroyMove];
    pos.x += currPiece.getPosition().x;
    pos.y += currPiece.getPosition().y;
    if ( pieceMatrix[pos.x][pos.y].getIsPresent() == false ) {
        return true;
    }
    // checks to see if they are jumping their own pawn
    pieceType currType = currPiece.getpieceType();
    if (currPiece.getIsKing()) {
        if ( pieceMatrix[pos.x][pos.y].getpieceType() == currType
        || pieceMatrix[pos.x][pos.y].getpieceType() == currType - 1) {
            return true;
        }
    } else {
        if ( pieceMatrix[pos.x][pos.y].getpieceType() == currType
            || pieceMatrix[pos.x][pos.y].getpieceType() == currType + 1) {
            return true;
        }
    }
    pieceMatrix[pos.x][pos.y].setIsPresent(false);
    pieceMatrix[pos.x][pos.y].setType(empty);
    return false;
}

int Checkers::getTurn(void) {
    return turn % 2;
}

// returns last color standing
bool Checkers::endGameCheck(void) {
    redWin = 0;
    blackWin = 0;
    vector<vector<Piece>>::iterator pieceVec = pieceMatrix.begin();
    vector<Piece>::iterator p;

    auto presentCheck = [&](Piece guy){
        if (guy.getIsPresent() == true) {
                if (guy.getpieceType() == red
                            || guy.getpieceType() == redKing) {
                    redWin++;
                } else if (guy.getpieceType() == black
                            || guy.getpieceType() == blackKing) {
                    blackWin++;
                }
            }
    };
    for ( ; pieceVec != pieceMatrix.end(); pieceVec++) {
        std::for_each(pieceVec->begin(), pieceVec->end(), presentCheck);
    }
    if (redWin == 0 || blackWin == 0) {
        return true;
    } else {
        return false;
    }
}
