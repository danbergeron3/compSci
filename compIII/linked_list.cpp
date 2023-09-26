
/***********************************************
Author: Daniel Bergeron
Date: 9/25/2022
Time Spent: 4hr
COMP	2010 Lecture	09	– LinkedList	Class Exercise
2
What learned: Came up with a strategy on how to implement linked lists in c++
also learned how to use the new function in c++
***********************************************/
/*
Computing III -- COMP.2010 Honor Statement
The practice of good ethical behavior is essential for
maintaining good order in the classroom, providing an enriching
learning experience for students, and as training as a practicing
computing professional upon graduation. This practice is
manifested in the University’s Academic Integrity policy.
Students are expected to strictly avoid academic dishonesty and
adhere to the Academic Integrity policy as outlined in the course
catalog. Violations will be dealt with as outlined therein.
All programming assignments in this class are to be done by the
student alone. No outside help is permitted except the
instructor and approved tutors.
I certify that the work submitted with this assignment is mine
and was generated in a manner consistent with this document, the
course academic policy on the course website on Blackboard, and
the UMass Lowell academic code.
Date:9/25/2022
Name: Daniel Bergeron
*/
#include <iostream>
#include <new>
using namespace std;

class Node {
public:
	//constructors
	Node();
	Node(int idata);
	Node(int idata, Node* inext);

	//accessor
	Node* get_node_next(void);
	int get_node_data(void) const;

	//mutators
	void set_node_data(int idata);
	void set_node_next(Node* inext);

private:
	int data;
	Node* next;
};


class LinkedList {
public:
	//constructors
	LinkedList();
	LinkedList(Node* iNode);
	LinkedList(const LinkedList& orglist);
	LinkedList(const int arr[], int size);
	//accessors
	Node* get_head(void) const;

	//mutators
	void set_head(Node* inNode);
	
	//adds a copy off the past node to the head and moves head back
	void head_insert(Node &ihead);
	//outputs entire linked list
	void display_list(void) const;
	//appends the input list to the back of current list
	void append(Node* newHead);
	//appends the input list to the front of the second
	void preAppend(Node* inNode);
private:
	Node* head;
};
int main(int argc, char* argv[])
{
	Node node1(3);
	Node node2(69);
	Node node3(59);
	Node node4(100);
	
	LinkedList list1;
	cout << list1.get_head() << endl;
	list1.head_insert(node1);
	int arr[] = { 1,2,3,4,5,6 };
	list1.head_insert(node1);
	cout << list1.get_head() << endl;
	LinkedList list2(arr, 6);
	list1.display_list();
	list1.append(&node2);
	list1.display_list();
	list1.append(&node1);
	list1.append(&node3);
	list1.display_list();

	LinkedList list3(&node2);
	list3.display_list();

	//now something fancy
	int arr2[] = { -6, -5, -4, -3, -2, -1, 0 };
	LinkedList list4(arr2, 7);
	list2.display_list();
	list1.preAppend(list2.get_head());
	list1.display_list();
	
	list1.append(&node4);
	list1.display_list();

	cout << "\n\n\n\n------------------------------\n\n\n\n";

	LinkedList arrlist(arr2, 7);
	LinkedList copylist(arrlist);
	arrlist.display_list();
	copylist.display_list();


	return 0; 
}
LinkedList::LinkedList()
{
	head = nullptr;
}
LinkedList::LinkedList(Node* inputNode)
{

	Node* newNode = new Node;
	newNode->set_node_data(inputNode->get_node_data());
	newNode->set_node_next(inputNode->get_node_next());
	head = newNode;
}

void LinkedList::head_insert(Node &iNode)
{
	Node* newNode = new Node;
	newNode->set_node_data(iNode.get_node_data());
	newNode->set_node_next(head);
	head = newNode;
}

Node* LinkedList::get_head(void) const
{
	return head;
}

LinkedList::LinkedList(const int arr[], int size)
{
	for (int i = size-1; i >= 0; i--)
	{
		Node* newNode = new Node;
		newNode->set_node_data(arr[i]);
		newNode->set_node_next(nullptr);
		head_insert(*newNode);
	}
}
Node::Node()
{
	data = 0;
	next = nullptr;
}
Node::Node(int idata)
{
	data = idata;
	next = nullptr;
}

Node::Node(int idata, Node* inext)
{
	data = idata;
	next = inext;
}

Node* Node::get_node_next(void)
{
	return next;
}

int Node::get_node_data(void) const
{
	return data;
}

void Node::set_node_data(int idata)
{
	data = idata;
}

void Node::set_node_next(Node* inext)
{
	next = inext;
}

void LinkedList::display_list(void) const 
{
	Node* temp = head;
	while (temp != nullptr)
	{
		cout << temp->get_node_data() << ", ";
		temp = temp->get_node_next();
	}

	cout << endl;
}

void LinkedList::append(Node* inNode)
{
	/*Node* newNode = new Node;
	newNode->set_node_data(inNode->get_node_data());
	newNode->set_node_next(inNode->get_node_next());*/
	
	Node* temp = head;
	while (temp->get_node_next() != nullptr)
	{
		temp = temp->get_node_next();
	}

	temp->set_node_next(inNode);
}

void LinkedList::set_head(Node* inNode)
{
	head = inNode;
}

void LinkedList::preAppend(Node* inNode)
{
	Node* temp = inNode;
	while (temp->get_node_next() != nullptr)
	{
		temp = temp->get_node_next();
	}

	temp->set_node_next(head);
	head = inNode;
}

LinkedList::LinkedList(const LinkedList& orgList)
{
	//make first node
	//make second nod
	//first next = secod
	Node* temp = orgList.get_head();
	Node* previous = nullptr;
	while (temp != nullptr)
	{
		Node* newNode = new Node;
		newNode->set_node_next(nullptr);
		newNode->set_node_data(temp->get_node_data());
		if (previous != nullptr) 
		{
			previous->set_node_next(newNode);
		}
		else
		{
			head = newNode;
		}
		previous = newNode;
		temp = temp->get_node_next();

	}

}