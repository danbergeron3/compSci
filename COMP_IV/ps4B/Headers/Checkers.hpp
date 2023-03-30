#ifndef _HOME_DBERGERO3_PROGRAMS_COMP4_PS4B_HEADERS_CHECKERS_HPP_
#define _HOME_DBERGERO3_PROGRAMS_COMP4_PS4B_HEADERS_CHECKERS_HPP_
// Copyright [2023] <Daniel Bergeron>
// ptree class that derives from sf::Drawable
#include <iostream>
using std::cout;
using std::endl;
#include <utility>
using std::pair;
#include <string>
using std::string;
using std::stoi;
using std::stod;
#include <vector>
using std::vector;
#include <map>
using std::map;
#include <cmath>
using std::abs;
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// constants for conversions and intial set up
const int GAMEBOARDLENGTH = 8;
const int SPACESIZES = 64;
const int UPPERBOARDLIMIT = 2;
const int LOWERBOARDLIMIT = 5;

// type for pieces
enum pieceType {empty, red, redKing, black, blackKing};
enum moveSet { nil, upLeft = 1, upLeftJump = -1, upRight = 2,
upRightJump = -2, downRight = 3, downRightJump = -3,
downLeft = 4, downLeftJump = -4};

class Piece {
 public:
    // constructors
    Piece() : isKing(false), isHighLighted(false), type(red),
                                 isPresent(false) {}
    Piece(bool _isKing, bool _isHighLighted, bool _isPresent, pieceType _type,
            sf::Sprite _sprite, sf::RectangleShape _highlight);

    // accessors
    inline bool getIsPresent(void) {return isPresent; }
    inline bool getIsKing(void) {return isKing; }
    inline bool getIsHighLighted(void) {return isHighLighted; }
    inline pieceType getpieceType(void) {return type; }
    inline sf::Sprite getSprite(void) {return sprite; }
    inline sf::RectangleShape getHighLighted(void) {return highlight; }
    inline sf::Vector2f getPosition(void) {return position; }

    // muttators
    inline void setIsKing(bool _isKing) {isKing = _isKing; }
    inline void setIsHighLighted(bool _isSelected)
                                 {isHighLighted = _isSelected; }
    inline void setType(pieceType _type) {type = _type; }
    inline void setSprite(sf::Sprite _sprite) {sprite = _sprite; }
    inline void setHighLight(sf::RectangleShape _selected)
                                 {highlight = _selected; }
    inline void setIsPresent(bool _isPresent) {isPresent = _isPresent; }
    inline void setPosition(sf::Vector2f _position) {position = _position; }

 private:
    // bool vars tell if specifc piece attributes are ture or not
    bool isKing;
    bool isHighLighted;
    bool isPresent;
    // other mem vars
    pieceType type;
    sf::Sprite sprite;
    sf::RectangleShape highlight;
    sf::Vector2f position;
};

class Checkers : public sf::Drawable {
 public:
    // constructor
    Checkers();
    // tells if checkers class to enable a pieces highlight attribute
    void highLight(sf::Vector2i localPosition);

    // move function
    bool move(sf::Vector2i LocalPosition);

    inline void increaseTurn(void) {turn++; }
    int getTurn(void);
    bool endGameCheck();

 private:
    // helper & private funcs
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // move helper functions
    moveSet getMovetype(sf::Vector2i LocalPosition);
    void resetHighLight(void);

    bool executeMove(moveSet currMove);

    // execute helper
    bool removePiece(moveSet destroy);


    void makeKing(pieceType currType, sf::Vector2i LocalPosition);

    // load intial elements
    void loadTextureMap(void);
    void loadPieceMatrix(void);
    void loadBackground(void);
    void loadMoveMap(void);

    // member vars
    int turn = 0;
    Piece currPiece;
    sf::Vector2f tileSize;
    sf::Vector2f currHighLight;
    sf::RectangleShape background[GAMEBOARDLENGTH][GAMEBOARDLENGTH];
    vector<vector<Piece>> pieceMatrix;
    map<pieceType, sf::Texture> textureMap;
    map<moveSet, sf::Vector2i> moveMap;
};

#endif  // _HOME_DBERGERO3_PROGRAMS_COMP4_PS4B_HEADERS_CHECKERS_HPP_
