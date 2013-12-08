#include "headers.h"

extern vector<dependencyNode> depList;
extern string rootTarget;

int main(int argc, char* argv[])
{
    /*Deal with makefile*/
    switch(argc)
    {
        case 2: /* Target specified*/
                rootTarget = argv[1];
                break;

        case 1: /*No specified target*/
                rootTarget = string(DEFAULT_TARGET);
                break;
    }

    /*Parse input file*/
    parseInputFile();
    /*Input file is parsed now. Resolve dependencies and figure out the order of execution*/
    buildLeafNodes();


    md5Hashing();
    resolveBuilds();

    determineOrderOfExec();
    /*Sort and print order of execution*/
    sortOrder();
    /*Execute code that is to be built*/
    runParallel();



   // printOutput();
   // printParsedOutput();
    return 0;

}
