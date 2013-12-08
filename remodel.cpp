#include "headers.h"

extern vector<dependencyNode> depList;
extern string rootTarget;
void initialize()
{

}

void determineOrderOfExec()
{
    int iterationCount = 0;
    int maxDepth;

    while(allNotResolved())
    {
        for(int i=0; i<depList.size(); i++)
        {
            maxDepth = -1;
            if(!depList[i].isResolved)
            {
                /*Check if all the sources of the current node is resolved*/
                if(areAllSourcesResolved(i))
                {
                    depList[i].isResolved = true;
                    depList[i].depth = iterationCount;
                }
            }
        }

        ++iterationCount;
    }
}

int main(int argc, char* argv[])
{
    initialize();

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

    //printOutput();
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
