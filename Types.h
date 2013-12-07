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
    unsigned char hashValue[MD5_DIGEST_LENGTH];
}hashNode;

#endif
