/* 
	heapsort.cc
	Isaac Hernandez
	May 18, 2014

	heapsort.cc takes in a file and and takes in each line
	as a string and places al lines in a heap. The heap sorts
	all strings. Then the program outputs the root of the heap
	and removes the root until there are no more nodes in the
	heap left. The output should have all of the ASCII records
	from the input in order.
*/

#include <fstream>
#include "MinHeap.h"
using namespace std;

int main(int argc, char* argv[]){

	// don't forget to add usage stuff!!!!

	// open input file from command line
	ifstream in(argv[1]);
	//initialize string to hold each line
	string line;
	// initialize heap
	MinHeap myHeap;

	// insert each ASCII string nto the heap
	if(in){
		while(getline(in, line))
			myHeap.insert(line);
	}
	
	// create the output file
	ofstream out("output");
	// write each ASCII string (in order) into the output, and then remove string from heap
	while(myHeap.getSize() > 0){
		out << myHeap.getVal() << endl;
		myHeap.remove();
	}
	
	// close files
	in.close();
	out.close();

}