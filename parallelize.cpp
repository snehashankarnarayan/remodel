#include "headers.h"

extern vector<dependencyNode> depList;
extern string rootTarget;

void runParallel()
{
    int depth = -1;
    int i = 0;
    FILE *fp;

    vector<string> commands;

    while(i < depList.size())
    {
        while(depth == depList[i].depth)
        {
            /*Make a vector of all commands to be executed in parallel*/
           if(depList[i].command.length() > 0 && !depList[i].isBuilt)
            {
                string str = depList[i].command;
                str.erase (std::remove(str.begin(), str.end(),'"'), str.end());
                commands.push_back(str);
            }

            i++;
        }

        /*Execute all of the commands in this depth in parallel*/
        #pragma omp parallel for
        for(int i=0; i<commands.size();i++)
            system(commands[i].c_str());

        commands.clear();
        depth++;
    }
}
