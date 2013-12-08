#include "headers.h"

extern vector<dependencyNode> depList;
extern string rootTarget;

/*Globals of current file*/
vector<hashNode> currentHashList;
vector<hashNode> oldHashList;

hashNode makeNode(string hashValue, string fileName)
{
    hashNode h;
    h.hashValue = hashValue;
    h.fileName = fileName;
    return h;
}

void computeMd5OfFile(string fileName)
{
    try
    {
        std::ifstream ifs;
        unsigned char result[MD5_DIGEST_LENGTH] = "lol";
        char* buffer;
        ifs.open(fileName.c_str());
        long long length;

        ifs.seekg(0, std::ios::end);
        length = ifs.tellg();
        ifs.seekg(0, std::ios::beg);
        buffer = new char[length];
        ifs.read(buffer, length);
        ifs.close();

        MD5((unsigned char*) buffer, length, result);
        delete(buffer);

        string hashResult = (string)(const char*)result;
        currentHashList.push_back(makeNode(hashResult, fileName));
    }
    catch(...)
    {
        cout<<"File not found: "<<fileName<<endl;
        cout<<REMODEL_ABORT<<endl;
        exit(1);
    }
}

void storeMD5Hashes()
{
    for(int i=0; i<depList.size(); i++)
    {
        if(depList[i].isResolved)
        {
            /*Is a leaf node, target will have the filename. Only leaf nodes are resolved
            initially.*/

            computeMd5OfFile(depList[i].target);
        }
    }
}

bool findAndCheckHash(string fileName, string hashValue)
{
    for(int i=0;i<currentHashList.size(); i++)
    {
        if(currentHashList[i].fileName == fileName)
        {
            if(currentHashList[i].hashValue == hashValue)
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
    int lineNumber = 3;
    bool writeAgainFlag = false;
    string fileName;
    string hashValue;

    try
    {
        ifs.open(REMODEL_FILE_PATH);
        while(getline(ifs, line))
        {
            if(lineNumber%2)
            {
                /*Copy file Name*/
                fileName = line;
            }
            else
            {
                /*Do computation*/

                hashValue = line;
               // cout<<"Fi:"<<fileName<<"line:"<<lineNumber<<"hash:"<<line<<endl;
                if(!findAndCheckHash(fileName, hashValue))
                {
                    /*Values have changed so, write again*/
                    cout<<"File "<<fileName<<" has changed"<<endl;
                    writeAgainFlag = true;
                }
                else
                {
                    markTargetAsBuilt(fileName);
                }
            }

            lineNumber = (lineNumber+1)%2;

        }
    }
    catch(...)
    {
        cout<<"File exception thrown in: "<<REMODEL_FILE_PATH<<endl;
        cout<<REMODEL_ABORT<<endl;
        exit(1);
    }

    ifs.close();
    /*if this is reached then it means all values are new*/
    return writeAgainFlag;
}

void writeMD5Hashes()
{
    ofstream ofs;
    try
    {
        ofs.open(REMODEL_FILE_PATH);
        for(int i=0; i< currentHashList.size(); i++)
        {
            ofs << currentHashList[i].fileName.c_str() <<endl<< currentHashList[i].hashValue << endl;
        }
    }
    catch(...)
    {
        cout<<"Cannot write to file "<<REMODEL_FILE_PATH<<endl;
        cout<<REMODEL_ABORT<<endl;
        exit(1);
    }
    ofs.close();
}

void md5Hashing()
{
    storeMD5Hashes();
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
