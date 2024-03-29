//=======================================================================================
// This file contains all the modules required for parsing the input file.
//=======================================================================================
#include "headers.h"

extern vector<dependencyNode> depList;
extern string rootTarget;
void parseInputFile()
{
    fstream fp;
    string line;
    try
    {
        fp.open(MAKEFILE);
        while(getline(fp, line))
        {
            parseLine(line);
        }
    }
    catch(...)
    {
        cout<<"Input remodelFile read failed"<<endl;
        cout<<REMODEL_ABORT<<endl;
        exit(1);
    }
}

vector<string> parseAndFillDependencyList(string currentDependencies)
{
    size_t found;
    size_t prev = 0;
    vector<string> vList;
    found = currentDependencies.find(",");

    while(found != string::npos)
    {
        vList.push_back(currentDependencies.substr(prev, found - prev));
        prev = found+1;
        found = currentDependencies.find(",", prev);
    }

    /*Deal with last entry*/
    /*There is only one dependency. Eliminate command now*/
    found = currentDependencies.find_first_of(":");
    if(found == string::npos)
    {
        if(currentDependencies.size())
        {
            vList.push_back(currentDependencies);
        }
    }
    else
    {
        string str = currentDependencies.substr(prev, found - prev);
        str = removeWhiteSpace(str);
        if(str.size())
        {
            vList.push_back(str);
        }
    }

    /*Strip white chars*/
    for(int i=0; i<vList.size(); i++)
    {
        vList[i] = removeWhiteSpace(vList[i]);
    }
    return vList;
}

void parseLine(string line)
{
    size_t found;
    string target;
    string currentDependencies;
    vector<string> vList;
    string command;
    found  = line.find("<-");
    if(found != string::npos)
    {
        /* Copy the target and the dependencies */
        target = removeWhiteSpace(line.substr(0, found));
        currentDependencies = line.substr(found+2);

        vList = parseAndFillDependencyList(currentDependencies);

        /*Deal with the command*/
        found = currentDependencies.find("\"");
        if(found != string::npos)
        {
            command = currentDependencies.substr(found, currentDependencies.length() - found);
        }
    }
    if(target.length() != 0)
    {
        dependencyNode d;
        d = makeNode(false, target, vList, command);
        depList.push_back(d);
    }
}

