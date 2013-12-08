#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;
int main(int argc, char *argv[])
{
	        if(argc != 2)
				        {
							                cout<<"Invalid"<<endl;
											                exit(1);
															        }

			        ofstream ofs;
					        ofs.open(argv[1], std::ios_base::app);
							        ofs <<endl<<"//new line"<<endl;
									        return 0;
}
