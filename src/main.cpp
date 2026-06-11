#include <stdio.h>
#include <iostream>
#include <limits>
#include <winsock2.h>
#include <ws2tcpip.h>

#define DEFAULT_PORT "27015"

#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char **argv)
{

    std::cout << "Hello, World!" << std::endl;

    WSADATA wsaData;

    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (iResult != 0)
    {
        std::cout << "failed to initialize winsock" << std::endl;
        return 1;
    }

    iResult = createClientSocket(argv[1]);

    std::cin.get();
    return 0;
}

int createServerSocket(char* ip)
{
    struct addrinfo *result = NULL, *ptr = NULL, hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    int iResult;
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);

    SOCKET ListenSocket = INVALID_SOCKET;

    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    
    if(ListenSocket == INVALID_SOCKET){
        printf("error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

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

    SOCKET ConnectSocket = INVALID_SOCKET;

    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (ConnectSocket == INVALID_SOCKET)
    {
        printf("error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    return 0;
}
