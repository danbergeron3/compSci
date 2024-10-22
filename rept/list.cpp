#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Bridges.h"
#include "DataSource.h"
#include "data_src/ActorMovieIMDB.h"

using namespace bridges;

// This program fragment illustrates how to access and read the IMDB actor/movie data

//
// This tutorial creates a set of singly linked list elements, links them 
// and displays them
//
// Reference: SLelement, Bridges classes
//
int main (int argc, char **argv) {
	// create Bridges object
	Bridges bridges (1, "danBergeron3",
		"846950238470");
	// set title
	bridges.setTitle("A Singly Linked List Example");

	// set  description
	bridges.setDescription("A singly linked list of 4 nodes with names; the nodes in this example use string as the generic type");

	// create the linked list elements with student names
	SLelement<string>  *st0 = new SLelement<string> ("Gretel Chaney");
	SLelement<string>  *st1 = new SLelement<string> ("Lamont Kyler");
	SLelement<string>  *st2 = new SLelement<string> ("Gladys Serino");
	SLelement<string>  *st3 = new SLelement<string> ("Karol Soderman");
	SLelement<string>  *st4 = new SLelement<string> ("Starr McGinn");

	// we want to see these names in the visualization so we will set them as
	// the nodes' labels. We will retrieve the nodes' generic data for the label
	st0->setLabel(st0->getValue());
	st1->setLabel(st1->getValue());
	st2->setLabel(st2->getValue());
	st3->setLabel(st3->getValue());
	st4->setLabel(st4->getValue());

	//  link the elements into a list
	st0->setNext(st1);
	st1->setNext(st2);
	st2->setNext(st3);
	st3->setNext(st4);

	// tell Bridges the head of the list
	bridges.setDataStructure(st0);

	// visualize the linked list (hit the key 'l' on the visualzation to see all labels
	bridges.visualize();

	//cleanup
	delete st0;
	delete st1;
	delete st2;
	delete st3;
	delete st4;
}

  
