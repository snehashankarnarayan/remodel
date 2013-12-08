//=======================================================================================
// This file contains all https://www.google.com/ionsthe function declarat
//=======================================================================================
#ifndef FUNC_DEFN_H
#define FUNC_DEFN_H

/*Input parse related functions*/
void parseInputFile(char* inputFile);
void parseLine(string line);
void parseInputFile();

/*Node related functions*/
dependencyNode makeNode(bool isLeaf, string target, vector<string> vList, string command);
void findAndParseRoot();
vector<string> parseAndFillDependencyList(string currentDependencies);
bool nodeExists(string nodeName);
void buildLeafNodes();
bool allNotResolved();
bool sourceResolved(string source);
bool areAllSourcesResolved(int index);
void determineOrderOfExec();
bool compareOrders(dependencyNode x, dependencyNode y);
void sortOrder();
void resolveBuilds();
void markTargetAsBuilt(string fileName);

/*Parallelism related functions*/
void runParallel();

/*MD5 related functions*/
void computeMd5OfFile(char* fileName);
void storeMD5Hashes();
void md5Hashing();

/*Output related functions*/
void printOutput();
void printParsedOutput();

/*Utility functions*/
string removeWhiteSpace(string);
string removeWhiteSpace(string str);
bool checkAndCreateDirectory();

#endif
