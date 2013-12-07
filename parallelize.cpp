#include "headers.h"

extern vector<dependencyNode> depList;
extern string rootTarget;

void runParallel()
{
    int depth = -1;
    int i = 0;
    FILE *fp;

    while(i < depList.size())
    {
        while(depth == depList[i].depth)
        {
            if(depList[i].command.length() > 0)
            {
                #pragma omp parallel
                {
                    string str = depList[i].command;
                    cout<<"Command: "<<depList[i].command<<endl;
                    str.erase (std::remove(str.begin(), str.end(),'"'), str.end());
                    fp = popen(str.c_str(), "re");
                    pclose(fp);
                   // system("g++ -c foo.cpp -o foo.o");
                }
            }

            i++;
        }

        depth++;
    }
}
