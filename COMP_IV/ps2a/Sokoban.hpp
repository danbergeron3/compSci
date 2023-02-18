#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
using std::ifstream;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <vector>
using std::vector;



enum typeObject{nill, player, wall, floor, crate, storage_space, stored};

class GameObject{
    private: 
    int x;
    int y;
    typeObject object;
    public:
    
    GameObject() : x(0), y(0), object(nill){}
    GameObject(int _x, int _y, typeObject _object); 
    int getXlocation(void) const {return x; }
    int getYlocation(void) const {return y; }
    typeObject getBlock(void) const {return object; }
    void setBlock(int _x, int _y, typeObject _object) {x = _x; y = _y; object = _object; }
};

class Sokoban : public sf::Drawable{
    public:
    void movePlayer(void);

    //muttator
    void buildMatrix(vector<GameObject>& blocks);
    //void generateGameMap(void);
    
    //accessors
    GameObject& getGameObject(int x, int y) {return matrix[x][y]; }
    int getWidth(void){return xSize; }
    int getHeight(void){return ySize; } 
    sf::Sprite getSprite(GameObject& block);
    
    friend ifstream& operator>>(ifstream& in, Sokoban& object);

    private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    int xSize;
    int ySize;
    sf::Sprite sprite;
    sf::Texture texture;
    std::string filename;
    vector<vector<GameObject>> matrix;
};

ifstream& operator>>(ifstream& in, Sokoban& object);
bool insert(ifstream& in, vector<GameObject>& objects, int x, int y);

//is passed GameObjects, and its x & y pixel sizes 
void makePixelCoordinate(sf::Vector2f& location, GameObject& block, int xPixel, int yPixel);