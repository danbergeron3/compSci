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
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// enum describes set of object types and move types
enum typeObject{nill, player, wall, floor, crate, storage_space, stored};
enum moveSet{noMove, up, down, left, right};

class GameObject {
 private:
    int x;
    int y;
    typeObject object;
    sf::Sprite sprite;
 public:
    // constructors
    GameObject() : x(0), y(0), object(nill) {}
    GameObject(int _x, int _y, typeObject _object);
    // accessors
    int getXlocation(void) const {return x; }
    int getYlocation(void) const {return y; }
    typeObject getTypeObject(void) const {return object; }
    sf::Sprite getSprite(void) const {return sprite; }
    // mutators
    void setBlock(int _x, int _y, typeObject _object, map<typeObject, sf::Texture>& texture);
};

class Sokoban : public sf::Drawable {
 public:
    // constructor
    Sokoban();
    // TODO(Daniel): develop moveplayer in part B
    void movePlayer(moveSet move);
    // muttator
    void setSokobanMatrix(vector<GameObject>& blocks);
    // accessors
    // pre: passed x & y values inside bounds of matrix
    // post: returns GameObject at location
    GameObject& getGameObject(const int y, const int x) {return matrix[y][x]; }
    int getWidth(void) {return xSize; }
    int getHeight(void) {return ySize; }
    int getTextureSizeX(void) const {return textureSize.first; }
    int getTextureSizeY(void) const {return textureSize.second; }
    friend ifstream& operator>>(ifstream& in, Sokoban& object);

 private:
    // overides sf::Drawable virtual function
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    // is a helper fucntion for the >> operator overload
    // pre: takes a vaild filestream, vector of gameObjects and coordintes
    // post: returns true if item was succesfully put in vector
    bool buildGameObjectVector(ifstream& in, vector<GameObject>& objects);
    void setTextureInMap(typeObject type, sf::Texture& texture);
    int xSize;
    int ySize;
    vector<vector<GameObject>> matrix;
    // edit
    pair<int, int> textureSize;
    map<typeObject , sf::Texture> textureMap;
};

// pre: is passed valid file stream & Sokoban object
// post: returns file stream & fills Sokoban
ifstream& operator>>(ifstream& in, Sokoban& object);

// pre: Is passed valid Vector2f, GameObjects, and int pair, pixel sizes
// post: returns updated an updated Vector2f
void getDrawPos(sf::Vector2f& location, const GameObject& block, const pair<int, int>& xyCor);

void getTexturePixelSize(sf::Texture texture, pair<int, int>& cor);
