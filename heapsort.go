/*
	heapsort.go
	Isaac Hernandez
	May 18, 2014


	I had never programmed in Go before so I needed to do a bit of research.
	Below are my sources:
	http://golang.org/doc/
	http://stackoverflow.com/questions/8757389/reading-file-line-by-line-in-go
	https://gobyexample.com/
*/

package main

import (
	"os"
	"bufio"
	"log"
)

func check(e error) {
	// Function to check for errors.
	if e != nil {
		panic(e)
	}
}

type MinHeap struct {
	/*
		MinHeap is a heap struct. The struct is essentially a complete binary tree with
		one rule: the value of a node must always be less than or eqaul to the values
		of its childrens' nodes. This MinHeap is implemented by nodes that keep track
		of its left and right children, as well as its parent (for heapifyUp). 
	*/
	val string
	inited bool
	nodesInHeap int

	parent *MinHeap
	left *MinHeap
	right *MinHeap
}

func (h *MinHeap) leftOrRight(n int) bool {
	/* 
		leftOrRight is an essential method in this MinHeap struct.
    	What it does is: it takes the number of total children the 
    	current node has, and it calculates the next move on the 
    	path to traverse down the heap tree in order to get to the 
    	next (for insert) or the current (for remove) final child node. 
	*/
	if n < 2 {
		return true
	} else {
		twos := 2
		for n >= twos {
			twos *= 2
		}
		if n < (twos-((twos - (twos/2))/2)) {
			return true
		} else {
			return false
		}
	}
}
func (h *MinHeap) compareASCIIStrings(a string, b string) bool {
	// helper function to compare two strings, char by char
	// does not have to be a method for the MinHeap class 
	for  i := 0; i < len(a); i++ {
		if a[i] < b[i] {
			return false
		} else if a[i] > b[i] {
			return true
		}
	}
	return false
}
// methods to return some variables
func (h *MinHeap) getVal() string {
	return h.val
}
func (h *MinHeap) getSize() int {
	return h.nodesInHeap
}
func (h *MinHeap) getParent() *MinHeap {
	return h.parent
}
func (h *MinHeap) getLeft() *MinHeap {
	return h.left
}
func (h *MinHeap) getRight() *MinHeap {
	return h.right
}
// method to set the val and "initialize" the node
func (h *MinHeap) setVal(s string) {
	h.val = s
	h.inited = true
}
func (h* MinHeap) heapifyUp() {
	/*
		heapifyUp is a helper function for insert. Once a value
		is inserted at the bottom most node, heapifyUp moves the
		value in the node up the tree by swapping its value
		with any parents' value that (in this case, because 
		it is MinHeap) are greater than the recently inserted value.
	*/
	if h.parent == nil {
		return 
	}
	if h.compareASCIIStrings(h.parent.val, h.val){
		temp := h.parent.val
		h.parent.val = h.val
		h.val = temp
		h.parent.heapifyUp()
	}
}
func (h* MinHeap) heapifyDown() {
	/* 
		heapifyDown is a helper function for remove. It takes the 
		value at the root and recursively swaps it down with one of 
		its childrens' values if its child's value is less.
	*/
	if h.left == nil && h.right == nil {
		return
	} else if h.right == nil {
		if h.compareASCIIStrings(h.val, h.left.val) {
			temp := h.val
			h.val = h.left.val
			h.left.val = temp
			h.left.heapifyDown()
		}
	} else if !h.compareASCIIStrings(h.left.val, h.right.val) {
		if h.compareASCIIStrings(h.val, h.left.val) {
			temp := h.val
			h.val = h.left.val
			h.left.val = temp
			h.left.heapifyDown()
		}
	} else if h.compareASCIIStrings(h.left.val, h.right.val) {
		if h.compareASCIIStrings(h.val, h.right.val) {
			temp := h.val
			h.val = h.right.val
			h.right.val = temp
			h.right.heapifyDown()
		}
	}

}
func (h* MinHeap) getBottom() string {
	/* 
		Using leftOrRight, this method gets to the bottom (the
	   	most recently added node. This method is a helper function
	    for remove. 
	*/
	if h.left == nil && h.right == nil{
		h.nodesInHeap--
		return h.val
	}
	if h.leftOrRight(h.nodesInHeap) {
		if h.left.getLeft()==nil && h.left.getRight()==nil{
			r := h.left.val
			h.left = nil
			h.nodesInHeap--
			return r
		} else {
			h.nodesInHeap--
			return h.left.getBottom()
		}
	} else {
		if h.right.getLeft()==nil && h.right.getRight()==nil{
			r := h.right.val
			h.right = nil
			h.nodesInHeap--
			return r
		} else {
			h.nodesInHeap--
			return h.right.getBottom()
		}
	}
}
func (h *MinHeap) insert(s string) {
	/* 
		This function is one of the two primary functions for 
		implementing the MinHeap. Insert takes a string and traverses 
		all the way down to the next null node on the heap tree. It 
		then inserts the value given as a paremeter and calls heapifyUp
		to sort the current tree appropriately.
	*/
	h.nodesInHeap++
	if !h.inited {
		h.setVal(s)
	} else if h.leftOrRight(h.nodesInHeap) {
		if h.left == nil {
			temp := NewMinHeap()
			h.left = &temp
			h.left.parent = h
			h.left.insert(s)
			h.left.heapifyUp()
		} else {
			h.left.insert(s)
		}
	} else {
		if h.right == nil {
			temp := NewMinHeap()
			h.right = &temp
			h.right.parent = h
			h.right.insert(s)
			h.right.heapifyUp()
		} else {
			h.right.insert(s)
		}
	}
}
func (h *MinHeap) remove() {
	/*
		This function is the other primary function for implementing
		this MinHeap. Remove deletes teh bottom most node and places its
		value in the root, essentially removing the root value. It then
		calls heapifyDown to appropriately sort the heap.
	*/
	h.val = h.getBottom()
	h.heapifyDown()
}
func NewMinHeap() MinHeap {
	mH := MinHeap{inited: false, nodesInHeap: 0}
	return mH
}

func main() {
	// open file from command line
	fileName :=  os.Args[1]
	file, e := os.Open(fileName)
	check(e)

	// creat a heap
	myHeap := NewMinHeap()
	// create a scanner to read line by line
	scanner := bufio.NewScanner(file)
	// read ine by line and insert each line into heap
	for scanner.Scan() {
		myHeap.insert(scanner.Text())
	}
	if err := scanner.Err(); err != nil {
    	log.Fatal(err)
	}

	// create output
	out, e2 := os.Create("goOutputHeap")
	check(e2)
	// place the root in the output and remove the root
	// the file will then have all values in order
	for myHeap.nodesInHeap > 0 {
	    out.WriteString(myHeap.val)
		out.WriteString("\n")
		myHeap.remove()
	}

	// close files
	out.Close()
	file.Close()

}