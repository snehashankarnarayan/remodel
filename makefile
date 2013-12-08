all: remodel
remodel: UtilFunctions.cpp printFunctions.cpp parseInput.cpp nodeFunctions.cpp md5Functions.cpp parallelize.cpp remodel.cpp
	g++ -fpermissive -g printFunctions.cpp parseInput.cpp nodeFunctions.cpp UtilFunctions.cpp remodel.cpp md5Functions.cpp parallelize.cpp -lssl -lcrypto -fopenmp -o remodel
