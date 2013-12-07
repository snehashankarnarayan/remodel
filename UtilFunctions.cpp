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

void stringcopy(unsigned char dest[], const char src[])
{
    int i;
    for(i = 0; src[i]!='\0';i++)
    {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}
