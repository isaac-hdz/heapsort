/*
	MinHeap.h
	Isaac Hernandez
	May 17, 2014

	MinHeap is a heap struct. The struct is essentially a complete binary tree with
	one rule: the value of a node must always be less than or eqaul to the values
	of its childrens' nodes. This MinHeap is implemented by nodes that keep track
	of its left and right children, as well as its parent (for heapifyUp). 
*/
#include <string>
using namespace std;

class MinHeap{

	// value at root of current heap
	string val;
	// boolean to keep track of whether the root has been initialized
	bool inited = false;
	// nodesInHeap is a value to keep track of all branches below the current node
	int nodesInHeap = 0; 	// it is used for leftOrRight

	// parent node, left and right children branches
	MinHeap* parent = 0;
	MinHeap* left = 0;
	MinHeap* right = 0;

	// private methdods, explained in MinHeap.cc
	bool leftOrRight(int n);
	string getBottom();
	void heapifyUp();
	void heapifyDown();

public:
	//public methods, explained in MinHeap.cc
	string getVal();
	int getSize();
	MinHeap* getParent();
	MinHeap* getLeft();
	MinHeap* getRight();
	void setVal(string s);
	void setParent(MinHeap* const mh);
	void insert(string s);
	void remove();

};