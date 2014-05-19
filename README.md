heapsort
========
Heap sort in both C++ and in Go. Download the entire contents of this repository for the
following instructions to work.

***NOTE*** 
I run my commands on a Windows command line. Commands may differ based on OS.


heapsort.cc
-----------
heapsort.cc is heap sort implemented in C++. In order to build it, I have included a Makefile.
With a GNU C++ compilaer, if you enter the "make" command on the command line, it will build 
the ccHeapsort executable. Then you can use gensort to create records. ccHeapsort will then sort
the records. And valsort will evaluate if the sorting was correct. In other words, these commands
will allow you to test out my heapsort.cc:

> make
This command will compile the program.

> gensort -a 50000 sortThis
This command will create the records for sorting. The -a is necessary to create ASCII records. The
50000 is necessary for it to be near 5MB, but up to 100000 would also be appropriate (a little under
10MB). 

> ccHeapsort sortThis
This command will take sortThis, put all the records in a heap and then output a file, named "output",  
with all the records in order (by ASCII values).

> valsort output
This command will evaluate whether the sorting was done correctly.


heapsort.go
-----------
heapsort.go is heap sort implemented in Go. In order to build it, you must have the Go compiler and 
enter the following command:
> go build heapsort.go
You should now have the heapsort executable.

***NOTE***
I ran into an issue with the output coming from any form of write that Go offered. valsort was not
able to evaluate any output coming from my Go programs. The oddest thing though, is that all of the
output is actually correct. When I pass it through the executable of my writeAgain.cc, which is a
program that literally reads a file and writes a copy of it, the copy is evaluated just fine with
valsort, and it is also proves that heapsort.go correctly sorts. So... I will give instructions on
how to test both the output of my Go program, but also how to write a copy of it, and test it again.

These are the commands to test out my heapsort.go:

> go build heapsort.go
This command will compile the program.

> gensort -a 50000 sortThis
This command will create the records for sorting. The -a is necessary to create ASCII records. The
50000 is necessary for it to be near 5MB, but up to 100000 would also be appropriate (a little under
10MB).

> heapsort sortThis
This command will take sortThis, put all the records in a heap and then output a file, named "goOutput",  
with all the records in order (by ASCII values).

> valsort goOutput
This command will evaluate whether the sorting was done correctly. In my experience, this will always say
it was not sorted correctly. There is some oddity when valsort reads a result from a Go program though.
Of course I take full responsibility for not being able to discover the reason, but I was able to prove
that my heapsort.go does sort correctly with the following commands.

> g++ writeAgain.cc
This will compile writeAgain.cc and make an executable "a", that will write a copy of a file.

> a goOutput
This will take goOutput and write a copy, "goOutput2".

> valsort goOutput2
This will evaluate whether the sorting was done correctly and prove that heapsort.go does indeed sort correctly.