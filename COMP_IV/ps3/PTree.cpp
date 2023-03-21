// Copyright [2023] <Daniel Bergeron>
#include "ps3_header/PTree.hpp"

PRec::PRec() {
    theta = 0;
    rectangle.setSize(sf::Vector2f(0, 0));
}
PRec::PRec(sf::RectangleShape _rectangle, int _theta) {
    rectangle = _rectangle;
    theta = _theta;
}

PTree::PTree() {
    depth = 0;
    baseRecSize = 0.0;
}
PTree::PTree(int _depth, double _baseRecSize) {
    depth = _depth;
    baseRecSize = _baseRecSize;
}

void PTree::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::RectangleShape shape;
    PRec rectangle;
    int i;
    for (i = 0; i < treeRectangle.size(); i++) {
        rectangle = treeRectangle[i];
        shape = rectangle.getRectangleShape();
        shape.setFillColor(sf::Color::Green);
        target.draw(shape, states);
    }
    return;
}

void PTree::pTree(void) {
    if (depth <= 0 && baseRecSize <= 0) {
        return;
    }
    sf::RectangleShape baseShape(sf::Vector2f(static_cast<float>(baseRecSize),
                        static_cast<float>(baseRecSize)));
    PRec basePRec;
    pair<float, float> coord;
    coord.first = (baseRecSize * 3.0) - (baseShape.getSize().x/2.0);
    coord.second = (baseRecSize * 3.5) - (baseShape.getSize().x/2.0);
    baseShape.setPosition(coord.first, coord.second);
    basePRec.SetRectangleShape(baseShape);
    basePRec.setTheta(0);
    treeRectangle.push_back(basePRec);

    pTreeRecursion(depth, basePRec);
}

// function will make two rectangles and push them onto the vector
void PTree::pTreeRecursion(int currdepth, PRec base) {
    if (currdepth == 0) {
        return;
    }
    PRec newLeftPRec, newRightPRec;
    sf::RectangleShape rectangleLeft, rectangleRight;
    sf::Vector2f sizeL, sizeR;

    // set the size
    sizeL.x = (base.getRectangleShape().getSize().x * cos((M_PI/180) * THETA));
    sizeL.y = sizeL.x;
    cout << sizeL.x << endl;
    sizeR.x = (base.getRectangleShape().getSize().y * sin((M_PI/180) * THETA));
    sizeR.y = sizeR.x;

    rectangleLeft.setSize(sizeL);
    rectangleRight.setSize(sizeR);

    // make new theta
    newLeftPRec.setTheta(base.getTheta() - THETA);
    newRightPRec.setTheta(base.getTheta() + THETA);

    // positioning
    sf::Vector2f posL, posR;
    sf::Rect gridLoc = base.getRectangleShape().getLocalBounds();

    rectangleLeft.setOrigin(0, rectangleLeft.getSize().y);
    rectangleRight.setOrigin(rectangleRight.getLocalBounds().width,
                    rectangleRight.getLocalBounds().height);

    posL = base.getRectangleShape().getTransform().transformPoint(gridLoc.left, gridLoc.top);
    posR = base.getRectangleShape().getTransform().transformPoint(gridLoc.left + gridLoc.width, gridLoc.top);

    rectangleLeft.setPosition(posL);
    rectangleRight.setPosition(posR);
    // applying to rectangle object

    rectangleLeft.setRotation(newLeftPRec.getTheta());
    rectangleRight.setRotation(newRightPRec.getTheta());


    newLeftPRec.SetRectangleShape(rectangleLeft);
    newRightPRec.SetRectangleShape(rectangleRight);

    // push
    treeRectangle.push_back(newLeftPRec);
    treeRectangle.push_back(newRightPRec);

    pTreeRecursion(currdepth - 1, newLeftPRec);
    pTreeRecursion(currdepth - 1, newRightPRec);
    return;
}
