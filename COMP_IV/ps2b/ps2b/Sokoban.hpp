#ifndef _HOME_DBERGERO3_PROGRAMS_COMP4_PS2B_PS2B_SOKOBAN_HPP_
#define _HOME_DBERGERO3_PROGRAMS_COMP4_PS2B_PS2B_SOKOBAN_HPP_
/* "Copyright [2023] <Daniel Bergeron>" */
#include <fstream>
using std::ifstream;
#include <utility>
using std::pair;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <map>
using std::map;
#include <algorithm>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// enum describes set of object types and move types
enum typeObject{nill, player, wall, floor, crate, storage_space, stored};
enum moveSet{noMove, up, down, left, right, restart, quiet};

class MoveObject {
 public:
      // constructor
      MoveObject();
      // accessor
      pair<int, int> getCurrSpace(void)const {return currSpace; }
      pair<int, int> getNextSpace(void)const {return nextSpace; }
      bool getMovable(void) {return moveable; }
      // mutators
      void setCurrSpace(pair<int, int> _next) {currSpace = _next; }
      void setNextSpace(pair<int, int> _next) {nextSpace = _next; }
      void setMoveable(bool _moveable) {moveable = _moveable; }
 private:
      bool moveable;
      pair<int, int> currSpace;
      pair<int, int> nextSpace;
};

class GameObject {
 private:
    int x;
    int y;
    typeObject object;
    typeObject currTypeUnder;  // the type under if object is layered
    sf::Sprite sprite;
 public:
    // constructors
    GameObject() : x(0), y(0), object(nill), currTypeUnder(nill) {}
    GameObject(int _x, int _y, typeObject _object);
    // accessors
    int getXlocation(void) const {return x; }
    int getYlocation(void) const {return y; }
    typeObject getCurrTypeUnder(void) const {return currTypeUnder; }
    typeObject getTypeObject(void) const {return object; }
    sf::Sprite getSprite(void) const {return sprite; }
    // mutators
    void setBlock(int _x, int _y, typeObject _object, map<typeObject, sf::Texture>& texture);
    void setCurrTypeUnder(typeObject type) {currTypeUnder = type; }
};

class Sokoban : public sf::Drawable {
 public:
    // constructor
    Sokoban();
    // pre: is given a move command
    // post: player will be moved by command
    void movePlayer(moveSet move);
    // muttator
    void setSokobanMatrix(const vector<GameObject>& blocks);
    void setPlayerPosition(int x, int y) {playerLocation.first = x, playerLocation.second = y; }
    // accessors
    // pre: passed x & y values inside bounds of matrix
    // post: returns GameObject at location
    GameObject& getGameObject(const int y, const int x) {return matrix[y][x]; }

    typeObject getTypeUnderAtPosition(pair<int, int>);
    int getWidth(void) const {return xSize; }
    int getHeight(void) const  {return ySize; }
    int getTextureSizeX(void) const {return textureSize.first; }
    int getTextureSizeY(void) const {return textureSize.second; }
    GameObject& getNextSpace(moveSet move, pair<int, int> CurrObjectLoc);
    const bool isWon(void);
    friend ifstream& operator>>(ifstream& in, Sokoban& object);

 private:
    // overides sf::Drawable virtual function
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    // is a helper fucntion for the >> operator overload
    // pre: takes a vaild filestream, vector of gameObjects and coordintes
    // post: returns true if item was succesfully put in vector
    bool buildGameObjectVector(ifstream& in, vector<GameObject>& objects);
    // pre: takes valid type and texture reffrence
    // post: sets inside texture map
    void setTextureInMap(typeObject type, sf::Texture& texture);
    // pre: takes commands
    // post: returns list of commands in order
    void setMoveObjects(moveSet move);
    // pre: is called
    // updates matrix using movevlocks
    bool executeMoveObjects(void);

    void moveMatrixBlocks(const GameObject& replaceBlock, const GameObject& movingBlock);

    int xSize;
    int ySize;
    int pointsToWin;
    MoveObject nextPlayerMove;
    MoveObject nextBlockMove;
    pair<int, int> playerLocation;
    pair<int, int> currentCrateLocation;
    pair<int, int> textureSize;
    vector<vector<GameObject>> matrix;
    map<typeObject, sf::Texture> textureMap;
};

// pre: is passed valid file stream & Sokoban object
// post: returns file stream & fills Sokoban
ifstream& operator>>(ifstream& in, Sokoban& object);

// pre: Is passed valid Vector2f, GameObjects, and int pair, pixel sizes
// post: returns updated an updated Vector2f
void setDrawPos(sf::Vector2f& location, const GameObject& block, const pair<int, int>& xyCor);

// pre: passed a valid texture size
// post: returns a pair with xy size
void getTexturePixelSize(const sf::Texture&, pair<int, int>& cor);

#endif  // _HOME_DBERGERO3_PROGRAMS_COMP4_PS2B_PS2B_SOKOBAN_HPP_
