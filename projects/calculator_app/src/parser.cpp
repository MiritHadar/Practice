/******************************************************************************/
/* Author: 		    Mirit Hadar											  	  */
/* Version: 	    Final			  		                                  */
/* Last update:     22-01-2020						                          */
/******************************************************************************/

#include <sstream>      // stringstream
#include <iostream>     // cout

#include "parser.hpp"   // header file

namespace mirit
{

using namespace std;

static string CopyFromFileToBuff(const char fileName_[]);
static vector<string> SplitStrIntoLines(string &str_);

vector<string> Parser::Parse(const char fileName_[])
{
    string expressionsFromFile = CopyFromFileToBuff(fileName_);
    vector<string> expressionsToReturn = SplitStrIntoLines(expressionsFromFile);

    return expressionsToReturn;
}

static string CopyFromFileToBuff(const char fileName_[])
{
    stringbuf buff;
    ifstream myFile;
    myFile.open(fileName_);

    if (!myFile.is_open())
    {
        throw FileDoesntOpen("Unable to open file");
    }

    myFile >> &buff;

    string str;
    str = buff.str();

    myFile.close();

    return str;
}

static vector<string> SplitStrIntoLines(string &str_)
{
    stringstream stream;
    stream << str_;
    string line;
    vector<string> expressions;

    do
    {
        getline(stream, line);
        expressions.push_back(line);

    } while (!stream.eof());
    
    return expressions;
}

FileDoesntOpen::FileDoesntOpen(const std::string &what_)
        : runtime_error(what_)
{
    ;
}

} // namespace mirit
