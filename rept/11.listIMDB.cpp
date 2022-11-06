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



#include "Bridges.h"
#include "DataSource.h"
#include "Array.h"
#include "SLelement.h"
#include <vector>
#include <list>

using namespace bridges;
using namespace std;

//
//  This program illustrates how to access a small subset of the IMDB actor movie data
//  set (a list of actor movie pairs and build a linked list and visualize it.
//
const int NUM_OF_RECORDS = 1814;

int main(int argc, char* argv[]) {

  //create the Bridges object, set credentials
    Bridges bridges (11, "danBergeron3", "846950238470");
    bridges.setTitle("List IMDB");

  // TODO:  access teh IMDB dataset - create a  data source object
  // and use its getActorMovieIMDBData() method
  // this will return a vector of actor-movie objects of type
  // ActorMovieIMDB - refer to the docs for that object and its attributes
    DataSource ActorData;
    vector<ActorMovieIMDB> actorVector = ActorData.getActorMovieIMDBData(1814);
    
  // TODO: build a linked list, using singly linked list elements, SLelement<ActorMovieIMDB>
  // where the actormovie object is a generic parameter that
    
    string actor;
    string movie;
    string list_label;
    actor = (actorVector[0]).getActor();
    movie = (actorVector[0]).getMovie();
    list_label = actor + " - ";
    list_label += movie;
  // iterate through the vector and put each of the actor movie names into the label
  // field of the SLelement (using the setLabel() method of the element) -
  // this will show up in the visualization when you do a moouse over the node
  // mark the first node of the list by changing its color (use the setColor()
  // method) SLelement (const E &val=E(), const string &lab=string())
  
  SLelement<ActorMovieIMDB> *head = new SLelement<ActorMovieIMDB>(actorVector[0], list_label); 
  int i = 1;
  
  for(int i = 1; i < actorVector.size(); i++){
    actor = (actorVector[i]).getActor();
    movie = (actorVector[i]).getMovie();
    list_label = actor + " - ";
    list_label += movie;
    SLelement<ActorMovieIMDB> *temp = new SLelement<ActorMovieIMDB>(actorVector[i], list_label);
    temp->setNext(head);
    head = temp;
  }
  // tell Bridges what data structure to visualize
  head->setColor("red");
  bridges.setDataStructure(head);

  // visualize the list
  bridges.visualize();

  //TODO: remember to free the list as you have created dynamic memory
  SLelement<ActorMovieIMDB> *previous = nullptr;
  while(head != nullptr){
    previous = head;
    head = head->getNext();
    delete previous;
  }
  return 0;
}