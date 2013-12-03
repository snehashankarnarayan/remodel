#include "headers.h"

void printOutput()
{
    for(int i=0; i<depList.size(); i++)
    {
        cout<<"Target "<<depList[i].target<<"Depth "<<depList[i].depth
        <<"isResolved "<<depList[i].isResolved
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
