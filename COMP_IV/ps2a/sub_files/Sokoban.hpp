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
 public:
    // constructors
    GameObject() : x(0), y(0), object(nill) {}
    GameObject(int _x, int _y, typeObject _object);
    // accessors
    int getXlocation(void) const {return x; }
    int getYlocation(void) const {return y; }
    typeObject getTypeObject(void) const {return object; }
    // mutators
    void setBlock(int _x, int _y, typeObject _object) {x = _x; y = _y; object = _object; }
};

class Sokoban : public sf::Drawable {
 public:
    // TODO(Daniel): develop moveplayer in part B
    void movePlayer(moveSet move);
    // muttator
    void setSokobanMatrix(vector<GameObject>& blocks);
    void setSprite(GameObject& block);
    // accessors
    // pre: passed x & y values inside bounds of matrix
    // post: returns GameObject at location
    GameObject& getGameObject(const int y, const int x) {return matrix[y][x]; }
    int getWidth(void) {return xSize; }
    int getHeight(void) {return ySize; }
    sf::Sprite getSprite(void) {return sprite; }
    friend ifstream& operator>>(ifstream& in, Sokoban& object);

 private:
    // overides sf::Drawable virtual function
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    int xSize;
    int ySize;
    sf::Sprite sprite;
    sf::Texture texture;
    vector<vector<GameObject>> matrix;
};

// pre: is passed valid file stream & Sokoban object
// post: returns file stream & fills Sokoban
ifstream& operator>>(ifstream& in, Sokoban& object);

// insert is a helper fucntion for the >> operator overload
// pre: takes a vaild filestream, vector of gameObjects and coordintes
// post: returns true if item was succesfully put in vector
bool insert(ifstream& in, vector<GameObject>& objects, int x, int y);

// pre: Is passed valid Vector2f, GameObjects, and int pair, pixel sizes
// post: returns updated an updated Vector2f
void getDrawPos(sf::Vector2f& location, const GameObject& block, const pair<int, int>& xyCor);
