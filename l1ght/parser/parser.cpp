/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* version: 	Final			  		                                      */
/* Last update: 					                                          */
/******************************************************************************/

#include <vector>       // vector
#include <sstream>      // std::stringstream
#include <iostream>
#include "parser.hpp"   // Header file

namespace l1ght
{

using namespace std;

void Parser::Parse(const char fileName_[])
{
    //CopyFromFileToBuff(fileName_);
    string buff = "one zero + seven eight";
    string delimiter = " ";
    size_t pos = 0;
    std::string token;
    while ((pos = buff.find(delimiter)) != string::npos)
    {
        token = buff.substr(0, pos);
        std::cout << token << std::endl;
        //check if itts a num or operator
        //push it in the right stack
        buff.erase(0, pos + delimiter.length());
    }
    cout << "my buff: ";
    cout << buff << endl;

}

string Parser::CopyFromFileToBuff(const char fileName_[])
{
    ifstream myfile(fileName_, ios::binary);

    if (!(myfile.is_open()))
    {
        throw FileDoesntOpen(std::string("Unable to open file") +
                                            std::string(strerror(errno)));
    }
    string buff;

    // char *token = strtok(ss, " ");
    // while(nullptr != token)
    // {
    //     cout << token << endl;
    //     token = strtok(nullptr," ");
    // }

    myfile.close();

    return buff;
}

FileDoesntOpen::FileDoesntOpen(const std::string &what_)
        : runtime_error(what_)
{
    ;
}

}//namespace l1ght
