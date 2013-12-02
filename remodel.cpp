#include "headers.h"

dependencyNode makeNode(bool isLeaf, string target, vector<string> vList = NULL, string command = "")
{
    dependencyNode d;
    d.target = target;
    d.source = vList;
    d.command = command;
    d.isResolved = isLeaf;
    d.depth = -1;

    return d;
}

void computeMd5OfFile(char* fileName)
{
    unsigned char result[MD5_DIGEST_LENGTH];
    std::ifstream ifs(fileName);
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );

    MD5((unsigned char*) content.c_str(), content.size(), result);
}

void parseInputFile()
{
    fstream fp;
    string line;
    fp.open(MAKEFILE);
    while(getline(fp, line))
    {
        parseLine(line);
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
        //depList[depCounter].source[sourceCount++] = currentDependencies.substr(prev, found - 1);
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

string removeWhiteSpace(string str)
{
    str.erase (std::remove(str.begin(), str.end(),' '), str.end());
    return str;
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
        command = currentDependencies.substr(found, currentDependencies.length() - found);

    }
    if(target.length() != 0)
    {
        depList.push_back(makeNode(false, target, vList, command));
    }
}

void initialize()
{

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

void determineOrderOfExec()
{
    int iterationCount = 0;
    int maxDepth;

    printOutput();
    /*Resolve leaf nodes*/
    buildLeafNodes();
    printOutput();
    /*Resolve the other nodes*/
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

bool compareOrders(dependencyNode x, dependencyNode y)
{
    return (x.depth < y.depth);
}

void sortOrder()
{
    sort(depList.begin(), depList.end(), compareOrders);
}

void printOutput()
{
    for(int i=0; i<depList.size(); i++)
    {
        cout<<"Target "<<depList[i].target<<"Depth "<<depList[i].depth
        <<"isResolved "<<depList[i].isResolved
        <<endl;
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
    determineOrderOfExec();

    /*Sort and print order of execution*/
    sortOrder();

    cout<<endl<<endl<<"Final"<<endl;
    printOutput();
    //printParsedOutput();
    return 0;

}
