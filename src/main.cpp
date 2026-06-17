#include <stdio.h>
#include <iostream>
#include <limits>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "../include/Server.h"
#include "../include/Client.h"

#define DEFAULT_PORT "27015"

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

    char input;

    printf("a: socket setup \nb: client setup \n");
    std::cin >> input;

    if (input == 'a')
    {
        int a = SetUpServerSocket();
    }
    else
    {
        int skib = SetUpClientSocket();
    }

    // int a = createServerSocket((char *)"27015");
    // int b = createClientSocket((char *)"127.0.0.1");

    std::cin.get();
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

    ptr = result;

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
    }
    else
    {
        printf("the socckets are connected !!!?");
    }

    // send some data

    char message[5] = {'a', 'b', 'c', 'd', 'e'};

    int res = send(ConnectSocket, message, 5, MSG_OOB);
    if (res == 0)
    {
        printf("something didnt work it didnt send");
    }
    else
    {
        printf("sent over %d amount of bytes \n", res);
    }

    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}
