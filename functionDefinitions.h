#ifndef FUNC_DEFN_H
#define FUNC_DEFN_H

/*Parse input files*/

void parseInputFile(char* inputFile);
void parseLine(string line);
void printOutput();
string removeWhiteSpace(string);
dependencyNode makeNode(bool isLeaf, string target, vector<string> vList, string command);
void computeMd5OfFile(char* fileName);
void findAndParseRoot();
void parseInputFile();
vector<string> parseAndFillDependencyList(string currentDependencies);
string removeWhiteSpace(string str);
void parseLine(string line);
void initialize();
bool nodeExists(string nodeName);
void printParsedOutput();
void buildLeafNodes();
bool allNotResolved();
bool sourceResolved(string source);
bool areAllSourcesResolved(int index);
void determineOrderOfExec();
bool compareOrders(dependencyNode x, dependencyNode y);
void sortOrder();
void printOutput();


#endif
