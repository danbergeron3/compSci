// "Copyright [2023] Daniel Bergeron"
#include "Headers/Checkers.hpp"

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
}

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

// map<pieceType, sf::Texture> textureMap;
void Checkers::loadTextureMap(void) {
    sf::Texture texture;
    texture.loadFromFile("checkers/blackking.png");
    textureMap[blackKing] = texture;
    texture.loadFromFile("checkers/blackpawn.png");
    textureMap[black] = texture;
    texture.loadFromFile("checkers/redking.png");
    textureMap[redKing] = texture;
    texture.loadFromFile("checkers/redpawn.png");
    textureMap[red] = texture;
}

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

void Checkers::highLight(sf::Vector2i localPosition) {
    // cout << "x:" << localPosition.x/64 << " y: "
    // << localPosition.y/64 <<endl;

    Piece selected = pieceMatrix[localPosition.x / SPACESIZES]
                [localPosition.y / SPACESIZES];
    if (selected.getIsPresent() == true) {
        selected.setIsHighLighted(true);
    }
    pieceMatrix[localPosition.x / SPACESIZES]
                [localPosition.y / SPACESIZES] = selected;

    // remove previous selection
    if (currHighLight == selected.getPosition()) {
        return;
    }
    if (currHighLight.x >= 0 && currHighLight.y >= 0) {
        pieceMatrix[currHighLight.x][currHighLight.y].setIsHighLighted(false);
    }
    currHighLight.x = selected.getPosition().x;
    currHighLight.y = selected.getPosition().y;
    return;
}
