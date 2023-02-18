#include <SFML/System.hpp>
using namespace std;
#include <SFML/Window.hpp>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace std;
#include <fstream>
using namespace std;
#include <iostream>
using namespace std;
#include <vector>
using namespace std;

#include "Sokoban.hpp"

enum typeObject{nill, player, wall, floor, box, storage_space, stored};

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
    typeObject getObject(void) const {return object; }
    void setBlock(int _x, int _y, typeObject _object) {x = _x; y = _y; object = _object; }
};

class Sokoban : public sf::Drawable{
    public:
    void buildMap(vector<GameObject>& blocks);
    void generateGameMap(void);
    friend ifstream& operator>>(ifstream& in, Sokoban& object);

    
    private:
    sf::Sprite& getSprite(GameObject& block);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    int xSize;
    int ySize;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Image image;
    std::string filename;
    vector<vector<GameObject>> matrix;
};

   ifstream& operator>>(ifstream& in, Sokoban& object);
   bool insert(ifstream& in, vector<GameObject>& objects, int x, int y);

int main(){
    Sokoban lv;
    ifstream fp;
    fp.open("level1.txt");
    fp >> lv;
    lv.generateGameMap();



    fp.close();
    cout << "hello\n";
    return 0;
}

void Sokoban::generateGameMap(void){
        sf::RenderWindow window(sf::VideoMode(1000, 1000), "Input");
    //read game object from matrix 
        GameObject block;  
        //get Sprite
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed){
                    window.close();
                }
            }
            //for(int i = 0; i < ySize; i++){
              //  for(int j = 0; j < xSize; j++){
                    //block = matrix[j][i];
                    //sprite = getSprite(block);
                    //window.clear(sf::Color::White);
                    //window.draw(sprite);
                    //window.display();
              //  }
            //}   
            window.clear(sf::Color::White);
            //window.draw(sprite);
            window.display();
        }
        return;
}
/*sf::Sprite& getSprite(GameObject& block){
    //nill, player, wall, floor, box, storage_space, stored};
    switch(block.getObject()){
        case player:
            block.setBlock(x, y, player);
            x++;
            break;
        case wall:
            block.setBlock(x, y, wall);
            x++;
            break;
        case '.':
            block.setBlock(x, y, floor);
            x++;
            break;
        case 'A':
            block.setBlock(x, y, box);
            x++;
            break;
        case 'a':
            block.setBlock(x, y, storage_space);
            x++;
            break;
        case '1':
            block.setBlock(x, y, stored);
            x++;
            break;
        default:
            return false;} 

}*/
void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const{
   target.draw(sprite, states);
}

GameObject::GameObject(int _x, int _y, typeObject _object){
    x = _x;
    y = _y;
    object = _object;
}

ifstream& operator>>(ifstream& in, Sokoban& level){
    //objects and var
    int xtemp, ytemp;
    vector<GameObject> objects, tempVec;

    //take map size input 
    in >> xtemp >> ytemp;
    if(xtemp <= 0 && ytemp <= 0){
        exit(1);
    }
    level.xSize = xtemp;
    level.ySize = ytemp;

    //make matrix outline
    level.matrix.resize(ytemp);
    for(int i = 0; i < static_cast<int>(level.matrix.size()); i++){
        for(int j = 0; j < xtemp; j++){
            GameObject empty;
            level.matrix[i].push_back(empty);
        }
    }

    //start reading chars
    //use to build Game objects
    //place in input vector
    if(insert(in, objects, xtemp, ytemp)){
        level.buildMap(objects);
    }
    
    //build map
    return in;
}

bool insert(ifstream& in, vector<GameObject>& objects, int xLimit, int yLimit){
    char input;
    int x = 0, y = 0;
    while(!(in.eof())){
        GameObject block;
        in >> input;
        switch (input){
        case '@':
            block.setBlock(x, y, player);
            x++;
            break;
        case '#':
            block.setBlock(x, y, wall);
            x++;
            break;
        case '.':
            block.setBlock(x, y, floor);
            x++;
            break;
        case 'A':
            block.setBlock(x, y, box);
            x++;
            break;
        case 'a':
            block.setBlock(x, y, storage_space);
            x++;
            break;
        case '1':
            block.setBlock(x, y, stored);
            x++;
            break;
        default:
            return false;}  
        if(y < yLimit){
            objects.push_back(block); 
        }
        if(x >= xLimit){
            y++;
            x = 0;
        }
        
    }
    return true;
}

void Sokoban::buildMap(vector<GameObject>& blocks){
    int x = 0, y = 0;
    int val = blocks.size();
    for(int i = 0; i < val; i++){
        x = blocks[i].getXlocation();
        y = blocks[i].getYlocation();
        matrix[y][x] = blocks[i];
    }
}


