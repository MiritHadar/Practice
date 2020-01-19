/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* version: 	Final			  		                                      */
/* Last update: 					                                          */
/******************************************************************************/

#include <sstream>      // stringstream
#include <iostream>     // cout
#include "parser.hpp"   // header file

namespace l1ght
{

using namespace std;

vector<string> Parser::Parse(const char fileName_[])
{
    string strFromFile = CopyFromFileToBuff(fileName_);
    vector<string> vec = SplitStrIntoLines(strFromFile);

    return vec;
}

vector<string> Parser::SplitStrIntoLines(string &str_)
{
    stringstream stream;
    stream << str_;
    string line;
    vector <string> vec; // No RAII. User responsible for freeing!!!

    do
    {
        getline(stream, line);
        cout << "!" << line << endl;
        vec.push_back(line);
    } while (!stream.eof());
    
    return vec;
}

string Parser::CopyFromFileToBuff(const char fileName_[])
{
    stringbuf buff;
    ifstream myFile;
    myFile.open(fileName_);
    myFile >> &buff;

    string str;
    str = buff.str();
    //cout << str;

    myFile.close();

    return str;
}

FileDoesntOpen::FileDoesntOpen(const std::string &what_)
        : runtime_error(what_)
{
    ;
}

}//namespace l1ght
