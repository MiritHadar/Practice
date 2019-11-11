/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/
#include <utility>              // pair
#include <iostream>             // cout, endl
#include <cstdio>               // stdin
#include "fd_listener.hpp"      // DfListener
#include "logging.hpp"

static void ListenerWithStdin();
static void LoggerTest();

using namespace ilrd;

Logger logger;

int main()
{
    //ListenerWithStdin();
    LoggerTest();
}

static void ListenerWithStdin()
{
    FdListener::FdVector fdVectorInput;
    fdVectorInput.push_back(std::pair<FdListener::Fd, FdListener::FdMode>(0, FdListener::READ));
    fdVectorInput.push_back(std::pair<FdListener::Fd, FdListener::FdMode>(1, FdListener::READ));
    fdVectorInput.push_back(std::pair<FdListener::Fd, FdListener::FdMode>(2, FdListener::READ));
    
    FdListener listener;
    FdListener::FdVector fdVectorOutput = listener(fdVectorInput, 10);

    for(size_t i = 0; i < fdVectorOutput.size(); ++i)
    {
        std::cout << fdVectorOutput[i].first << std::endl;
    }

    char buf[100] = {0};
    fread(buf, sizeof(char), 100, stdin);
    puts(buf);
}

static void LoggerTest()
{
    logger.SetOutputSeverity(Logger::SDEBUG);
    logger.SetOutput(std::cout);
    FdListener::FdVector fdVectorInput;
    fdVectorInput.push_back(std::pair<FdListener::Fd, FdListener::FdMode>(0, FdListener::READ));
    fdVectorInput.push_back(std::pair<FdListener::Fd, FdListener::FdMode>(1, FdListener::READ));
    fdVectorInput.push_back(std::pair<FdListener::Fd, FdListener::FdMode>(2, FdListener::READ));
    
    FdListener listener;
    FdListener::FdVector fdVectorOutput = listener(fdVectorInput, 10);

    for(size_t i = 0; i < fdVectorOutput.size(); ++i)
    {
        std::cout << fdVectorOutput[i].first << std::endl;
    }

    char buf[100] = {0};
    fread(buf, sizeof(char), 100, stdin);
    puts(buf);
}

