all: remodel
remodel: UtilFunctions.o printFunctions.o parseInput.o nodeFunctions.o md5Functions.o parallelize.o remodel.o
	g++ -g UtilFunctions.o printFunctions.o parseInput.o nodeFunctions.o remodel.o md5Functions.o parallelize.o -lssl -lcrypto -o remodel
UtilFunctions.o: UtilFunctions.cpp
	g++ -g -c UtilFunctions.cpp -lssl -lcrypto -o UtilFunctions.o
printFunctions.o: printFunctions.cpp
	g++ -g -c printFunctions.cpp -o printFunctions.o
parseInput.o: parseInput.cpp
	g++ -g -c parseInput.cpp -o parseInput.o 
nodeFunctions.o: nodeFunctions.cpp
	g++ -g -c nodeFunctions.cpp -o nodeFunctions.o
parallelize.o: parallelize.cpp 
	g++ -g -c parallelize.cpp -o parallelize.o
md5Functions.o: md5Functions.cpp
	g++ -g -c md5Functions.cpp -lssl -lcrypto -o md5Functions.o
remodel.o: remodel.cpp
	g++ -g -c remodel.cpp -o remodel.o
