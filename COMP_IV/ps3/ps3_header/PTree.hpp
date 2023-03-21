#ifndef _HOME_DBERGERO3_PROGRAMS_COMP4_PS3_PS3_HEADER_PTREE_HPP_
#define _HOME_DBERGERO3_PROGRAMS_COMP4_PS3_PS3_HEADER_PTREE_HPP_
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
#include <algorithm>
#include <vector>
using std::vector;
#include <cmath>
using std::sin;
using std::cos;
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

const float THETA = 45;

// need an object to hold rectangle
// hold a pair for its map loaction
// tells draw func where and how to draw
class PRec {
 public:
      // constructors
      PRec();
      PRec(sf::RectangleShape _rectangle, int _theta);
      // accessors
      sf::RectangleShape getRectangleShape(void) {return rectangle; }
      int getTheta(void) {return theta; }
      // muttators
      void SetRectangleShape(sf::RectangleShape _rectangle)
                                    {rectangle = _rectangle; }
      void setTheta(int _theta) {theta = _theta; }
 private:
      int theta;
      sf::RectangleShape rectangle;
};

class PTree : public sf::Drawable {
 public:
    PTree();
    PTree(int _depth, double _baseRecSize);

    // uses recurison to produce tree
    // pre: is called
    // post: tree is drawn
    void pTree(void);
 private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void pTreeRecursion(int currdepth, PRec base);
    // helper function to ptree
    // this function makes a rectangle
    vector<PRec> treeRectangle;
    int depth;
    double baseRecSize;
};

#endif  //  _HOME_DBERGERO3_PROGRAMS_COMP4_PS3_PS3_HEADER_PTREE_HPP_
