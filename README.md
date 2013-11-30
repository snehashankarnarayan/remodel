remodel
=======

Project requirements:
======================
For this individual project, you will write a replacement program for make called remodel. make takes a series of dependencies and builds targets by executing commands. Unfortunately, its use of UNIX timestamps as a happens-before relation means that it can fail to build properly. This is especially true during parallel builds.

Your program, remodel, will also take a series of dependencies and targets, etc. (grammar below), but unlike make, it will use MD5 hashes to detect new content and provide, together with the dependency chain, a happens-before relation (md5diff(oldA,newA) => everything that depends on A must be rebuilt). It must also execute all independent (non-conflicting) commands in parallel, using threads or processes.

remodel uses a different grammar than make. Dependencies can appear in any order. If you execute remodel with no arguments, it should start with the pseudo-target DEFAULT. Otherwise, the root is the argument to remodel, as in remodel foo.o.

program ::= production*
production ::= target '<-' dependency (':' '"' command '"")
dependency ::= filename (',' filename)*
target ::= filename (',' filename)*


Here's an example that builds the program baz from two source files, foo.cpp and bar.cpp.

DEFAULT <- baz
baz <- foo.o, bar.o: "g++ foo.o bar.o -o baz"
foo.o <- foo.cpp : "g++ -c foo.cpp -o foo.o"
bar.o <- bar.cpp: "g++ -c bar.cpp -o bar.o"


You should store the dependencies on disk in a special directory called .remodel/, so that remodel will not re-execute any commands unless a dependency has been violated.

You may write remodel in the language of your choice, as long as that language is statically compiled (i.e., no JVM languages). Examples of such languages include C, C++, and Haskell (via the GHC compiler). 

Project implementation:
=============================

Project is being implemented in C++. Specify the input in a file named 'makefile', if a specific target has to be built specify the target.
