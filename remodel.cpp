#include "headers.h"

dependencyNode makeNode(string target, vector<string> vList, string command)
{
    dependencyNode d;
    d.target = target;
    d.source = vList;
    d.command = command;
    d.order = -1;
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

void findAndParseRoot(char* root)
{


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
        vList.push_back(currentDependencies);
    }
    else
    {
        cout<<currentDependencies.substr(prev+1, found-1)<<endl;
        vList.push_back(currentDependencies.substr(prev+1, found - prev -1));
    }

    /*Strip white chars*/
    for(int i=0; i<vList.size(); i++)
    {
        //replace(vList[i].begin(), vList[i].end(), ' ', '');
        vList[i].erase (std::remove(vList[i].begin(), vList[i].end(), ' '), vList[i].end());
    }
    return vList;
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
        cout<<"here"<<endl;
        target = line.substr(0, found);
        currentDependencies = line.substr(found+2);

        vList = parseAndFillDependencyList(currentDependencies);

        /*Deal with the command*/
        found = currentDependencies.find("\"");
        if(found != string::npos)
        command = currentDependencies.substr(found, currentDependencies.length() - found);

    }
    depList.push_back(makeNode(target, vList, command));
}

void initialize()
{
    /*depCounter = 0;
    for(int i=0; i<SIZE; i++)
    {
        depList[i].sourceCount = 0;
    }*/
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

    printParsedOutput();
    return 0;

}
