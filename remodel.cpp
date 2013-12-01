#include "headers.h"

dependencyNode makeNode(bool isLeaf, string target, vector<string> vList = NULL, string command = "")
{
    dependencyNode d;
    d.target = target;
    d.source = vList;
    d.command = command;
    d.order = 0;
    d.isResolved = isLeaf;
    d.depth = 0;

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

void findAndParseRoot(const char* str)
{
   /* string root = str;
    for(int i=0; i<depList.size(); i++)
    {
        if(depList[i].source == root)
        {
            /* Make it the last statement to be evaluated*/
          /*  depList[i].order = depList.size();
            break;
        }
    }*/
}

void parseInputFile(char* root)
{
    fstream fp;
    string line;
    fp.open(MAKEFILE);
    while(getline(fp, line))
    {
        parseLine(line);
    }
    findAndParseRoot(root);
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
        if(currentDependencies != " " || currentDependencies != "")
        {
            vList.push_back(currentDependencies);
        }
    }
    else
    {
        if((found - prev - 1) != 0)
        {
            vList.push_back(currentDependencies.substr(prev+1, found - prev -1));
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
        command = removeWhiteSpace(currentDependencies.substr(found, currentDependencies.length() - found));

    }
    depList.push_back(makeNode(false, target, vList, command));
}

void initialize()
{
    /*Leaf nodes are already at 0*/
    globalOrder = 1;
}

void printParsedOutput()
{
    for(int i=0; i<depList.size(); i++)
    {
        cout<<endl<<"New NODE"<<endl;
        cout<<"Target "<<depList[i].target<<endl;
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
                d.order = 0;
                d.depth = 0;
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

bool sourceResolved(string source, int& depth)
{
    for(int i=0; i<depList.size(); i++)
    {
        if(source == depList[i].target)
        {
            depth = depList[i].depth;
            return depList[i].isResolved;
        }
    }
}

bool areAllSourcesResolved(int index, int iterationCount, int& maxDepth)
{
    int depth = -1;
    for(int i=0; i<depList[index].source.size(); i++)
    {
        if(sourceResolved(depList[index].source[i], depth))
        {
            if(depth > maxDepth)
            {
                maxDepth = depth;
            }
        }
        else
        {
            /*One of the sources is not yet resolved, return false*/
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
  //  printOutput();
    /*Resolve the other nodes*/
    while(allNotResolved())
    {
        for(int i=0; i<depList.size(); i++)
        {
            maxDepth = -1;
            if(areAllSourcesResolved(i, iterationCount, maxDepth))
            {
                depList[i].isResolved = true;
                depList[i].depth = iterationCount;
                if(maxDepth == iterationCount)
                {
                    /*This node's dependency was also involved in the current iteration, so the dependent node should
                    be built first*/
                    depList[i].order = ++globalOrder;
                }
                else
                {
                    depList[i].order = globalOrder;
                }

            }
        }

        ++iterationCount;
    }
}

bool compareOrders(dependencyNode x, dependencyNode y)
{
    return (x.order < y.order);
}

void sortOrder()
{
    sort(depList.begin(), depList.end(), compareOrders);
}

void printOutput()
{
    for(int i=0; i<depList.size(); i++)
    {
        cout<<"Target "<<depList[i].target<<" Order "<<depList[i].order<<"Depth "<<depList[i].depth<<endl;
    }
}
int main(int argc, char* argv[])
{
    initialize();

    /*Deal with makefile*/
    switch(argc)
    {
        case 2: /* Target specified*/
                parseInputFile(argv[1]);
                break;

        case 1: /*No specified target*/
                parseInputFile(DEFAULT_TARGET);
                break;
    }

    /*Input file is parsed now. Resolve dependencies and figure out the order of execution*/
    determineOrderOfExec();

    /*Sort and print order of execution*/
    sortOrder();

    cout<<endl<<endl<<"Final"<<endl;
    printOutput();
    //printParsedOutput();
    return 0;

}
