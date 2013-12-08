//=======================================================================================
// This file contains all the output related functions. Used for debugging and testing
//=======================================================================================
#include "headers.h"

extern vector<dependencyNode> depList;
extern string rootTarget;
void printOutput()
{
    cout<<endl<<"output"<<endl;
    for(int i=0; i<depList.size(); i++)
    {
        cout<<"Target "<<depList[i].target<< "Depth "<<depList[i].depth
        <<" isResolved "<<depList[i].isResolved
        <<" isBuilt" <<depList[i].isBuilt
        <<endl;
    }
}

void printParsedOutput()
{
    for(int i=0; i<depList.size(); i++)
    {
        cout<<endl<<"New NODE"<<endl;
        cout<<"Target:"<<depList[i].target<<":"<<endl;
        cout<<"Command "<<depList[i].command<<endl;
        for(int j=0; j<depList[i].source.size(); j++)
        {
            cout<<"Dependency "<<depList[i].source[j]<<endl;
        }
    }
}
