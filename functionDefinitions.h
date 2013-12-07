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
void storeMD5Hashes();
void runParallel();
bool checkAndCreateDirectory();
void markTargetAsBuilt(string fileName);
void stringcopy(unsigned char dest[], const char src[]);

/* MD5 Hashing related functions */
void computeMd5OfFile(char fileName[], unsigned char* result);
void storeMD5Hashes();
bool checkAgainstMD5Hashes();
void md5Hashing();
void resolveBuilds();

/*Paralellize*/
void runParallel();

#endif
