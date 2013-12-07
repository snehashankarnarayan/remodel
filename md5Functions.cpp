#include "headers.h"

extern vector<dependencyNode> depList;
extern string rootTarget;

/*Globals of current file*/
vector<hashNode> currentHashList;
vector<hashNode> oldHashList;

hashNode makeNode(unsigned char hashValue[], string fileName)
{
    hashNode h;
    stringcopy(h.hashValue, hashValue);
    h.fileName = fileName;
    return h;
}

void computeMd5OfFile(const char fileName[], unsigned char result[])
{
    std::ifstream ifs(fileName);
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );

    MD5((unsigned char*) content.c_str(), content.size(), result);
}

void storeMD5Hashes()
{
    for(int i=0; i<depList.size(); i++)
    {
        if(depList[i].isResolved)
        {
            /*Is a leaf node, target will have the filename. Only leaf nodes are resolved
            initially.*/
            unsigned char result[MD5_DIGEST_LENGTH];
            computeMd5OfFile(depList[i].target.c_str(), result);
            cout<<"ii"<<endl;
            currentHashList.push_back(makeNode(result, depList[i].target));
            cout<<"uu"<<endl;
        }
    }
    cout<<"Out?"<<endl;
    return;
}

bool findAndCheckHash(string fileName, unsigned char hashValue[])
{
    for(int i=0;i<currentHashList.size(); i++)
    {
        if(currentHashList[i].fileName == fileName)
        {
            if(strcmp(currentHashList[i].hashValue, hashValue) == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    return false;
}


bool checkAgainstMD5Hashes()
{
    ifstream ifs;
    string line;
    size_t found;

    string fileName;
    unsigned char hashValue[MD5_DIGEST_LENGTH];

    try
    {
        ifs.open(REMODEL_FILE_PATH);
        while(getline(ifs, line))
        {
            found  = line.find(":");
            if(found != string::npos)
            {
                /* Copy relevant data*/
                 fileName = removeWhiteSpace(line.substr(0, found));
                 stringcopy(hashValue, (unsigned char*)line.substr(found).c_str());
            }

            if(!findAndCheckHash(fileName, hashValue))
            {
                /*Values have changed so, write again*/
                return true;
            }
            else
            {
                /*Hashes are the same. No need to build file*/
                markTargetAsBuilt(fileName);
            }

        }
    }
    catch(...)
    {
        cout<<"File exception thrown: "<<endl;
    }

    /*if this is reached then it means all values are new*/
    return false;
}

void writeMD5Hashes()
{
    ofstream ofs;
    try
    {
        ofs.open(REMODEL_FILE_PATH);
        for(int i=0; i< currentHashList.size(); i++)
        {
            ofs << currentHashList[i].fileName.c_str() <<":"<< currentHashList[i].hashValue << endl;
        }
        ofs.close();
    }
    catch(...)
    {
        cout<<"File exception thrown: "<<endl;
    }
}

void md5Hashing()
{
    storeMD5Hashes();
    cout<<"returns?"<<endl;
    if(checkAndCreateDirectory())
    {
        /*Directory exists => not the first run*/
        if(checkAgainstMD5Hashes())
        {
            /*Hashes have changed, write them in*/
            writeMD5Hashes();
        }
    }
    else
    {
        writeMD5Hashes();
    }
}
