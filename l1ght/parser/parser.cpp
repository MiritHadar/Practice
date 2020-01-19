/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* version: 	Final			  		                                      */
/* Last update: 					                                          */
/******************************************************************************/


#include "parser.hpp"   // Header file

namespace l1ght
{

using namespace std;

FileDoesntOpen::FileDoesntOpen(const std::string &what_)
        : runtime_error(what_)
{
    ;
}

void Parser::Parse(const char fileName_[])
{
    // std::ofstream fp(fileName_);
    // fp.open(fileName_);

    // if (!(fp.is_open()))
    // {
    //     throw FileDoesntOpen(std::string("The file you mentioned failed to open") +
    //                          std::string(strerror(errno)));
    // } 

    // string line;
    // fp.getline(line);

    string line;
    ifstream myfile(fileName_, ios::in);
    if (myfile.is_open())
    {
        while (getline (myfile,line))
        {
            cout << line << endl;
        }

        myfile.close();
    }

    else
    {
         throw FileDoesntOpen(std::string("Unable to open file") +
                                            std::string(strerror(errno)));
    }
}


}//namespace l1ght
