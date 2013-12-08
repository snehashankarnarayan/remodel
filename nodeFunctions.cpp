#include "headers.h"

extern vector<dependencyNode> depList;
extern string rootTarget;

dependencyNode makeNode(bool isLeaf, string target, vector<string> vList = NULL, string command = "")
{
    dependencyNode d;
    d.target = target;
    d.source = vList;
    d.command = command;
    d.isResolved = isLeaf;
    d.depth = -1;
    d.isBuilt = false;
    d.builtCounter = 0;
    return d;
}

bool nodeExists(string nodeName)
{
    for(int i=0; i<depList.size(); i++)
    {
        if(depList[i].target == nodeName)
        {
            return true;
        }
    }
    return false;
}

void buildLeafNodes()
{
    for(int i=0; i<depList.size(); i++)
    {
        for(int j=0; j<depList[i].source.size(); j++)
        {
            if(!nodeExists(depList[i].source[j]))
            {
                /*This is stupid but debug this later and try to use makeNode()*/
                string nodeName = depList[i].source[j];
                dependencyNode d;
                d.target = nodeName;
                d.isResolved = true;
                d.depth = -1;
                depList.push_back(d);
            }
        }
    }
}

bool allNotResolved()
{
    for(int i=0; i<depList.size(); i++)
    {
        if(!depList[i].isResolved)
        {
            return true;
        }
    }
    return false;
}

bool sourceResolved(string source)
{
    for(int i=0; i<depList.size(); i++)
    {
        if(source == depList[i].target)
        {
            return depList[i].isResolved;
        }
    }
}

bool areAllSourcesResolved(int index)
{
    for(int i=0; i<depList[index].source.size(); i++)
    {
        if(!sourceResolved(depList[index].source[i]))
        {
            return false;
        }
    }

    /*All sources resolved*/
    return true;
}


//=======================================================
// BUILDING related code
//========================================================
void markTargetAsBuilt(string fileName)
{
    for(int i=0; i<depList.size();i++)
    {
        if(depList[i].target == fileName)
        {
            depList[i].isBuilt = true;
        }
    }
}

bool allNotBuilt()
{
    for(int i=0; i<depList.size(); i++)
    {
        if(!depList[i].isBuilt)
        {
            return true;
        }
    }
    return false;
}

bool sourceBuilt(string source)
{
    for(int i=0; i<depList.size(); i++)
    {
        if(source == depList[i].target)
        {
            return depList[i].isBuilt;
        }
    }
}

bool areAllSourcesBuilt(int index)
{
    for(int i=0; i<depList[index].source.size(); i++)
    {
        if(!sourceBuilt(depList[index].source[i]))
        {
            return false;
        }
    }

    /*All sources resolved*/
    return true;
}

void resolveBuilds()
{
   while(allNotBuilt())
    {
        for(int i=0; i<depList.size(); i++)
        {
            if(!depList[i].isBuilt)
            {
                /*Check if all the sources of the current node is resolved*/
                if(areAllSourcesBuilt(i))
                {
                    depList[i].isResolved = true;
                    depList[i].isBuilt = true;
                }
            }
        }
    }
}
