#include "headers.h"

bool compareOrders(dependencyNode x, dependencyNode y)
{
    return (x.depth < y.depth);
}

void sortOrder()
{
    sort(depList.begin(), depList.end(), compareOrders);
}
/*
void computeMd5OfFile(char* fileName)
{
    unsigned char result[MD5_DIGEST_LENGTH];
    std::ifstream ifs(fileName);
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );

    MD5((unsigned char*) content.c_str(), content.size(), result);
}
*/
string removeWhiteSpace(string str)
{
    str.erase (std::remove(str.begin(), str.end(),' '), str.end());
    return str;
}

