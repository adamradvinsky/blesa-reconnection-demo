#include "../include/Client.h"
#define DEFAULT_PORT "27015"

Client::Client()
{
   

    
}

void Client::setSocket(SOCKET newsocket)
{
    curSocket = newsocket;
}

SOCKET Client::getSocket()
{
    return curSocket;
}

int Client::SetUpClientSocket()
{
    printf("setting up client socket \n");
    int iResult;

    // set up into about this thingy
    struct addrinfo *result = NULL, *ptr = NULL, hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
    ptr = result;

    SOCKET ConnectSocket = INVALID_SOCKET;

    // create socket for client
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (ConnectSocket == INVALID_SOCKET)
    {
        printf("error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return -1;
    }
    else
    {
        printf("client socket has been opened \n");
        setSocket(ConnectSocket);
    }

    // connect socket
    iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        closesocket(ConnectSocket);
        setSocket(INVALID_SOCKET);
        ConnectSocket = INVALID_SOCKET;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET)
    {
        printf("couldnt connect to server \n");
        
        printf("aaa \n");
        printf("aaa \n");
        printf("aaa \n");printf("aaa \n");
        printf("aaa \n");printf("aaa \n");
        printf("aaa \n");
        printf("aaa \n");
        printf("aaa \n");
        printf("aaa \n");
        printf("aaa \n");
        WSACleanup();
        return -1;
    }
    else
    {
        printf("the sockets are connected !!!? \n");
    }
    return 1;
}

void Client::sendMessage(char *message)
{
    SOCKET cSocket = getSocket();

    size_t strlen = std::strlen(message);

    int res = send(cSocket, message, strlen, MSG_OOB);
    if (res == 0)
    {
        printf("something didnt work it didnt send \n");
    }
    else
    {
        printf("sent over %d amount of bytes \n", res);
    }
}