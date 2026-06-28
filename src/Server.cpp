#include "../include/Server.h"
#define DEFAULT_PORT "27015"

Server::Server()
{
    SOCKET serverSocket = SetUpServerSocket();
    if (serverSocket != INVALID_SOCKET)
    {
        ActiveServerSocket(serverSocket);
    }
}

SOCKET Server::SetUpServerSocket()
{
    printf("opening up a server socket \n");
    int iResult;

    // set up the info about the socket
    struct addrinfo *result = NULL, *ptr = NULL, hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);

    SOCKET ListenSocket;

    // create socket
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET)
    {
        printf("error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }
    else
    {
        printf("server socket has been created \n");
    }

    // bound socket to a port
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult)
    {
        printf("bind failed with error: %ld \n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    else
    {
        printf("bind successful \n");
        freeaddrinfo(result);
    }

    // socket is listening
    if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        printf("listen failed with error: %ld \n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    else
    {
        printf("set up main listening server socket, its ready to forward any sockets \n");
    }

    return ListenSocket;
}

void Server::ActiveServerSocket(SOCKET ListenSocket)
{

    // tangent socket for private conversation so listening socket can listen

    for (int i = 0; i < 4; i++)
    {
        SOCKET privateSocket = INVALID_SOCKET;
        // listening until find a connection
        printf("waiting for a connection request \n");
        privateSocket = accept(ListenSocket, NULL, NULL);
        if (privateSocket == INVALID_SOCKET)
        {
            printf("accept failed: %d \n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
            return;
        }
        printf("sending off a socket to a private connection with client \n");
        CreateConnection(privateSocket);
    }

    WSACleanup();

    return;
}

void Server::CreateConnection(SOCKET privateSocket)
{

    char buffer[256];
    // recieve name
    memset(buffer, 0, 256);
    int iResult = recv(privateSocket, buffer, 255, 0);

    // check if have seen this client before
    for (int i = 0; i < 5; i++)
    {
        if (savedClients[i].name == buffer)
        {
            if (savedClients[i].LTK == LTK)
            {
                // we chilin let him through
                PrivateServerConnectionEnCrypted(privateSocket);
            }
            else
            {
                PrivateServerConnectionUnEnCrypted(privateSocket);
                // just do unencrypted
            }
        }
    }

    // must be first time here so set up handshake

    int b = GenerateLTK();
    // add name and ltk key to the array
    PrivateServerConnectionEnCrypted(privateSocket);
}

bool Server::checkSavedClients(char * name)
{
    for (int i = 0; i < 5; i++)
    {
        if (savedClients[i].name == name)
        {
            // have seen this client before
            return true;
        }
    }

    // have never seen this client before
    return false;
}
int Server::GenerateLTK()
{

    return 12345;
}

void Server::PrivateServerConnectionUnEnCrypted(SOCKET privateSocket)
{
    // un encrypted

    printf("set up a private and NOT encrypted connection \n");
    return;
}

void Server::PrivateServerConnectionEnCrypted(SOCKET privateSocket)
{

    printf("set up a private and encrypted connection \n");
    // safe encrypted

    int iResult = 3;

    char buffer[256];

    do
    {
        memset(buffer, 0, 256);
        iResult = recv(privateSocket, buffer, 255, 0);

        if (iResult == 0)
        {
            printf(" connection closed \n");
        }
        else if (iResult > 0)
        {
            printf("recieved bytes: %d \n", iResult);
            printf("%s \n", buffer);
        }
        else
        {
            printf("connection lost \n", iResult);
            closesocket(privateSocket);
        }

    } while (iResult > 0);
}
