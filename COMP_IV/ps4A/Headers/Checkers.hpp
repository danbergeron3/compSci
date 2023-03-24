#ifndef _HOME_DBERGERO3_PROGRAMS_COMP4_PS4A_HEADERS_CHECKERS_HPP_
#define _HOME_DBERGERO3_PROGRAMS_COMP4_PS4A_HEADERS_CHECKERS_HPP_
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
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

const int GAMEBOARDLENGTH = 8;
const int SPACESIZES = 64;
const int UPPERBOARDLIMIT = 2;
const int LOWERBOARDLIMIT = 5;

enum pieceType {red, black, redKing, blackKing};

class Piece {
 public:
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
    bool isKing;
    bool isHighLighted;
    bool isPresent;
    pieceType type;
    sf::Sprite sprite;
    sf::RectangleShape highlight;
    sf::Vector2f position;
};

class Checkers : public sf::Drawable {
 public:
    Checkers();
    void highLight(sf::Vector2i localPosition);

    // accessors
 private:
    // helper & private funcs
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    // load intial elements
    void loadTextureMap(void);
    void loadPieceMatrix(void);
    void loadBackground(void);

    // member vars
    sf::Vector2f tileSize;
    sf::Vector2f currHighLight;
    sf::RectangleShape background[GAMEBOARDLENGTH][GAMEBOARDLENGTH];
    vector<vector<Piece>> pieceMatrix;
    map<pieceType, sf::Texture> textureMap;
};



#endif  // _HOME_DBERGERO3_PROGRAMS_COMP4_PS4A_HEADERS_CHECKERS_HPP_
