/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "client_tcp.hpp"

using namespace std;

const size_t MAX = 10;
const char* msgToServer = "ping ";

void RunTCPClient(int port, size_t numOfSends)
{
    sockaddr_in servaddr = {0};
    int sockfd = CreateSocket();
    InitSocket(servaddr, port);
    ConnectToServer(sockfd, servaddr);
    ChatWithServer(sockfd, numOfSends);
}

int CreateSocket()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sockfd)
    {
        perror("client : failed socket");
        exit(EXIT_FAILURE);
    }

    return sockfd;
}

void InitSocket(sockaddr_in& servaddr, int port)
{
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(port); 
}

void ConnectToServer(int sockfd, sockaddr_in& servaddr)
{
    if (-1 == connect(sockfd, reinterpret_cast<sockaddr*>(&servaddr), sizeof(servaddr)))
    {
        perror("client : failed connect");
        exit(EXIT_FAILURE);
    }
}

void ChatWithServer(int sockfd, size_t numOfSends)
{
    char buff[MAX] = {0};

    do
    {
        strncpy(buff, msgToServer, strlen(msgToServer));
        if (-1 == write(sockfd, buff, MAX))
        {
            perror("client : failed write");
            exit(EXIT_FAILURE);
        }

        if (-1 == read(sockfd, buff, MAX))
        {
            perror("client : failed read");
            exit(EXIT_FAILURE);
        }

        cout << buff << endl;
        sleep(1);
        --numOfSends;

    }while((0 != strncmp(buff, "exit", 4)) && (numOfSends > 0));

    close(sockfd);
}
