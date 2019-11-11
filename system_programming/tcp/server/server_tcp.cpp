/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <pthread.h>
#include "server_tcp.hpp"

const size_t MAX = 10;
const char* msgTcpToClient = "pong";

using namespace std;

static int CreateSocket();
static void InitSocket(sockaddr_in& servaddr, int port);
static void BindToClient(int sockfd, sockaddr_in& servaddr);
static int EstablishCom(int sockfd);
static void ChatWithClient(int sockfd, int connfd);
static void *ChatWrapper(void *args);

void RunTcpServer(int port)
{
    int sockfd = CreateSocket();
    sockaddr_in servaddr = {0};
    InitSocket(servaddr, port);
    BindToClient(sockfd, servaddr);
    int connfd = EstablishCom(sockfd);
    ChatWithClient(sockfd, connfd);
}
    
static int CreateSocket()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sockfd)
    {
        perror("server : failed create");
        exit(EXIT_FAILURE);
    }
    
    return sockfd;
}

static void InitSocket(sockaddr_in& servaddr, int port)
{
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
}

static void BindToClient(int sockfd, sockaddr_in& servaddr)
{
    if (-1 == (bind(sockfd, reinterpret_cast<const sockaddr*>(&servaddr), sizeof(servaddr))))
    {
        perror("server : failed binding");
        exit(EXIT_FAILURE);
    }
}

static int EstablishCom(int sockfd)
{
    if (-1 == listen(sockfd, 4))
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in clientAddr = {0};
    socklen_t lenClientAddr = sizeof(clientAddr);
    int connfd = 0;
    pthread_t thread = 0;
    while (true)
    {
        connfd = accept(sockfd, reinterpret_cast<sockaddr*>(&clientAddr), &lenClientAddr);
        if (-1 == connfd)
        {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }

        int args[2] = {sockfd, connfd};
        if (0 != pthread_create(&thread, NULL, ChatWrapper,
                                        reinterpret_cast<void*>(args)))
        {
            perror("pthread_create failed");
            exit(EXIT_FAILURE);
        }
    }

    return connfd;
}

static void *ChatWrapper(void *args)
{
    ChatWithClient(*reinterpret_cast<int*>(args),
                   *reinterpret_cast<int*>(reinterpret_cast<int*>(args) + 1));
    pthread_detach(pthread_self());

    return NULL;
}

static void ChatWithClient(int sockfd, int connfd)
{
    char buff[MAX] = {0};
    
    while(true)
    {
        bzero(buff, MAX);
        if (-1 == read(connfd, buff, MAX))
        {
            perror("server : failed read");
            exit(EXIT_FAILURE);
        }
        cout << buff << endl;
        strcpy(buff, msgTcpToClient);
        if(-1 == write(connfd, buff, sizeof(buff)))
        {
            perror("server : failed write");
            exit(EXIT_FAILURE);
        }
    }

    close(sockfd);
}