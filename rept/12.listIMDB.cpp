/***********************************************
    Author: Daniel Bergeron
    Date: 11/06/2022

    Purpose: The program produces a singualy linked list 
    using real world.
    
    3 things learned from this assignment:
        Learned how to utilize my first API
        learned how to research things I needed for my code
        Gained experience working in an unfamiliar work enviroment
    
    BRIDGES URL for this assignment: https://bridges-cs.herokuapp.com/assignments/11/danBergeron3
    
    Sources of Help: The bridges documentation

    Time Spent: <Insert how much time you spent
        on the assignment here>
***********************************************/
/*
Computing III -- COMP.2010 Honor Statement
The practice of good ethical behavior is essential for maintaining good order in the classroom,
providing an enriching learning experience for students, and as training as a practicing computing
professional upon graduation. This practice is manifested in the University’s Academic Integrity
policy. Students are expected to strictly avoid academic dishonesty and adhere to the Academic
Integrity policy as outlined in the course catalog. Violations will be dealt with as outlined therein.
All programming assignments in this class are to be done by the student alone. No outside help
is permitted except the instructor and approved tutors.
I certify that the work submitted with this assignment is mine and was generated in a manner
consistent with this document, the course academic policy on the course website on Blackboard,
and the UMass Lowell academic code.
Date:11/6/2022
Name:Daniel Bergeron
*/


#include "Bridges.h"
#include "DataSource.h"
#include "Array.h"
#include "SLelement.h"
#include <vector>
#include <map>

using namespace bridges;
using namespace std;

//
//  This program illustrates how to access a small subset of the IMDB actor movie data
//  set (a list of actor movie pairs and build a linked list and visualize it.
//
const int NUM_OF_RECORDS = 1814;

int main(int argc, char* argv[]) {

  //create the Bridges object, set credentials
    Bridges bridges (12, "danBergeron3", "846950238470");
    bridges.setTitle("List IMDB");

  // TODO:  access teh IMDB dataset - create a  data source object
  // and use its getActorMovieIMDBData() method
  // this will return a vector of actor-movie objects of type
  // ActorMovieIMDB - refer to the docs for that object and its attributes
    DataSource ActorData;
    vector<ActorMovieIMDB> actorVector = ActorData.getActorMovieIMDBData(1814);
    map<string, int> actorMap;
    map<string, int>::iterator p;
    for(int i = 0; i < actorVector.size(); i++){
      p = actorMap.find((actorVector[i]).getActor());
        if(p == actorMap.end()){
            actorMap.insert({(actorVector[i]).getActor(), 1});
        } else {
            int temp = (*p).second;
            temp++;
            (*p).second = temp;
        }
    }
    
  // TODO: build a linked list, using singly linked list elements, SLelement<ActorMovieIMDB>
  // where the actormovie object is a generic parameter that
  
  // iterate through the vector and put each of the actor movie names into the label
  // field of the SLelement (using the setLabel() method of the element) -
  // this will show up in the visualization when you do a moouse over the node
  // mark the first node of the list by changing its color (use the setColor()
  // method) SLelement (const E &val=E(), const string &lab=string())
  string newLabel;
  SLelement<int> *head = nullptr, *node = nullptr;
  int largest = 0;
  
  for(p = actorMap.begin(); p != actorMap.end(); p++){
    SLelement<int> *temp = new SLelement<int>((*p).second);
    newLabel = (*p).first + "(" + to_string((*p).second) + ")";
    temp->setLabel(newLabel);
    temp->setNext(head);
    head = temp;
    if((*p).second == 50){
      head->setColor("red");
      head->setSize(50.);
      head->setShape(SQUARE);
    }
    if(largest < (*p).second){
      largest = (*p).second;
      node = head;
    }
  }
  head->setColor("red");
  node->setColor("red");
  node->setSize(50.);
  node->setShape(DIAMOND);
  // tell Bridges what data structure to visualize
  bridges.setDataStructure(head);

  // visualize the list
  bridges.visualize();

  //TODO: remember to free the list as you have created dynamic memory
  SLelement<int> *previous = nullptr;
  while(head != nullptr){
    previous = head;
    head = head->getNext();
    delete previous;
  }
  return 0;
}