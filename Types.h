//=======================================================================================
// This file contains the decription of the major data structures used.
// dependencyNode: This refers to the nodes of the dependency resolution graph
// hashNode: This refers to the datastructure used to store the MD5 hash and the
//            corresponding filename.
//=======================================================================================
#ifndef REMODEL_TYPES_H
#define REMODEL_TYPES_H

#define SIZE 100;
#define DEFAULT_TARGET "DEFAULT"
#define MAKEFILE "remodelFile"
#define REMODEL_DIR_PATH ".remodel/"
#define REMODEL_FILE_PATH ".remodel/dependency"

#include<string>
#include<vector>
#include<openssl/md5.h>
using namespace std;

typedef struct dependencyNode_t
{
    string target;
    vector<string> source;
    string command;
    int order;
    bool isResolved;
    int depth;
    bool isBuilt;
    int builtCounter;
}dependencyNode;

typedef struct
{
    string fileName;
    string hashValue;
}hashNode;

#endif
