#undef debug

#include <iostream>
#include <string>
#include <list>
#include <map>
using namespace std;


template<typename T>
class BSTNode {
public:
	// Constructors, etc.
	BSTNode() : _data(0), _left(nullptr), _right(nullptr) {} // default constructor
    BSTNode(T data) : _left(nullptr), _right(nullptr) { _data = data; } // value constructor
	BSTNode(BSTNode&); // copy constructor
    ~BSTNode(); // destructor
	BSTNode& operator= (BSTNode&); // copy assignment operator
	
	// ***** Your group will define/implement the insert function
	// ***** at about line 89 below...
	void insert(const T& data);
	
	// Accessor and mutator functions
    BSTNode<T>* getLeft() const { return _left; }
	BSTNode<T>* getRight() const { return _right; }
	T& getData() const { return _data; }
	void setData(const T& data) { _data = data; }

	// Display functions used by operator<<.
	// ***** Your group will define/implement the pre & post display functions
	// ***** at about lines 114 & 127 below...
	void inOrderDisplay(ostream&) const;
	void preOrderDisplay(ostream&) const;
	void postOrderDisplay(ostream&) const;
	
	// The insertion operator below uses in-order display.
	// ***** Change the implementation of this insertion operator
	// ***** in order to switch to pre- or post-order display
	friend ostream& operator<< (ostream& out, const BSTNode<T>& b)
		{ b.inOrderDisplay(out); return out; }

    //other
    void listify(list<T>&) const;
	
private:
	T _data;
    BSTNode<T>* _left;
    BSTNode<T>* _right;
	
	// private "helper" functions
    void addLeft(const T& data) { _left = new BSTNode(data); }
	void addRight(const T& data) { _right = new BSTNode(data); }
};

//The result of the listify member function invocation is to perform an in-order traversal
//of the BST iroot, inserting the data of each BST node into the list irootList in the proper order
template<typename T>
void BSTNode<T>::listify(list<T>& newList) const{
    if (_left != nullptr) {
	    _left->listify(newList);
	}
	newList.push_back(_data);
	if (_right != nullptr) {
	    _right->listify(newList);
	}
    return;
}

template<typename T>
BSTNode<T>::BSTNode(BSTNode& b) {
#ifdef debug
	cout << "BSTNode copy constructor called, _data == " << _data << endl;
#endif
	_data = b._data;
	_left = _right = nullptr;
	if (b._left != nullptr) _left = new BSTNode<T>(*b._left);
	if (b._right != nullptr) _right = new BSTNode<T>(*b._right);
}


template<typename T>
BSTNode<T>::~BSTNode() {
#ifdef debug
	cout << "BSTNode destructor called, _data == " << _data << endl;
#endif
    delete _left;
	delete _right;
}


template<typename T>
BSTNode<T>& BSTNode<T>::operator= (BSTNode& b) {
#ifdef debug
	cout << "BSTNode copy assignment operator: ";
#endif
	_data = b._data;
	_left = _right = nullptr;
	if (b._left != nullptr) _left = new BSTNode<T>(*b._left);
    if (b._right != nullptr) _right = new BSTNode<T>(*b._right);
	return *this;
}


template<typename T>
void BSTNode<T>::insert(const T& data) {
	// comment out the next line when you've completed this function!
	//cout << "BSTNode<T>::insert called with data == " << data << endl;

	//compare data with _data if greater go right
	//else go left
	//repeat at new node until come across a nullptr
	//create and sign ptr
	if(data <_data){
		if(_left == nullptr){
			addLeft(data);
		} else {
			_left->insert(data);
		}
	} else if(data > _data){
		if(_right == nullptr){
			addRight(data);
		} else {
			_right->insert(data);
		}
	}
}


template<typename T>
void BSTNode<T>::inOrderDisplay(ostream& out) const {
	if (_left != nullptr) {
	    _left->inOrderDisplay(out);
	    out << ", ";
	}
	out << _data;
	if (_right != nullptr) {
	    out << ", ";
	    _right->inOrderDisplay(out);
	}
}

template<typename T>
void BSTNode<T>::preOrderDisplay(ostream& out) const {
	// comment out the next line when you've completed this function!
	//cout << "BSTNode<T>::preOrderDisplay called\n";
	//recursion set up:
	//vist root

	out << _data;
	//vist left
	if(_left != nullptr){
		out << ", ";
		_left->preOrderDisplay(out);
	}
	//if left is null visit the right
	//vist right 
	if(_right != nullptr){
		out << ", ";
		_right->preOrderDisplay(out);
	}
	return;
}

