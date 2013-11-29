#ifndef REMODEL_TYPES_H
#define REMODEL_TYPES_H

#define SIZE 100;
#define DEFAULT_TARGET "Default"
#define MAKEFILE "makefile"

#include<string>
#include<vector>
using namespace std;

typedef struct dependencyNode_t
{
    string target;
    vector<string> source;
    string command;
}dependencyNode;

#endif
