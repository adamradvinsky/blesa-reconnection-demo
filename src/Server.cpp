#include "../include/Server.h"


#define DEFAULT_PORT "27015"

int SetUpServerSocket()
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

    SOCKET ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

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
        printf("set up main listening server socket, its ready to forward any sockets");
    }

    // tangent socket for private conversation so listening socket can listen

    SOCKET ClientSocket = INVALID_SOCKET;

    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET)
    {
        printf("accept failed: %d \n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    char buffer[5];
    do
    {
        iResult = recv(ClientSocket, buffer, 5, 0);

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
            closesocket(ClientSocket);
            WSACleanup();
        }

    } while (iResult > 0);

    // no longer need teh server socket (optional)
    closesocket(ListenSocket);

    return 0;
}