template<typename T>
void BSTNode<T>::postOrderDisplay(ostream& out) const {
	// comment out the next line when you've completed this function!
	//cout << "BSTNode<T>::postOrderDisplay called\n";
	
	//recursion setup
	//go left
	if(_left != nullptr){
		_left->postOrderDisplay(cout);
		cout << ", ";
	}
	//go right
	if(_right != nullptr){
		_right->postOrderDisplay(cout);
		cout << ", ";
	}
	//get data
	cout << _data;
	return;
}


int main(void) {
	BSTNode<int> iroot(100);
	iroot.insert(10);
	iroot.insert(20);
	iroot.insert(200);
	iroot.insert(300);
	

	

	BSTNode<string> sroot("Sunday");
	sroot.insert("Monday");
	sroot.insert("Tuesday");
	sroot.insert("Wednesday");
	sroot.insert("Thursday");
	sroot.insert("Friday");
	sroot.insert("Saturday");

	cout << "Given output: \n";
	cout << "iroot == " << iroot << endl;
	cout << "sroot == " << sroot << endl;
    cout << "\nCreating irootList via iroot.listify\n\n";
    list<int> irootList;
    iroot.listify(irootList);

    cout << "irootList (forward iterator) == ";
    //iterations
    list<int>::iterator p = irootList.begin();
    for(; p != irootList.end(); p++){
        cout << *p << " ";
    }
    cout << endl;
    cout << "irootList (reverse iterator) == ";
    for(p = irootList.end(); p != irootList.begin(); ){
        cout << *(--p) << " ";
    }
    cout << endl;
    cout << "irootList (ranged for loop) == ";
    for(int eachElement:irootList){
        cout << eachElement << " "; 
    }
    cout << endl;
    /// 
    /// 
    cout << "\nCreating srootList via sroot.listify\n\n";
    list<string> srootList;
    sroot.listify(srootList);
    list<string>::iterator s = srootList.begin();
    cout << "srootList (forward iterator) == ";
    for(; s != srootList.end(); s++){
        cout << *s << " ";
    }
    cout << endl;
    cout << "srootList (reverse iterator) == ";
    for(s = srootList.end(); s != srootList.begin(); ){
        cout << *(--s) << " ";
    }
    cout << endl;
    cout << "srootList (ranged for loop) == ";
    for(string eachString:srootList){
        cout << eachString << " "; 
    }
    cout << endl;
    //Create BSTNode<int> iroot4 containing the items 1000, 2000, 3000, 4000, and 5000;
    //5. Create iroot4List from iroot4;
    BSTNode<int> iroot4(1000);
    iroot4.insert(2000);
    iroot4.insert(3000);
    iroot4.insert(4000);
    iroot4.insert(5000);
    list<int> iroot4List;
    iroot4.listify(iroot4List);
    cout << "iroot4List (ranged for loop) == ";
    for(int eachElement:iroot4List){
        cout << eachElement << " "; 
    }
    cout << endl;
    cout << "\nCreating iroot4List via iroot4.listify\n" << endl;
    cout << "Contents of map<string, list<int>> mi (using ranged for loops):\n";
    //Create a map instance mi with string as the “first” element type and list<int> as the
    //“second” element type, i.e., map<string, list<int>> mi;
	map<string, list<int>> mi;
    //Assign two elements of mi as in the sample output below
    cout << "Contents of map<string, list<int>> mi (using ranged for loops):\n";
    mi["iroot4List"] = iroot4List;
    mi["irootList"] = irootList;
    for(auto & each:mi){
        cout << each.first << " == ";
        for(auto eachitem:each.second){
            cout << eachitem << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "\nUsing map index operator:\n";
    cout << "mi[\"iroot4List\"] == ";
    list<int>::iterator l = mi["iroot4List"].begin();
    for(; l !=mi["iroot4List"].end(); l++){
        cout << *l << " ";
    }
    cout << endl;
    cout << "mi[\"irootList\"] == "; 
    l = mi["irootList"].begin();
    for(; l !=mi["irootList"].end(); l++){
        cout << *l << " ";
    }
    cout << endl;
#ifdef debug	
	BSTNode<int> iroot2(iroot); // use copy constructor
	cout << "\nAfter copy constructor:\n";
	cout << "iroot2 == " << iroot2 << endl;
	
	BSTNode<int> iroot3;
	iroot3 = iroot2; // use copy assignment operator
	cout << "\nAfter copy assignment operator:\n";
	cout << "iroot3 == " << iroot3 << endl << endl;
#endif
	
	return 0;
}
