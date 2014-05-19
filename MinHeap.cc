/*
	MinHeap.cc
	Isaac Hernandez
	May 17, 2014

	This file contains all of the methods for the MinHeap struct.
*/

#include "MinHeap.h"
using namespace std;

bool compareASCIIStrings(string a, string b){
	// helper function to compare two strings, char by char
	// does not have to be a method for the MinHeap class 
	for(int i=0; i<a.length(); i++){
		if(a[i] < b[i])
			return false;
		else if(a[i] > b[i])
			return true;
	}
	return false;
}

bool MinHeap::leftOrRight(int n){
	/* 
		leftOrRight is an essential method in this MinHeap struct.
    	What it does is: it takes the number of total children the 
    	current node has, and it calculates the next move on the 
    	path to traverse down the heap tree in order to get to the 
    	next (for insert) or the current (for remove) final child node. 
	*/
	if(n < 2)
		return true;
	else {
		int twos = 2;
		while(n >= twos)
			twos *= 2;
		if( n < (twos-((twos - (twos/2))/2)) )
			return true;
		else 
			return false;
	}
}

string MinHeap::getBottom(){
	/* 
		Using leftOrRight, this method gets to the bottom (the
	   	most recently added node. This method is a helper function
	    for remove. 
	*/
	if(!left && !right){
		nodesInHeap--;
		return val;
	}
	if(leftOrRight(nodesInHeap)){
		if(!(left->getLeft()) && !(left->getRight())){
			string r = left->getVal();
			left = NULL;
			nodesInHeap--;
			return r;
		}
		else{
			nodesInHeap--;
			return left->getBottom();
		}
	}
	else{
		if(!(right->getLeft()) && !(right->getRight())){
			string r = right->getVal();
			right = NULL;
			nodesInHeap--;
			return r;
		}
		else{
			nodesInHeap--;
			return right->getBottom();
		}
	}
}

void MinHeap::heapifyUp(){
	/*
		heapifyUp is a helper function for insert. Once a value
		is inserted at the bottom most node, heapifyUp moves the
		value in the node up the tree by swapping its value
		with any parents' value that (in this case, because 
		it is MinHeap) are greater than the recently inserted value.
	*/
	if(!parent)
		return;
	if(compareASCIIStrings(parent->getVal(), val)){
		string temp = parent->getVal();
		parent->setVal(val);
		setVal(temp);
		parent->heapifyUp();
	}
}

void MinHeap::heapifyDown(){
	/* 
		heapifyDown is a helper function for remove. It takes the 
		value at the root and recursively swaps it down with one of 
		its childrens' values if its child's value is less.
	*/
	if(!left && !right){
		return;
	}
	// maybe combine the following two else ifs?
	else if(!right){
		if(compareASCIIStrings(val, left->getVal())) {
			string temp = val;
			val = left->getVal();
			left->setVal(temp);
			left->heapifyDown();
		}
	}
	else if(!compareASCIIStrings(left->getVal(), right->getVal())) {
		if(compareASCIIStrings(val, left->getVal())) {
			string temp = val;
			val = left->getVal();
			left->setVal(temp);
			left->heapifyDown();
		}
	}
	else if(compareASCIIStrings(left->getVal(), right->getVal())) {
		if(compareASCIIStrings(val, right->getVal())) {
			string temp = val;
			val = right->getVal();
			right->setVal(temp);
			right->heapifyDown();
		}
	}
}

// methods to return some private variables
string MinHeap::getVal(){return val;}
int MinHeap::getSize(){return nodesInHeap;}
MinHeap* MinHeap::getParent(){return parent;}
MinHeap* MinHeap::getLeft(){return left;}
MinHeap* MinHeap::getRight(){return right;}

// methods to set some private variables
void MinHeap::setVal(string s){val = s; inited = true;}
void MinHeap::setParent(MinHeap* const mh){parent = mh;}

void MinHeap::insert(string s){
	/* 
		This function is one of the two primary functions for 
		implementing the MinHeap. Insert takes a string and traverses 
		all the way down to the next null node on the heap tree. It 
		then inserts the value given as a paremeter and calls heapifyUp
		to sort the current tree appropriately.
	*/
	nodesInHeap++;
	if(!inited)
		setVal(s);
	else if(leftOrRight(nodesInHeap)){
		if(!left){
			left = new MinHeap;
			left->setParent(this);
			left->insert(s);
			left->heapifyUp();
		}
		else
			left->insert(s);
	}
	else{
		if(!right){
			right = new MinHeap;
			right->setParent(this);
			right->insert(s);
			right->heapifyUp();
		}
		else
			right->insert(s);
	}
}

void MinHeap::remove(){
	/*
		This function is the other primary function for implementing
		this MinHeap. Remove deletes teh bottom most node and places its
		value in the root, essentially removing the root value. It then
		calls heapifyDown to appropriately sort the heap.
	*/
	val = getBottom();
	heapifyDown();
}
