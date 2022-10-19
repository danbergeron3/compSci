#undef debug

#include <iostream>
#include <string>

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
	
private:
	T _data;
    BSTNode<T>* _left;
    BSTNode<T>* _right;
	
	// private "helper" functions
    void addLeft(const T& data) { _left = new BSTNode(data); }
	void addRight(const T& data) { _right = new BSTNode(data); }
};


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

	cout << "given output: \n";
	cout << "iroot == " << iroot << endl;
	cout << "sroot == " << sroot << endl;
	
	cout << "preOrderDisplay: \n";
	cout << "iroot == ";
	iroot.preOrderDisplay(cout);
	cout << endl;
	cout << "sroot == ";
	sroot.preOrderDisplay(cout);
	cout << endl;

	cout << "postOrderDisplay: \n";
	cout << "iroot == ";
	iroot.postOrderDisplay(cout);
	cout << endl;
	cout << "sroot == ";
	sroot.postOrderDisplay(cout);
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
