#include <stdio.h>
#include <iostream>
#include <limits>
#include <winsock2.h>
#include <ws2tcpip.h>

#define DEFAULT_PORT "8080"

#pragma comment(lib, "Ws2_32.lib")

int createServerSocket(char *ip);
int createClientSocket(char *ip);

int main(int argc, char **argv)
{

    std::cout << "Hello, Woddrld\n"
              << std::endl;

    WSADATA wsaData;

    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (iResult != 0)
    {
        std::cout << "failed to initialize winsock" << std::endl;
        return 1;
    }
    else
    {
        printf("winsock has been initialized \n");
    }

    char port[] = {'8', '0', '8','0', '\0'};
    //int a = createServerSocket(port);
    
    int b = createClientSocket(port);
    
    
    // iResult = bind(ListenSocket,  );

    std::cin.get();
    return 0;
}

int createServerSocket(char *ip)
{
    printf(" skib");
    struct addrinfo *result = NULL, *ptr = NULL, hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    int iResult;
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);

    SOCKET ListenSocket = INVALID_SOCKET;

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

    // create socket at a port
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
    } else {
        printf("set up main listening server socket, its ready to forward any sockets");
    }

    SOCKET ClientSocket = INVALID_SOCKET;

    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET)
    {
        printf("accept failed: %d \n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    } 

    // no longer need teh server socket (optional)
    closesocket(ListenSocket);

    return 0;
}




int createClientSocket(char *ip)
{
    struct addrinfo *result = NULL, *ptr = NULL, hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    int iResult;
    iResult = getaddrinfo(ip, DEFAULT_PORT, &hints, &result);

    if (iResult != 0)
    {
        printf("the lookup failed, couldnt find nuffin with: %d , the error code is: %d ", DEFAULT_PORT, iResult);
        WSACleanup();
        return 1;
    }
    else
    {
        printf("found an ip address");
    }

    SOCKET ConnectSocket = INVALID_SOCKET;


    // create socket for client
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (ConnectSocket == INVALID_SOCKET)
    {
        printf("error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }
    else
    {
        printf("client socket has been opened \n");
    }


    // set up socket to 
    iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET)
    {
        printf("couldnt connect to server");
        WSACleanup();
    } else {

        printf("the soccket is listening ayeee !!!?");
    }
    


    return 0;
}
