all: remodel
remodel: UtilFunctions.o printFunctions.o parseInput.o nodeFunctions.o remodel.o
	g++ -g UtilFunctions.o printFunctions.o parseInput.o nodeFunctions.o remodel.o  -o remodel
UtilFunctions.o: UtilFunctions.cpp
	g++ -g -c UtilFunctions.cpp -lssl -lcrypto
printFunctions.o: printFunctions.cpp
	g++ -g -c printFunctions.cpp -o printFunctions.o
parseInput.o: parseInput.cpp
	g++ -g -c parseInput.cpp -o parseInput.o 
nodeFunctions.o: nodeFunctions.cpp
	g++ -g -c nodeFunctions.cpp -o nodeFunctions.o 
remodel.o: remodel.cpp
	g++ -g -c remodel.cpp -o remodel.o
