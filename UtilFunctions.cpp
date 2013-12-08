//=======================================================================================
// This file contains all the utility functions used
//=======================================================================================

#include "headers.h"

vector<dependencyNode> depList;
string rootTarget;

bool compareOrders(dependencyNode x, dependencyNode y)
{
    return (x.depth < y.depth);
}

void sortOrder()
{
    sort(depList.begin(), depList.end(), compareOrders);
}

string removeWhiteSpace(string str)
{
    str.erase (std::remove(str.begin(), str.end(),' '), str.end());
    return str;
}

bool checkAndCreateDirectory()
{
    struct stat st;
    if(stat(REMODEL_DIR_PATH, &st) == -1)
    {
        /*Directory doesnt exist, create one*/
        mkdir(REMODEL_DIR_PATH, 0777);
        return false;
    }
    return true;
}

